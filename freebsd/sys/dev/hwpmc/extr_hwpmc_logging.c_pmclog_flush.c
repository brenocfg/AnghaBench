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
struct pmc_owner {int po_error; int po_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FLS ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  PMCDBG1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct pmc_owner*) ; 
 int PMC_PO_OWNS_LOGFILE ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmc_kthread_mtx ; 
 int /*<<< orphan*/  pmclog_schedule_all (struct pmc_owner*) ; 

int
pmclog_flush(struct pmc_owner *po, int force)
{
	int error;

	PMCDBG1(LOG,FLS,1, "po=%p", po);

	/*
	 * If there is a pending error recorded by the logger thread,
	 * return that.
	 */
	if (po->po_error)
		return (po->po_error);

	error = 0;

	/*
	 * Check that we do have an active log file.
	 */
	mtx_lock(&pmc_kthread_mtx);
	if ((po->po_flags & PMC_PO_OWNS_LOGFILE) == 0) {
		error = EINVAL;
		goto error;
	}

	pmclog_schedule_all(po);
 error:
	mtx_unlock(&pmc_kthread_mtx);

	return (error);
}