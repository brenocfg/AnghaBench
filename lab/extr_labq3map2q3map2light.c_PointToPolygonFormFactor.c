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
struct TYPE_3__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ winding_t ;
typedef  int /*<<< orphan*/  const vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 float DotProduct (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int MAX_POINTS_ON_WINDING ; 
 float ONE_OVER_2PI ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 float VectorNormalize (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 float acos (float) ; 

float PointToPolygonFormFactor( const vec3_t point, const vec3_t normal, const winding_t *w ){
	vec3_t triVector, triNormal;
	int i, j;
	vec3_t dirs[ MAX_POINTS_ON_WINDING ];
	float total;
	float dot, angle, facing;


	/* this is expensive */
	for ( i = 0; i < w->numpoints; i++ )
	{
		VectorSubtract( w->p[ i ], point, dirs[ i ] );
		VectorNormalize( dirs[ i ], dirs[ i ] );
	}

	/* duplicate first vertex to avoid mod operation */
	VectorCopy( dirs[ 0 ], dirs[ i ] );

	/* calculcate relative area */
	total = 0.0f;
	for ( i = 0; i < w->numpoints; i++ )
	{
		/* get a triangle */
		j = i + 1;
		dot = DotProduct( dirs[ i ], dirs[ j ] );

		/* roundoff can cause slight creep, which gives an IND from acos */
		if ( dot > 1.0f ) {
			dot = 1.0f;
		}
		else if ( dot < -1.0f ) {
			dot = -1.0f;
		}

		/* get the angle */
		angle = acos( dot );

		CrossProduct( dirs[ i ], dirs[ j ], triVector );
		if ( VectorNormalize( triVector, triNormal ) < 0.0001f ) {
			continue;
		}

		facing = DotProduct( normal, triNormal );
		total += facing * angle;

		/* ydnar: this was throwing too many errors with radiosity + crappy maps. ignoring it. */
		if ( total > 6.3f || total < -6.3f ) {
			return 0.0f;
		}
	}

	/* now in the range of 0 to 1 over the entire incoming hemisphere */
	//%	total /= (2.0f * 3.141592657f);
	total *= ONE_OVER_2PI;
	return total;
}