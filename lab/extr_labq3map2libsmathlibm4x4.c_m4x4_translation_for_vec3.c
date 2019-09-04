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
typedef  int* vec3_t ;
typedef  int* m4x4_t ;

/* Variables and functions */

void m4x4_translation_for_vec3( m4x4_t matrix, const vec3_t translation ){
	matrix[1] = matrix[2] = matrix[3] =
								matrix[4] = matrix[6] = matrix[7] =
															matrix[8] = matrix[9] = matrix[11] = 0;

	matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1;

	matrix[12] = translation[0];
	matrix[13] = translation[1];
	matrix[14] = translation[2];
}