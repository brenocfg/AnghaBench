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
typedef  scalar_t__ vec_accu_t ;
typedef  scalar_t__* vec3_t ;
typedef  scalar_t__* vec3_accu_t ;

/* Variables and functions */

void VectorCopyRegularToAccu( const vec3_t in, vec3_accu_t out ){
	out[0] = (vec_accu_t) in[0];
	out[1] = (vec_accu_t) in[1];
	out[2] = (vec_accu_t) in[2];
}