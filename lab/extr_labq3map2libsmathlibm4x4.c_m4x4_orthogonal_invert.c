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
typedef  float* m4x4_t ;

/* Variables and functions */

void m4x4_orthogonal_invert( m4x4_t matrix ){
	float temp;

	temp = -matrix[3];
	matrix[3] = matrix[12];
	matrix[12] = temp;

	temp = -matrix[7];
	matrix[7] = matrix[13];
	matrix[13] = temp;

	temp = -matrix[11];
	matrix[11] = matrix[14];
	matrix[14] = temp;

	/*
	   temp = matrix[1];
	   matrix[1] = matrix[4];
	   matrix[4] = temp;

	   temp = matrix[2];
	   matrix[2] = matrix[8];
	   matrix[8] = temp;

	   temp = matrix[6];
	   matrix[6] = matrix[9];
	   matrix[9] = temp;

	   matrix[3] = -matrix[3];
	   matrix[7] = -matrix[7];
	   matrix[11] = -matrix[11];
	 */
}