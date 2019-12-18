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
struct proc {int /*<<< orphan*/  p_comm; int /*<<< orphan*/  p_flag; int /*<<< orphan*/  p_pid; } ;
struct pmclog_proccreate {int dummy; } ;
struct pmc_owner {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAXCOMLEN ; 
 int /*<<< orphan*/  PMCLOG_DESPATCH (struct pmc_owner*) ; 
 int /*<<< orphan*/  PMCLOG_DESPATCH_SYNC (struct pmc_owner*) ; 
 int /*<<< orphan*/  PMCLOG_EMIT32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMCLOG_EMITSTRING (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PMCLOG_RESERVE (struct pmc_owner*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PROC_CREATE ; 

void
pmclog_process_proccreate(struct pmc_owner *po, struct proc *p, int sync)
{
	if (sync) {
		PMCLOG_RESERVE(po, PROC_CREATE, sizeof(struct pmclog_proccreate));
		PMCLOG_EMIT32(p->p_pid);
		PMCLOG_EMIT32(p->p_flag);
		PMCLOG_EMITSTRING(p->p_comm, MAXCOMLEN+1);
		PMCLOG_DESPATCH_SYNC(po);
	} else {
		PMCLOG_RESERVE(po, PROC_CREATE, sizeof(struct pmclog_proccreate));
		PMCLOG_EMIT32(p->p_pid);
		PMCLOG_EMIT32(p->p_flag);
		PMCLOG_EMITSTRING(p->p_comm, MAXCOMLEN+1);
		PMCLOG_DESPATCH(po);
	}
}