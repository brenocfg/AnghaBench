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
struct rand_data {scalar_t__ prev_time; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  jent_get_nstime (scalar_t__*) ; 
 int /*<<< orphan*/  jent_lfsr_time (struct rand_data*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jent_memaccess (struct rand_data*,int /*<<< orphan*/ ) ; 
 int jent_stuck (struct rand_data*,scalar_t__) ; 

__attribute__((used)) static int jent_measure_jitter(struct rand_data *ec)
{
	__u64 time = 0;
	__u64 current_delta = 0;

	/* Invoke one noise source before time measurement to add variations */
	jent_memaccess(ec, 0);

	/*
	 * Get time stamp and calculate time delta to previous
	 * invocation to measure the timing variations
	 */
	jent_get_nstime(&time);
	current_delta = time - ec->prev_time;
	ec->prev_time = time;

	/* Now call the next noise sources which also injects the data */
	jent_lfsr_time(ec, current_delta, 0);

	/* Check whether we have a stuck measurement. */
	return jent_stuck(ec, current_delta);
}