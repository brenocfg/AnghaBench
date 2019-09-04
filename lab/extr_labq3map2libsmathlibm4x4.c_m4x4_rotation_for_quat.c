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
typedef  float* vec4_t ;
typedef  int* m4x4_t ;

/* Variables and functions */

void m4x4_rotation_for_quat( m4x4_t matrix, const vec4_t rotation ){
	float xx,xy,xz,xw,yy,yz,yw,zz,zw;

	xx      = rotation[0] * rotation[0];
	xy      = rotation[0] * rotation[1];
	xz      = rotation[0] * rotation[2];
	xw      = rotation[0] * rotation[3];

	yy      = rotation[1] * rotation[1];
	yz      = rotation[1] * rotation[2];
	yw      = rotation[1] * rotation[3];

	zz      = rotation[2] * rotation[2];
	zw      = rotation[2] * rotation[3];

	matrix[0]  = 1 - 2 * ( yy + zz );
	matrix[4]  =     2 * ( xy - zw );
	matrix[8]  =     2 * ( xz + yw );

	matrix[1]  =     2 * ( xy + zw );
	matrix[5]  = 1 - 2 * ( xx + zz );
	matrix[9]  =     2 * ( yz - xw );

	matrix[2]  =     2 * ( xz - yw );
	matrix[6]  =     2 * ( yz + xw );
	matrix[10] = 1 - 2 * ( xx + yy );

	matrix[3]  = matrix[7] = matrix[11] = matrix[12] = matrix[13] = matrix[14] = 0;
	matrix[15] = 1;
}