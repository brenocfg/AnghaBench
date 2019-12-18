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
struct ikev2_integ_alg {int id; } ;

/* Variables and functions */
 size_t NUM_INTEG_ALGS ; 
 struct ikev2_integ_alg const* ikev2_integ_algs ; 

const struct ikev2_integ_alg * ikev2_get_integ(int id)
{
	size_t i;

	for (i = 0; i < NUM_INTEG_ALGS; i++) {
		if (ikev2_integ_algs[i].id == id)
			return &ikev2_integ_algs[i];
	}

	return NULL;
}