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
struct kinfo_proc {char* ki_pid; char* ki_comm; } ;

/* Variables and functions */
 int KERN_PROC_INC_THREAD ; 
 int KERN_PROC_PID ; 
 int PS_OPT_NOHEADER ; 
 int PS_OPT_PERTHREAD ; 
 int /*<<< orphan*/  kinfo_proc_sort (struct kinfo_proc*,unsigned int) ; 
 int /*<<< orphan*/  print_rusage (struct kinfo_proc*) ; 
 int /*<<< orphan*/  procstat_freeprocs (struct procstat*,struct kinfo_proc*) ; 
 struct kinfo_proc* procstat_getprocs (struct procstat*,int,char*,unsigned int*) ; 
 int procstat_opts ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,char*,...) ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 

void
procstat_rusage(struct procstat *procstat, struct kinfo_proc *kipp)
{
	struct kinfo_proc *kip;
	unsigned int count, i;

	if ((procstat_opts & PS_OPT_NOHEADER) == 0) {
		xo_emit("{d:ta/%5s} ", "PID");
		if ((procstat_opts & PS_OPT_PERTHREAD) != 0)
			xo_emit("{d:tb/%6s} ", "TID");
		xo_emit("{d:tc/%-16s %-32s %14s}\n", "COMM", "RESOURCE",
		    "VALUE        ");
	}

	if ((procstat_opts & PS_OPT_PERTHREAD) == 0) {
		print_rusage(kipp);
		return;
	}

	xo_emit("{e:process_id/%d}", kipp->ki_pid);
	xo_emit("{e:command/%s}", kipp->ki_comm);
	xo_open_container("threads");

	kip = procstat_getprocs(procstat, KERN_PROC_PID | KERN_PROC_INC_THREAD,
	    kipp->ki_pid, &count);
	if (kip == NULL)
		return;
	kinfo_proc_sort(kip, count);
	for (i = 0; i < count; i++) {
		print_rusage(&kip[i]);
	}

	xo_close_container("threads");
	procstat_freeprocs(procstat, kip);
}