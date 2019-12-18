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
struct ck_barrier_mcs {int /*<<< orphan*/  parentsense; int /*<<< orphan*/  dummy; int /*<<< orphan*/ ** children; int /*<<< orphan*/ * childnotready; int /*<<< orphan*/ * parent; int /*<<< orphan*/ * havechild; int /*<<< orphan*/  tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ck_pr_store_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ck_barrier_mcs_init(struct ck_barrier_mcs *barrier, unsigned int nthr)
{
	unsigned int i, j;

	ck_pr_store_uint(&barrier->tid, 0);

	for (i = 0; i < nthr; ++i) {
		for (j = 0; j < 4; ++j) {
			/*
			 * If there are still threads that don't have parents,
			 * add it as a child.
			 */
			barrier[i].havechild[j] = ((i << 2) + j < nthr - 1) ? ~0 : 0;

			/*
			 * childnotready is initialized to havechild to ensure
			 * a thread does not wait for a child that does not exist.
			 */
			barrier[i].childnotready[j] = barrier[i].havechild[j];
		}

		/* The root thread does not have a parent. */
		barrier[i].parent = (i == 0) ?
		    &barrier[i].dummy :
		    &barrier[(i - 1) >> 2].childnotready[(i - 1) & 3];

		/* Leaf threads do not have any children. */
		barrier[i].children[0] = ((i << 1) + 1 >= nthr)	?
		    &barrier[i].dummy :
		    &barrier[(i << 1) + 1].parentsense;

		barrier[i].children[1] = ((i << 1) + 2 >= nthr)	?
		    &barrier[i].dummy :
		    &barrier[(i << 1) + 2].parentsense;

		barrier[i].parentsense = 0;
	}

	return;
}