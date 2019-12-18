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
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  crng_init_wait ; 
 int /*<<< orphan*/  crng_ready () ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_to_generate_entropy () ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wait_for_random_bytes(void)
{
	if (likely(crng_ready()))
		return 0;

	do {
		int ret;
		ret = wait_event_interruptible_timeout(crng_init_wait, crng_ready(), HZ);
		if (ret)
			return ret > 0 ? 0 : ret;

		try_to_generate_entropy();
	} while (!crng_ready());

	return 0;
}