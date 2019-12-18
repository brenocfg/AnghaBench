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
struct domainset {int /*<<< orphan*/  ds_mask; } ;

/* Variables and functions */
 int PDROP ; 
 int PUSER ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_domainset_lock ; 
 int /*<<< orphan*/  vm_min_domains ; 
 int /*<<< orphan*/  vm_min_waiters ; 
 scalar_t__ vm_page_count_min_set (int /*<<< orphan*/ *) ; 

void
vm_waitpfault(struct domainset *dset, int timo)
{

	/*
	 * XXX Ideally we would wait only until the allocation could
	 * be satisfied.  This condition can cause new allocators to
	 * consume all freed pages while old allocators wait.
	 */
	mtx_lock(&vm_domainset_lock);
	if (vm_page_count_min_set(&dset->ds_mask)) {
		vm_min_waiters++;
		msleep(&vm_min_domains, &vm_domainset_lock, PUSER | PDROP,
		    "pfault", timo);
	} else
		mtx_unlock(&vm_domainset_lock);
}