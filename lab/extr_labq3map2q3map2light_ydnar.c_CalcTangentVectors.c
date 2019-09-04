#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_3__ {float* st; float* xyz; } ;
typedef  TYPE_1__ bspDrawVert_t ;

/* Variables and functions */
 int /*<<< orphan*/  VectorNormalize (float*,float*) ; 
 int /*<<< orphan*/  VectorSubtract (float*,float*,float*) ; 
 float fabs (float) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static qboolean CalcTangentVectors( int numVerts, bspDrawVert_t **dv, vec3_t *stv, vec3_t *ttv ){
	int i;
	float bb, s, t;
	vec3_t bary;


	/* calculate barycentric basis for the triangle */
	bb = ( dv[ 1 ]->st[ 0 ] - dv[ 0 ]->st[ 0 ] ) * ( dv[ 2 ]->st[ 1 ] - dv[ 0 ]->st[ 1 ] ) - ( dv[ 2 ]->st[ 0 ] - dv[ 0 ]->st[ 0 ] ) * ( dv[ 1 ]->st[ 1 ] - dv[ 0 ]->st[ 1 ] );
	if ( fabs( bb ) < 0.00000001f ) {
		return qfalse;
	}

	/* do each vertex */
	for ( i = 0; i < numVerts; i++ )
	{
		/* calculate s tangent vector */
		s = dv[ i ]->st[ 0 ] + 10.0f;
		t = dv[ i ]->st[ 1 ];
		bary[ 0 ] = ( ( dv[ 1 ]->st[ 0 ] - s ) * ( dv[ 2 ]->st[ 1 ] - t ) - ( dv[ 2 ]->st[ 0 ] - s ) * ( dv[ 1 ]->st[ 1 ] - t ) ) / bb;
		bary[ 1 ] = ( ( dv[ 2 ]->st[ 0 ] - s ) * ( dv[ 0 ]->st[ 1 ] - t ) - ( dv[ 0 ]->st[ 0 ] - s ) * ( dv[ 2 ]->st[ 1 ] - t ) ) / bb;
		bary[ 2 ] = ( ( dv[ 0 ]->st[ 0 ] - s ) * ( dv[ 1 ]->st[ 1 ] - t ) - ( dv[ 1 ]->st[ 0 ] - s ) * ( dv[ 0 ]->st[ 1 ] - t ) ) / bb;

		stv[ i ][ 0 ] = bary[ 0 ] * dv[ 0 ]->xyz[ 0 ] + bary[ 1 ] * dv[ 1 ]->xyz[ 0 ] + bary[ 2 ] * dv[ 2 ]->xyz[ 0 ];
		stv[ i ][ 1 ] = bary[ 0 ] * dv[ 0 ]->xyz[ 1 ] + bary[ 1 ] * dv[ 1 ]->xyz[ 1 ] + bary[ 2 ] * dv[ 2 ]->xyz[ 1 ];
		stv[ i ][ 2 ] = bary[ 0 ] * dv[ 0 ]->xyz[ 2 ] + bary[ 1 ] * dv[ 1 ]->xyz[ 2 ] + bary[ 2 ] * dv[ 2 ]->xyz[ 2 ];

		VectorSubtract( stv[ i ], dv[ i ]->xyz, stv[ i ] );
		VectorNormalize( stv[ i ], stv[ i ] );

		/* calculate t tangent vector */
		s = dv[ i ]->st[ 0 ];
		t = dv[ i ]->st[ 1 ] + 10.0f;
		bary[ 0 ] = ( ( dv[ 1 ]->st[ 0 ] - s ) * ( dv[ 2 ]->st[ 1 ] - t ) - ( dv[ 2 ]->st[ 0 ] - s ) * ( dv[ 1 ]->st[ 1 ] - t ) ) / bb;
		bary[ 1 ] = ( ( dv[ 2 ]->st[ 0 ] - s ) * ( dv[ 0 ]->st[ 1 ] - t ) - ( dv[ 0 ]->st[ 0 ] - s ) * ( dv[ 2 ]->st[ 1 ] - t ) ) / bb;
		bary[ 2 ] = ( ( dv[ 0 ]->st[ 0 ] - s ) * ( dv[ 1 ]->st[ 1 ] - t ) - ( dv[ 1 ]->st[ 0 ] - s ) * ( dv[ 0 ]->st[ 1 ] - t ) ) / bb;

		ttv[ i ][ 0 ] = bary[ 0 ] * dv[ 0 ]->xyz[ 0 ] + bary[ 1 ] * dv[ 1 ]->xyz[ 0 ] + bary[ 2 ] * dv[ 2 ]->xyz[ 0 ];
		ttv[ i ][ 1 ] = bary[ 0 ] * dv[ 0 ]->xyz[ 1 ] + bary[ 1 ] * dv[ 1 ]->xyz[ 1 ] + bary[ 2 ] * dv[ 2 ]->xyz[ 1 ];
		ttv[ i ][ 2 ] = bary[ 0 ] * dv[ 0 ]->xyz[ 2 ] + bary[ 1 ] * dv[ 1 ]->xyz[ 2 ] + bary[ 2 ] * dv[ 2 ]->xyz[ 2 ];

		VectorSubtract( ttv[ i ], dv[ i ]->xyz, ttv[ i ] );
		VectorNormalize( ttv[ i ], ttv[ i ] );

		/* debug code */
		//%	Sys_FPrintf( SYS_VRB, "%d S: (%f %f %f) T: (%f %f %f)\n", i,
		//%		stv[ i ][ 0 ], stv[ i ][ 1 ], stv[ i ][ 2 ], ttv[ i ][ 0 ], ttv[ i ][ 1 ], ttv[ i ][ 2 ] );
	}

	/* return to caller */
	return qtrue;
}