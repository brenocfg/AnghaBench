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
struct pmc_thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GROUPTASK_ENQUEUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct pmc_thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THREADENTRY_SIZE ; 
 int /*<<< orphan*/  free_gtask ; 
 int /*<<< orphan*/  memset (struct pmc_thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmc_threadfreelist ; 
 scalar_t__ pmc_threadfreelist_entries ; 
 scalar_t__ pmc_threadfreelist_max ; 
 int /*<<< orphan*/  pmc_threadfreelist_mtx ; 
 int /*<<< orphan*/  pt_next ; 

__attribute__((used)) static void
pmc_thread_descriptor_pool_free(struct pmc_thread *pt)
{

	if (pt == NULL)
		return;

	memset(pt, 0, THREADENTRY_SIZE);
	mtx_lock_spin(&pmc_threadfreelist_mtx);
	LIST_INSERT_HEAD(&pmc_threadfreelist, pt, pt_next);
	pmc_threadfreelist_entries++;
	if (pmc_threadfreelist_entries > pmc_threadfreelist_max)
		GROUPTASK_ENQUEUE(&free_gtask);
	mtx_unlock_spin(&pmc_threadfreelist_mtx);
}