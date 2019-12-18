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

/* Variables and functions */
 scalar_t__ __predict_true (int) ; 
 scalar_t__ block_seeded_status ; 
 int /*<<< orphan*/  random_fortuna_pre_read () ; 
 int random_fortuna_seeded_internal () ; 

__attribute__((used)) static bool
random_fortuna_seeded(void)
{

#ifdef _KERNEL
	if (block_seeded_status)
		return (false);
#endif

	if (__predict_true(random_fortuna_seeded_internal()))
		return (true);

	/*
	 * Maybe we have enough entropy in the zeroth pool but just haven't
	 * kicked the initial seed step.  Do so now.
	 */
	random_fortuna_pre_read();

	return (random_fortuna_seeded_internal());
}