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
typedef  float* m4x4_t ;

/* Variables and functions */

void m4x4_transform_vec4( const m4x4_t matrix, vec4_t vector ){
	float out1, out2, out3, out4;

	out1 =  matrix[0]  * vector[0];
	out2 =  matrix[1]  * vector[0];
	out3 =  matrix[2]  * vector[0];
	out4 =  matrix[3]  * vector[0];
	out1 += matrix[4]  * vector[1];
	out2 += matrix[5]  * vector[1];
	out3 += matrix[6]  * vector[1];
	out4 += matrix[7]  * vector[1];
	out1 += matrix[8]  * vector[2];
	out2 += matrix[9]  * vector[2];
	out3 += matrix[10] * vector[2];
	out4 += matrix[11] * vector[2];
	out1 += matrix[12] * vector[3];
	out2 += matrix[13] * vector[3];
	out3 += matrix[14] * vector[3];
	out4 += matrix[15] * vector[3];

	vector[0] = out1;
	vector[1] = out2;
	vector[2] = out3;
	vector[3] = out4;
}