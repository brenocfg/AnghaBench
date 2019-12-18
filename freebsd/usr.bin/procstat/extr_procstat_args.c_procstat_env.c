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
struct procstat {int dummy; } ;
struct kinfo_proc {int /*<<< orphan*/  ki_comm; int /*<<< orphan*/  ki_pid; } ;

/* Variables and functions */
 int PS_OPT_NOHEADER ; 
 char** procstat_getenvv (struct procstat*,struct kinfo_proc*,int /*<<< orphan*/ ) ; 
 int procstat_opts ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 

void
procstat_env(struct procstat *procstat, struct kinfo_proc *kipp)
{
	int i;
	char **envs;

	if ((procstat_opts & PS_OPT_NOHEADER) == 0) {
		xo_emit("{T:/%5s %-16s %-53s}\n", "PID", "COMM", "ENVIRONMENT");
	}

	envs = procstat_getenvv(procstat, kipp, 0);

	xo_emit("{k:process_id/%5d/%d} {:command/%-16s/%s}", kipp->ki_pid,
	    kipp->ki_comm);

	if (envs == NULL) {
		xo_emit(" {d:env/-}\n");
		return;
	}

	xo_open_list("environment");
	for (i = 0; envs[i] != NULL; i++)
		xo_emit(" {l:env/%s}", envs[i]);
	xo_close_list("environment");
	xo_emit("\n");
}