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
typedef  float vec_t ;
typedef  float* vec3_t ;

/* Variables and functions */
 float M_PI ; 
 size_t PITCH ; 
 size_t ROLL ; 
 size_t YAW ; 
 scalar_t__ cos (float) ; 
 scalar_t__ sin (float) ; 

void AngleVectors( vec3_t angles, vec3_t forward, vec3_t right, vec3_t up ){
	float angle;
	static float sr, sp, sy, cr, cp, cy;
	// static to help MS compiler fp bugs

	angle = angles[YAW] * ( M_PI * 2.0f / 360.0f );
	sy = (vec_t)sin( angle );
	cy = (vec_t)cos( angle );
	angle = angles[PITCH] * ( M_PI * 2.0f / 360.0f );
	sp = (vec_t)sin( angle );
	cp = (vec_t)cos( angle );
	angle = angles[ROLL] * ( M_PI * 2.0f / 360.0f );
	sr = (vec_t)sin( angle );
	cr = (vec_t)cos( angle );

	if ( forward ) {
		forward[0] = cp * cy;
		forward[1] = cp * sy;
		forward[2] = -sp;
	}
	if ( right ) {
		right[0] = -sr * sp * cy + cr * sy;
		right[1] = -sr * sp * sy - cr * cy;
		right[2] = -sr * cp;
	}
	if ( up ) {
		up[0] = cr * sp * cy + sr * sy;
		up[1] = cr * sp * sy - sr * cy;
		up[2] = cr * cp;
	}
}