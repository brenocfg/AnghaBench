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
struct pmclog_pmcdetach {int dummy; } ;
struct pmc_owner {int dummy; } ;
struct pmc {int /*<<< orphan*/  pm_id; struct pmc_owner* pm_owner; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATT ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  PMCDBG2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct pmc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMCDETACH ; 
 int /*<<< orphan*/  PMCLOG_DESPATCH_SYNC (struct pmc_owner*) ; 
 int /*<<< orphan*/  PMCLOG_EMIT32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMCLOG_RESERVE (struct pmc_owner*,int /*<<< orphan*/ ,int) ; 

void
pmclog_process_pmcdetach(struct pmc *pm, pid_t pid)
{
	struct pmc_owner *po;

	PMCDBG2(LOG,ATT,1,"!pm=%p pid=%d", pm, pid);

	po = pm->pm_owner;

	PMCLOG_RESERVE(po, PMCDETACH, sizeof(struct pmclog_pmcdetach));
	PMCLOG_EMIT32(pm->pm_id);
	PMCLOG_EMIT32(pid);
	PMCLOG_DESPATCH_SYNC(po);
}