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
struct ck_barrier_centralized_state {unsigned int sense; } ;
struct ck_barrier_centralized {int /*<<< orphan*/  sense; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 unsigned int ck_pr_faa_uint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ck_pr_fence_acquire () ; 
 int /*<<< orphan*/  ck_pr_fence_atomic_load () ; 
 int /*<<< orphan*/  ck_pr_fence_memory () ; 
 unsigned int ck_pr_load_uint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ck_pr_stall () ; 
 int /*<<< orphan*/  ck_pr_store_uint (int /*<<< orphan*/ *,unsigned int) ; 

void
ck_barrier_centralized(struct ck_barrier_centralized *barrier,
    struct ck_barrier_centralized_state *state,
    unsigned int n_threads)
{
	unsigned int sense, value;

	/*
	 * Every execution context has a sense associated with it.
	 * This sense is reversed when the barrier is entered. Every
	 * thread will spin on the global sense until the last thread
	 * reverses it.
	 */
	sense = state->sense = ~state->sense;
	value = ck_pr_faa_uint(&barrier->value, 1);
	if (value == n_threads - 1) {
		ck_pr_store_uint(&barrier->value, 0);
		ck_pr_fence_memory();
		ck_pr_store_uint(&barrier->sense, sense);
		return;
	}

	ck_pr_fence_atomic_load();
	while (sense != ck_pr_load_uint(&barrier->sense))
		ck_pr_stall();

	ck_pr_fence_acquire();
	return;
}