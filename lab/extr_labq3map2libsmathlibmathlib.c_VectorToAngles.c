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
typedef  int vec_t ;
typedef  float* vec3_t ;

/* Variables and functions */
 int M_PI ; 
 scalar_t__ atan2 (float,float) ; 
 scalar_t__ sqrt (float) ; 

void VectorToAngles( vec3_t vec, vec3_t angles ){
	float forward;
	float yaw, pitch;

	if ( ( vec[ 0 ] == 0 ) && ( vec[ 1 ] == 0 ) ) {
		yaw = 0;
		if ( vec[ 2 ] > 0 ) {
			pitch = 90;
		}
		else
		{
			pitch = 270;
		}
	}
	else
	{
		yaw = (vec_t)atan2( vec[ 1 ], vec[ 0 ] ) * 180 / M_PI;
		if ( yaw < 0 ) {
			yaw += 360;
		}

		forward = ( float )sqrt( vec[ 0 ] * vec[ 0 ] + vec[ 1 ] * vec[ 1 ] );
		pitch = (vec_t)atan2( vec[ 2 ], forward ) * 180 / M_PI;
		if ( pitch < 0 ) {
			pitch += 360;
		}
	}

	angles[ 0 ] = pitch;
	angles[ 1 ] = yaw;
	angles[ 2 ] = 0;
}