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
typedef  float* vec3_t ;
typedef  float* m4x4_t ;

/* Variables and functions */

void m4x4_transform_point( const m4x4_t matrix, vec3_t point ){
	float out1, out2, out3;

	out1 =  matrix[0]  * point[0];
	out2 =  matrix[1]  * point[0];
	out3 =  matrix[2]  * point[0];
	out1 += matrix[4]  * point[1];
	out2 += matrix[5]  * point[1];
	out3 += matrix[6]  * point[1];
	out1 += matrix[8]  * point[2];
	out2 += matrix[9]  * point[2];
	out3 += matrix[10] * point[2];
	out1 += matrix[12];
	out2 += matrix[13];
	out3 += matrix[14];

	point[0] = out1;
	point[1] = out2;
	point[2] = out3;
}