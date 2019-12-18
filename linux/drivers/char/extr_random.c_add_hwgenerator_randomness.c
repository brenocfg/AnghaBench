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
struct entropy_store {int dummy; } ;

/* Variables and functions */
 scalar_t__ ENTROPY_BITS (struct entropy_store*) ; 
 int /*<<< orphan*/  credit_entropy_bits (struct entropy_store*,size_t) ; 
 int /*<<< orphan*/  crng_fast_load (char const*,size_t) ; 
 scalar_t__ crng_init ; 
 struct entropy_store input_pool ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  mix_pool_bytes (struct entropy_store*,char const*,size_t) ; 
 int /*<<< orphan*/  random_write_wait ; 
 scalar_t__ random_write_wakeup_bits ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_event_freezable (int /*<<< orphan*/ ,int) ; 

void add_hwgenerator_randomness(const char *buffer, size_t count,
				size_t entropy)
{
	struct entropy_store *poolp = &input_pool;

	if (unlikely(crng_init == 0)) {
		crng_fast_load(buffer, count);
		return;
	}

	/* Suspend writing if we're above the trickle threshold.
	 * We'll be woken up again once below random_write_wakeup_thresh,
	 * or when the calling thread is about to terminate.
	 */
	wait_event_freezable(random_write_wait,
			kthread_should_stop() ||
			ENTROPY_BITS(&input_pool) <= random_write_wakeup_bits);
	mix_pool_bytes(poolp, buffer, count);
	credit_entropy_bits(poolp, entropy);
}