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
struct pmc_owner {int /*<<< orphan*/ * po_kthread; int /*<<< orphan*/  po_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMC_PO_OWNS_LOGFILE ; 
 int /*<<< orphan*/  PPAUSE ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  kern_psignal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmc_kthread_mtx ; 
 int /*<<< orphan*/  wakeup_one (struct pmc_owner*) ; 

__attribute__((used)) static void
pmclog_stop_kthread(struct pmc_owner *po)
{

	mtx_lock(&pmc_kthread_mtx);
	po->po_flags &= ~PMC_PO_OWNS_LOGFILE;
	if (po->po_kthread != NULL) {
		PROC_LOCK(po->po_kthread);
		kern_psignal(po->po_kthread, SIGHUP);
		PROC_UNLOCK(po->po_kthread);
	}
	wakeup_one(po);
	while (po->po_kthread)
		msleep(po->po_kthread, &pmc_kthread_mtx, PPAUSE, "pmckstp", 0);
	mtx_unlock(&pmc_kthread_mtx);
}