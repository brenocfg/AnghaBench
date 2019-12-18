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
struct ck_barrier_combining_group {int k; int /*<<< orphan*/  sense; int /*<<< orphan*/  count; struct ck_barrier_combining_group* parent; } ;
struct ck_barrier_combining {int dummy; } ;

/* Variables and functions */
 int ck_pr_faa_uint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ck_pr_fence_memory () ; 
 int /*<<< orphan*/  ck_pr_fence_store () ; 
 unsigned int ck_pr_load_uint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ck_pr_stall () ; 
 int /*<<< orphan*/  ck_pr_store_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ck_barrier_combining_aux(struct ck_barrier_combining *barrier,
    struct ck_barrier_combining_group *tnode,
    unsigned int sense)
{

	/*
	 * If this is the last thread in the group, it moves on to the parent group.
	 * Otherwise, it spins on this group's sense.
	 */
	if (ck_pr_faa_uint(&tnode->count, 1) == tnode->k - 1) {
		/*
		 * If we are and will be the last thread entering the barrier for the
		 * current group then signal the parent group if one exists.
		 */
		if (tnode->parent != NULL)
			ck_barrier_combining_aux(barrier, tnode->parent, sense);

		/*
		 * Once the thread returns from its parent(s), it reinitializes the group's
		 * arrival count and signals other threads to continue by flipping the group
		 * sense. Order of these operations is not important since we assume a static
		 * number of threads are members of a barrier for the lifetime of the barrier.
		 * Since count is explicitly reinitialized, it is guaranteed that at any point
		 * tnode->count is equivalent to tnode->k if and only if that many threads
		 * are at the barrier.
		 */
		ck_pr_store_uint(&tnode->count, 0);
		ck_pr_fence_store();
		ck_pr_store_uint(&tnode->sense, ~tnode->sense);
	} else {
		while (sense != ck_pr_load_uint(&tnode->sense))
			ck_pr_stall();
	}
	ck_pr_fence_memory();

	return;
}