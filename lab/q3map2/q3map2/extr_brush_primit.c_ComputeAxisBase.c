#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vec_t ;
typedef  float* vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  atan2 (float,float) ; 
 float cos (int /*<<< orphan*/ ) ; 
 int fabs (float) ; 
 float sin (int /*<<< orphan*/ ) ; 
 float sqrt (float) ; 

void ComputeAxisBase( vec3_t normal, vec3_t texX, vec3_t texY ){
	vec_t RotY, RotZ;


	/* do some cleaning */
	if ( fabs( normal[ 0 ] ) < 1e-6 ) {
		normal[ 0 ] = 0.0f;
	}
	if ( fabs( normal[ 1 ] ) < 1e-6 ) {
		normal[ 1 ] = 0.0f;
	}
	if ( fabs( normal[ 2 ] ) < 1e-6 ) {
		normal[ 2 ] = 0.0f;
	}

	/* compute the two rotations around y and z to rotate x to normal */
	RotY = -atan2( normal[ 2 ], sqrt( normal[ 1 ] * normal[ 1 ] + normal[ 0 ] * normal[ 0 ] ) );
	RotZ = atan2( normal[ 1 ], normal[ 0 ] );

	/* rotate (0,1,0) and (0,0,1) to compute texX and texY */
	texX[ 0 ] = -sin( RotZ );
	texX[ 1 ] = cos( RotZ );
	texX[ 2 ] = 0;

	/* the texY vector is along -z (t texture coorinates axis) */
	texY[ 0 ] = -sin( RotY ) * cos( RotZ );
	texY[ 1 ] = -sin( RotY ) * sin( RotZ );
	texY[ 2 ] = -cos( RotY );
}