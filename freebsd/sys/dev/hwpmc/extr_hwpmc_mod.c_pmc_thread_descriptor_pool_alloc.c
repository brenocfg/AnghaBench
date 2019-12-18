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
 struct pmc_thread* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct pmc_thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmc_threadfreelist ; 
 int /*<<< orphan*/  pmc_threadfreelist_entries ; 
 int /*<<< orphan*/  pmc_threadfreelist_mtx ; 
 int /*<<< orphan*/  pt_next ; 

__attribute__((used)) static struct pmc_thread *
pmc_thread_descriptor_pool_alloc(void)
{
	struct pmc_thread *pt;

	mtx_lock_spin(&pmc_threadfreelist_mtx);
	if ((pt = LIST_FIRST(&pmc_threadfreelist)) != NULL) {
		LIST_REMOVE(pt, pt_next);
		pmc_threadfreelist_entries--;
	}
	mtx_unlock_spin(&pmc_threadfreelist_mtx);

	return (pt);
}