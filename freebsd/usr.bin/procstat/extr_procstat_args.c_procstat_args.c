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
 char** procstat_getargv (struct procstat*,struct kinfo_proc*,int /*<<< orphan*/ ) ; 
 int procstat_opts ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 

void
procstat_args(struct procstat *procstat, struct kinfo_proc *kipp)
{
	int i;
	char **args;

	if ((procstat_opts & PS_OPT_NOHEADER) == 0) {
		xo_emit("{T:/%5s %-16s %-53s}\n", "PID", "COMM", "ARGS");
	}

	args = procstat_getargv(procstat, kipp, 0);

	xo_emit("{k:process_id/%5d/%d} {:command/%-16s/%s}", kipp->ki_pid,
	    kipp->ki_comm);

	if (args == NULL) {
		xo_emit(" {d:args/-}\n");
		return;
	}

	xo_open_list("arguments");
	for (i = 0; args[i] != NULL; i++)
		xo_emit(" {l:args/%s}", args[i]);
	xo_close_list("arguments");
	xo_emit("\n");
}