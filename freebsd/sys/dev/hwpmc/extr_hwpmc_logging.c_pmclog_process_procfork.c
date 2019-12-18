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
struct pmclog_procfork {int dummy; } ;
struct pmc_owner {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMCLOG_DESPATCH (struct pmc_owner*) ; 
 int /*<<< orphan*/  PMCLOG_EMIT32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMCLOG_RESERVE (struct pmc_owner*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PROCFORK ; 

void
pmclog_process_procfork(struct pmc_owner *po, pid_t oldpid, pid_t newpid)
{
	PMCLOG_RESERVE(po, PROCFORK, sizeof(struct pmclog_procfork));
	PMCLOG_EMIT32(oldpid);
	PMCLOG_EMIT32(newpid);
	PMCLOG_DESPATCH(po);
}