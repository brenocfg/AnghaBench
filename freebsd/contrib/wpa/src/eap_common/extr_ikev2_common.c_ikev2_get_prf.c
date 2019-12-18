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
struct ikev2_prf_alg {int id; } ;

/* Variables and functions */
 size_t NUM_PRF_ALGS ; 
 struct ikev2_prf_alg const* ikev2_prf_algs ; 

const struct ikev2_prf_alg * ikev2_get_prf(int id)
{
	size_t i;

	for (i = 0; i < NUM_PRF_ALGS; i++) {
		if (ikev2_prf_algs[i].id == id)
			return &ikev2_prf_algs[i];
	}

	return NULL;
}