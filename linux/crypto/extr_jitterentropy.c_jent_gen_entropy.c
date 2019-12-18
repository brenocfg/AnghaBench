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
struct rand_data {unsigned int osr; } ;

/* Variables and functions */
 unsigned int DATA_SIZE_BITS ; 
 scalar_t__ jent_measure_jitter (struct rand_data*) ; 

__attribute__((used)) static void jent_gen_entropy(struct rand_data *ec)
{
	unsigned int k = 0;

	/* priming of the ->prev_time value */
	jent_measure_jitter(ec);

	while (1) {
		/* If a stuck measurement is received, repeat measurement */
		if (jent_measure_jitter(ec))
			continue;

		/*
		 * We multiply the loop value with ->osr to obtain the
		 * oversampling rate requested by the caller
		 */
		if (++k >= (DATA_SIZE_BITS * ec->osr))
			break;
	}
}