#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ck_barrier_dissemination_state {size_t tid; size_t parity; int /*<<< orphan*/  sense; } ;
struct ck_barrier_dissemination {unsigned int size; TYPE_1__** flags; } ;
struct TYPE_2__ {unsigned int* pflag; unsigned int tflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ck_pr_fence_acquire () ; 
 int /*<<< orphan*/  ck_pr_load_uint (unsigned int*) ; 
 int /*<<< orphan*/  ck_pr_stall () ; 
 int /*<<< orphan*/  ck_pr_store_uint (unsigned int*,int /*<<< orphan*/ ) ; 

void
ck_barrier_dissemination(struct ck_barrier_dissemination *barrier,
    struct ck_barrier_dissemination_state *state)
{
	unsigned int i;
	unsigned int size = barrier->size;

	for (i = 0; i < size; ++i) {
		unsigned int *pflag, *tflag;

		pflag = barrier[state->tid].flags[state->parity][i].pflag;
		tflag = &barrier[state->tid].flags[state->parity][i].tflag;

		/* Unblock current partner. */
		ck_pr_store_uint(pflag, state->sense);

		/* Wait until some other thread unblocks this one. */
		while (ck_pr_load_uint(tflag) != state->sense)
			ck_pr_stall();
	}

	/*
	 * Dissemination barriers use two sets of flags to prevent race conditions
	 * between successive calls to the barrier. Parity indicates which set will
	 * be used for the next barrier. They also use a sense reversal technique
	 * to avoid re-initialization of the flags for every two calls to the barrier.
	 */
	if (state->parity == 1)
		state->sense = ~state->sense;

	state->parity = 1 - state->parity;

	ck_pr_fence_acquire();
	return;
}