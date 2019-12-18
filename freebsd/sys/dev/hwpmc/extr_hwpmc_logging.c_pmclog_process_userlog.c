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
struct pmclog_userdata {int dummy; } ;
struct pmc_owner {int dummy; } ;
struct pmc_op_writelog {int /*<<< orphan*/  pm_userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  PMCDBG2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct pmc_owner*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMCLOG_DESPATCH (struct pmc_owner*) ; 
 int /*<<< orphan*/  PMCLOG_EMIT32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMCLOG_RESERVE_WITH_ERROR (struct pmc_owner*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USERDATA ; 
 int /*<<< orphan*/  WRI ; 

int
pmclog_process_userlog(struct pmc_owner *po, struct pmc_op_writelog *wl)
{
	int error;

	PMCDBG2(LOG,WRI,1, "writelog po=%p ud=0x%x", po, wl->pm_userdata);

	error = 0;

	PMCLOG_RESERVE_WITH_ERROR(po, USERDATA,
	    sizeof(struct pmclog_userdata));
	PMCLOG_EMIT32(wl->pm_userdata);
	PMCLOG_DESPATCH(po);

 error:
	return (error);
}