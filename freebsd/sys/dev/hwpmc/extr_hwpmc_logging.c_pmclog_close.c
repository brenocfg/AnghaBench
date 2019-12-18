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
struct pmc_owner {int /*<<< orphan*/  po_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLO ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  PMCDBG1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct pmc_owner*) ; 
 int /*<<< orphan*/  PMC_PO_SHUTDOWN ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmc_kthread_mtx ; 
 int /*<<< orphan*/  pmclog_process_closelog (struct pmc_owner*) ; 
 int /*<<< orphan*/  pmclog_schedule_all (struct pmc_owner*) ; 
 int /*<<< orphan*/  wakeup_one (struct pmc_owner*) ; 

int
pmclog_close(struct pmc_owner *po)
{

	PMCDBG1(LOG,CLO,1, "po=%p", po);

	pmclog_process_closelog(po);

	mtx_lock(&pmc_kthread_mtx);
	/*
	 * Initiate shutdown: no new data queued,
	 * thread will close file on last block.
	 */
	po->po_flags |= PMC_PO_SHUTDOWN;
	/* give time for all to see */
	DELAY(50);
	
	/*
	 * Schedule the current buffer.
	 */
	pmclog_schedule_all(po);
	wakeup_one(po);

	mtx_unlock(&pmc_kthread_mtx);

	return (0);
}