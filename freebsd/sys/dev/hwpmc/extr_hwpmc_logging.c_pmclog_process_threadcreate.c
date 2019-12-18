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
struct thread {int /*<<< orphan*/  td_name; int /*<<< orphan*/  td_tid; struct proc* td_proc; } ;
struct proc {int /*<<< orphan*/  p_flag; int /*<<< orphan*/  p_pid; } ;
struct pmclog_threadcreate {int dummy; } ;
struct pmc_owner {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAXCOMLEN ; 
 int /*<<< orphan*/  PMCLOG_DESPATCH (struct pmc_owner*) ; 
 int /*<<< orphan*/  PMCLOG_DESPATCH_SYNC (struct pmc_owner*) ; 
 int /*<<< orphan*/  PMCLOG_EMIT32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMCLOG_EMITSTRING (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PMCLOG_RESERVE (struct pmc_owner*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  THR_CREATE ; 

void
pmclog_process_threadcreate(struct pmc_owner *po, struct thread *td, int sync)
{
	struct proc *p;

	p = td->td_proc;
	if (sync) {
		PMCLOG_RESERVE(po, THR_CREATE, sizeof(struct pmclog_threadcreate));
		PMCLOG_EMIT32(td->td_tid);
		PMCLOG_EMIT32(p->p_pid);
		PMCLOG_EMIT32(p->p_flag);
		PMCLOG_EMIT32(0);
		PMCLOG_EMITSTRING(td->td_name, MAXCOMLEN+1);
		PMCLOG_DESPATCH_SYNC(po);
	} else {
		PMCLOG_RESERVE(po, THR_CREATE, sizeof(struct pmclog_threadcreate));
		PMCLOG_EMIT32(td->td_tid);
		PMCLOG_EMIT32(p->p_pid);
		PMCLOG_EMIT32(p->p_flag);
		PMCLOG_EMIT32(0);
		PMCLOG_EMITSTRING(td->td_name, MAXCOMLEN+1);
		PMCLOG_DESPATCH(po);
	}
}