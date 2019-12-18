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
struct ck_barrier_dissemination_flag {scalar_t__ tflag; scalar_t__* pflag; } ;
struct ck_barrier_dissemination {unsigned int nthr; unsigned int size; struct ck_barrier_dissemination_flag** flags; int /*<<< orphan*/  tid; } ;

/* Variables and functions */
 unsigned int ck_internal_log (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ck_internal_power_2 (unsigned int) ; 
 int /*<<< orphan*/  ck_pr_store_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ck_barrier_dissemination_init(struct ck_barrier_dissemination *barrier,
    struct ck_barrier_dissemination_flag **barrier_internal,
    unsigned int nthr)
{
	unsigned int i, j, k, size, offset;
	bool p = nthr & (nthr - 1);

	barrier->nthr = nthr;
	barrier->size = size = ck_internal_log(ck_internal_power_2(nthr));
	ck_pr_store_uint(&barrier->tid, 0);

	for (i = 0; i < nthr; ++i) {
		barrier[i].flags[0] = barrier_internal[i];
		barrier[i].flags[1] = barrier_internal[i] + size;
	}

	for (i = 0; i < nthr; ++i) {
		for (k = 0, offset = 1; k < size; ++k, offset <<= 1) {
			/*
			 * Determine the thread's partner, j, for the current round, k.
			 * Partners are chosen such that by the completion of the barrier,
			 * every thread has been directly (having one of its flag set) or
			 * indirectly (having one of its partners's flags set) signaled
			 * by every other thread in the barrier.
			 */
			if (p == false)
				j = (i + offset) & (nthr - 1);
			else
				j = (i + offset) % nthr;

			/* Set the thread's partner for round k. */
			barrier[i].flags[0][k].pflag = &barrier[j].flags[0][k].tflag;
			barrier[i].flags[1][k].pflag = &barrier[j].flags[1][k].tflag;

			/* Set the thread's flags to false. */
			barrier[i].flags[0][k].tflag = barrier[i].flags[1][k].tflag = 0;
		}
	}

	return;
}