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
typedef  int vec_accu_t ;
typedef  int* vec3_accu_t ;

/* Variables and functions */

void VectorScaleAccu( const vec3_accu_t in, vec_accu_t scaleFactor, vec3_accu_t out ){
	out[0] = in[0] * scaleFactor;
	out[1] = in[1] * scaleFactor;
	out[2] = in[2] * scaleFactor;
}