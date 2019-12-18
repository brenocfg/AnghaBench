#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pid_t ;
struct TYPE_4__ {int /*<<< orphan*/  e_id; } ;
struct TYPE_3__ {scalar_t__ proc_pid; scalar_t__ proc_type; scalar_t__ proc_count; int /*<<< orphan*/  proc_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHK_CUR_RUNNERS (char*,int,scalar_t__) ; 
 int CurChildren ; 
 TYPE_2__* CurEnv ; 
 int /*<<< orphan*/  CurRunners ; 
 scalar_t__ CurrentPid ; 
 scalar_t__ DaemonPid ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int LogLevel ; 
 int /*<<< orphan*/  NOQID ; 
 scalar_t__ NO_PID ; 
 scalar_t__ PROC_QUEUE ; 
 int ProcListSize ; 
 TYPE_1__* ProcListVec ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SM_FREE_CLR (int /*<<< orphan*/ ) ; 
 scalar_t__ kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int sm_blocksignal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm_releasesignal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm_syslog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 

void
proc_list_probe()
{
	int i, children;
	int chldwasblocked;
	pid_t pid;

	children = 0;
	chldwasblocked = sm_blocksignal(SIGCHLD);

	/* start from 1 since 0 is the daemon itself */
	for (i = 1; i < ProcListSize; i++)
	{
		pid = ProcListVec[i].proc_pid;
		if (pid == NO_PID || pid == CurrentPid)
			continue;
		if (kill(pid, 0) < 0)
		{
			if (LogLevel > 3)
				sm_syslog(LOG_DEBUG, CurEnv->e_id,
					  "proc_list_probe: lost pid %d",
					  (int) ProcListVec[i].proc_pid);
			ProcListVec[i].proc_pid = NO_PID;
			SM_FREE_CLR(ProcListVec[i].proc_task);

			if (ProcListVec[i].proc_type == PROC_QUEUE)
			{
				CurRunners -= ProcListVec[i].proc_count;
				CHK_CUR_RUNNERS("proc_list_probe", i,
						ProcListVec[i].proc_count);
			}

			CurChildren--;
		}
		else
		{
			++children;
		}
	}
	if (CurChildren < 0)
		CurChildren = 0;
	if (chldwasblocked == 0)
		(void) sm_releasesignal(SIGCHLD);
	if (LogLevel > 10 && children != CurChildren && CurrentPid == DaemonPid)
	{
		sm_syslog(LOG_ERR, NOQID,
			  "proc_list_probe: found %d children, expected %d",
			  children, CurChildren);
	}
}