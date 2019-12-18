#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
struct TYPE_5__ {scalar_t__ cluster; int /*<<< orphan*/  origin; int /*<<< orphan*/  hit; scalar_t__ opaque; int /*<<< orphan*/  end; int /*<<< orphan*/  normal; } ;
typedef  TYPE_1__ trace_t ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (float*,float*,float*) ; 
 float DEG2RAD (float) ; 
 float DIRT_CONE_ANGLE ; 
 float Random () ; 
 int /*<<< orphan*/  SetupTrace (TYPE_1__*) ; 
 int /*<<< orphan*/  TraceLine (TYPE_1__*) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,float*) ; 
 float VectorLength (float*) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,float,float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNormalize (float*,float*) ; 
 int /*<<< orphan*/  VectorSet (float*,float,float,float) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 float cos (float) ; 
 float dirtDepth ; 
 int /*<<< orphan*/  dirtGain ; 
 int dirtMode ; 
 float dirtScale ; 
 float** dirtVectors ; 
 int /*<<< orphan*/  dirty ; 
 int numDirtVectors ; 
 float pow (float,int /*<<< orphan*/ ) ; 
 float sin (float) ; 

float DirtForSample( trace_t *trace ){
	int i;
	float gatherDirt, outDirt, angle, elevation, ooDepth;
	vec3_t normal, worldUp, myUp, myRt, temp, direction, displacement;


	/* dummy check */
	if ( !dirty ) {
		return 1.0f;
	}
	if ( trace == NULL || trace->cluster < 0 ) {
		return 0.0f;
	}

	/* setup */
	gatherDirt = 0.0f;
	ooDepth = 1.0f / dirtDepth;
	VectorCopy( trace->normal, normal );

	/* check if the normal is aligned to the world-up */
	if ( normal[ 0 ] == 0.0f && normal[ 1 ] == 0.0f ) {
		if ( normal[ 2 ] == -1.0f ) {
			VectorSet( myRt, -1.0f, 0.0f, 0.0f );
			VectorSet( myUp,  0.0f, 1.0f, 0.0f );
		}
		else {
			VectorSet( myRt, 1.0f, 0.0f, 0.0f );
			VectorSet( myUp, 0.0f, 1.0f, 0.0f );
		}
	}
	else
	{
		VectorSet( worldUp, 0.0f, 0.0f, 1.0f );
		CrossProduct( normal, worldUp, myRt );
		VectorNormalize( myRt, myRt );
		CrossProduct( myRt, normal, myUp );
		VectorNormalize( myUp, myUp );
	}

	/* 1 = random mode, 0 (well everything else) = non-random mode */
	if ( dirtMode == 1 ) {
		/* iterate */
		for ( i = 0; i < numDirtVectors; i++ )
		{
			/* get random vector */
			angle = Random() * DEG2RAD( 360.0f );
			elevation = Random() * DEG2RAD( DIRT_CONE_ANGLE );
			temp[ 0 ] = cos( angle ) * sin( elevation );
			temp[ 1 ] = sin( angle ) * sin( elevation );
			temp[ 2 ] = cos( elevation );

			/* transform into tangent space */
			direction[ 0 ] = myRt[ 0 ] * temp[ 0 ] + myUp[ 0 ] * temp[ 1 ] + normal[ 0 ] * temp[ 2 ];
			direction[ 1 ] = myRt[ 1 ] * temp[ 0 ] + myUp[ 1 ] * temp[ 1 ] + normal[ 1 ] * temp[ 2 ];
			direction[ 2 ] = myRt[ 2 ] * temp[ 0 ] + myUp[ 2 ] * temp[ 1 ] + normal[ 2 ] * temp[ 2 ];

			/* set endpoint */
			VectorMA( trace->origin, dirtDepth, direction, trace->end );
			SetupTrace( trace );

			/* trace */
			TraceLine( trace );
			if ( trace->opaque ) {
				VectorSubtract( trace->hit, trace->origin, displacement );
				gatherDirt += 1.0f - ooDepth * VectorLength( displacement );
			}
		}
	}
	else
	{
		/* iterate through ordered vectors */
		for ( i = 0; i < numDirtVectors; i++ )
		{
			/* transform vector into tangent space */
			direction[ 0 ] = myRt[ 0 ] * dirtVectors[ i ][ 0 ] + myUp[ 0 ] * dirtVectors[ i ][ 1 ] + normal[ 0 ] * dirtVectors[ i ][ 2 ];
			direction[ 1 ] = myRt[ 1 ] * dirtVectors[ i ][ 0 ] + myUp[ 1 ] * dirtVectors[ i ][ 1 ] + normal[ 1 ] * dirtVectors[ i ][ 2 ];
			direction[ 2 ] = myRt[ 2 ] * dirtVectors[ i ][ 0 ] + myUp[ 2 ] * dirtVectors[ i ][ 1 ] + normal[ 2 ] * dirtVectors[ i ][ 2 ];

			/* set endpoint */
			VectorMA( trace->origin, dirtDepth, direction, trace->end );
			SetupTrace( trace );

			/* trace */
			TraceLine( trace );
			if ( trace->opaque ) {
				VectorSubtract( trace->hit, trace->origin, displacement );
				gatherDirt += 1.0f - ooDepth * VectorLength( displacement );
			}
		}
	}

	/* direct ray */
	VectorMA( trace->origin, dirtDepth, normal, trace->end );
	SetupTrace( trace );

	/* trace */
	TraceLine( trace );
	if ( trace->opaque ) {
		VectorSubtract( trace->hit, trace->origin, displacement );
		gatherDirt += 1.0f - ooDepth * VectorLength( displacement );
	}

	/* early out */
	if ( gatherDirt <= 0.0f ) {
		return 1.0f;
	}

	/* apply gain (does this even do much? heh) */
	outDirt = pow( gatherDirt / ( numDirtVectors + 1 ), dirtGain );
	if ( outDirt > 1.0f ) {
		outDirt = 1.0f;
	}

	/* apply scale */
	outDirt *= dirtScale;
	if ( outDirt > 1.0f ) {
		outDirt = 1.0f;
	}

	/* return to sender */
	return 1.0f - outDirt;
}