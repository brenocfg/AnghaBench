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
struct ck_barrier_mcs_state {size_t vpid; int /*<<< orphan*/  sense; } ;
struct ck_barrier_mcs {int /*<<< orphan*/ * children; int /*<<< orphan*/  parentsense; int /*<<< orphan*/  parent; int /*<<< orphan*/  childnotready; } ;

/* Variables and functions */
 int ck_barrier_mcs_check_children (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ck_barrier_mcs_reinitialize_children (struct ck_barrier_mcs*) ; 
 int /*<<< orphan*/  ck_pr_fence_memory () ; 
 int /*<<< orphan*/  ck_pr_load_uint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ck_pr_stall () ; 
 int /*<<< orphan*/  ck_pr_store_uint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ck_barrier_mcs(struct ck_barrier_mcs *barrier,
    struct ck_barrier_mcs_state *state)
{

	/*
	 * Wait until all children have reached the barrier and are done waiting
	 * for their children.
	 */
	while (ck_barrier_mcs_check_children(barrier[state->vpid].childnotready) == false)
		ck_pr_stall();

	/* Reinitialize for next barrier. */
	ck_barrier_mcs_reinitialize_children(&barrier[state->vpid]);

	/* Inform parent thread and its children have arrived at the barrier. */
	ck_pr_store_uint(barrier[state->vpid].parent, 0);

	/* Wait until parent indicates all threads have arrived at the barrier. */
	if (state->vpid != 0) {
		while (ck_pr_load_uint(&barrier[state->vpid].parentsense) != state->sense)
			ck_pr_stall();
	}

	/* Inform children of successful barrier. */
	ck_pr_store_uint(barrier[state->vpid].children[0], state->sense);
	ck_pr_store_uint(barrier[state->vpid].children[1], state->sense);
	state->sense = ~state->sense;
	ck_pr_fence_memory();
	return;
}