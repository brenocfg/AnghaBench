#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct proc {int /*<<< orphan*/  p_comm; TYPE_2__* p_stats; } ;
struct TYPE_6__ {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_4__ {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_5__ {TYPE_1__ p_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  kern_psignal (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_master_comm ; 
 int /*<<< orphan*/  nfsd_master_pid ; 
 struct proc* nfsd_master_proc ; 
 TYPE_3__ nfsd_master_start ; 
 struct proc* pfind (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
nfsrv_backupstable(void)
{
	struct proc *procp;

	if (nfsd_master_proc != NULL) {
		procp = pfind(nfsd_master_pid);
		/* Try to make sure it is the correct process. */
		if (procp == nfsd_master_proc &&
		    procp->p_stats->p_start.tv_sec ==
		    nfsd_master_start.tv_sec &&
		    procp->p_stats->p_start.tv_usec ==
		    nfsd_master_start.tv_usec &&
		    strcmp(procp->p_comm, nfsd_master_comm) == 0)
			kern_psignal(procp, SIGUSR2);
		else
			nfsd_master_proc = NULL;

		if (procp != NULL)
			PROC_UNLOCK(procp);
	}
}