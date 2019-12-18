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

/* Variables and functions */
 int /*<<< orphan*/  PVM ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_domainset_lock ; 
 scalar_t__ vm_page_count_severe () ; 
 int /*<<< orphan*/  vm_severe_domains ; 
 int /*<<< orphan*/  vm_severe_waiters ; 

void
vm_wait_severe(void)
{

	mtx_lock(&vm_domainset_lock);
	while (vm_page_count_severe()) {
		vm_severe_waiters++;
		msleep(&vm_severe_domains, &vm_domainset_lock, PVM,
		    "vmwait", 0);
	}
	mtx_unlock(&vm_domainset_lock);
}