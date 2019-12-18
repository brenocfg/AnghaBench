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
struct kinfo_proc {int /*<<< orphan*/  ki_sigmask; int /*<<< orphan*/  ki_siglist; int /*<<< orphan*/  ki_comm; int /*<<< orphan*/  ki_tid; int /*<<< orphan*/  ki_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int KERN_PROC_INC_THREAD ; 
 int KERN_PROC_PID ; 
 int PS_OPT_NOHEADER ; 
 int _SIG_MAXSIG ; 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  kinfo_proc_sort (struct kinfo_proc*,unsigned int) ; 
 int /*<<< orphan*/  procstat_close_signame (int) ; 
 int /*<<< orphan*/  procstat_freeprocs (struct procstat*,struct kinfo_proc*) ; 
 struct kinfo_proc* procstat_getprocs (struct procstat*,int,int /*<<< orphan*/ ,unsigned int*) ; 
 int procstat_opts ; 
 int /*<<< orphan*/  procstat_print_sig (int /*<<< orphan*/ *,int,char) ; 
 int /*<<< orphan*/  procstat_print_signame (int) ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 
 int /*<<< orphan*/  xo_errc (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 

void
procstat_threads_sigs(struct procstat *procstat, struct kinfo_proc *kipp)
{
	struct kinfo_proc *kip;
	int j;
	unsigned int count, i;
	char *threadid;

	if ((procstat_opts & PS_OPT_NOHEADER) == 0)
		xo_emit("{T:/%5s %6s %-16s %-7s %4s}\n", "PID", "TID", "COMM",
		     "SIG", "FLAGS");

	kip = procstat_getprocs(procstat, KERN_PROC_PID | KERN_PROC_INC_THREAD,
	    kipp->ki_pid, &count);
	if (kip == NULL)
		return;
	xo_emit("{ek:process_id/%5d/%d}", kipp->ki_pid);
	xo_emit("{e:command/%-16s/%s}", kipp->ki_comm);
	xo_open_container("threads");
	kinfo_proc_sort(kip, count);
	for (i = 0; i < count; i++) {
		kipp = &kip[i];
		asprintf(&threadid, "%d", kipp->ki_tid);
		if (threadid == NULL)
			xo_errc(1, ENOMEM, "Failed to allocate memory in "
			    "procstat_threads_sigs()");
		xo_open_container(threadid);
		xo_emit("{e:thread_id/%6d/%d}", kipp->ki_tid);
		xo_open_container("signals");
		for (j = 1; j <= _SIG_MAXSIG; j++) {
			xo_emit("{dk:process_id/%5d/%d} ", kipp->ki_pid);
			xo_emit("{d:thread_id/%6d/%d} ", kipp->ki_tid);
			xo_emit("{d:command/%-16s/%s} ", kipp->ki_comm);
			procstat_print_signame(j);
			xo_emit(" ");
			procstat_print_sig(&kipp->ki_siglist, j, 'P');
			procstat_print_sig(&kipp->ki_sigmask, j, 'B');
			procstat_close_signame(j);
			xo_emit("\n");
		}
		xo_close_container("signals");
		xo_close_container(threadid);
		free(threadid);
	}
	xo_close_container("threads");
	procstat_freeprocs(procstat, kip);
}