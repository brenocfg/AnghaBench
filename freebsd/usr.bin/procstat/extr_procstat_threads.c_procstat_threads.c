#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct procstat {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pri_level; } ;
struct kinfo_proc {char* ki_comm; int ki_oncpu; int ki_lastcpu; int ki_stat; int ki_kiflag; char* ki_lockname; char* ki_wmesg; TYPE_1__ ki_pri; int /*<<< orphan*/  ki_tid; int /*<<< orphan*/  ki_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int KERN_PROC_INC_THREAD ; 
 int KERN_PROC_PID ; 
 int KI_LOCKBLOCK ; 
 int PS_OPT_NOHEADER ; 
#define  SIDL 134 
#define  SLOCK 133 
#define  SRUN 132 
#define  SSLEEP 131 
#define  SSTOP 130 
#define  SWAIT 129 
#define  SZOMB 128 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  kinfo_proc_sort (struct kinfo_proc*,unsigned int) ; 
 int /*<<< orphan*/  kinfo_proc_thread_name (struct kinfo_proc*) ; 
 int /*<<< orphan*/  procstat_freeprocs (struct procstat*,struct kinfo_proc*) ; 
 struct kinfo_proc* procstat_getprocs (struct procstat*,int,int /*<<< orphan*/ ,unsigned int*) ; 
 int procstat_opts ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 
 int /*<<< orphan*/  xo_errc (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 

void
procstat_threads(struct procstat *procstat, struct kinfo_proc *kipp)
{
	struct kinfo_proc *kip;
	unsigned int count, i;
	const char *str;
	char *threadid;

	if ((procstat_opts & PS_OPT_NOHEADER) == 0)
		xo_emit("{T:/%5s %6s %-19s %-19s %2s %4s %-7s %-9s}\n", "PID",
		    "TID", "COMM", "TDNAME", "CPU", "PRI", "STATE", "WCHAN");

	xo_emit("{ek:process_id/%d}", kipp->ki_pid);
	xo_emit("{e:command/%s}", strlen(kipp->ki_comm) ?
		    kipp->ki_comm : "-");
	xo_open_container("threads");

	kip = procstat_getprocs(procstat, KERN_PROC_PID | KERN_PROC_INC_THREAD,
	    kipp->ki_pid, &count);
	if (kip == NULL)
		return;
	kinfo_proc_sort(kip, count);
	for (i = 0; i < count; i++) {
		kipp = &kip[i];
		asprintf(&threadid, "%d", kipp->ki_tid);
		if (threadid == NULL)
			xo_errc(1, ENOMEM, "Failed to allocate memory in "
			    "procstat_threads()");
		xo_open_container(threadid);
		xo_emit("{dk:process_id/%5d/%d} ", kipp->ki_pid);
		xo_emit("{:thread_id/%6d/%d} ", kipp->ki_tid);
		xo_emit("{d:command/%-19s/%s} ", strlen(kipp->ki_comm) ?
		    kipp->ki_comm : "-");
		xo_emit("{:thread_name/%-19s/%s} ",
		    kinfo_proc_thread_name(kipp));
		if (kipp->ki_oncpu != 255)
			xo_emit("{:cpu/%3d/%d} ", kipp->ki_oncpu);
		else if (kipp->ki_lastcpu != 255)
			xo_emit("{:cpu/%3d/%d} ", kipp->ki_lastcpu);
		else
			xo_emit("{:cpu/%3s/%s} ", "-");
		xo_emit("{:priority/%4d/%d} ", kipp->ki_pri.pri_level);
		switch (kipp->ki_stat) {
		case SRUN:
			str = "run";
			break;

		case SSTOP:
			str = "stop";
			break;

		case SSLEEP:
			str = "sleep";
			break;

		case SLOCK:
			str = "lock";
			break;

		case SWAIT:
			str = "wait";
			break;

		case SZOMB:
			str = "zomb";
			break;

		case SIDL:
			str = "idle";
			break;

		default:
			str = "??";
			break;
		}
		xo_emit("{:run_state/%-7s/%s} ", str);
		if (kipp->ki_kiflag & KI_LOCKBLOCK) {
			xo_emit("{:lock_name/*%-8s/%s} ",
			    strlen(kipp->ki_lockname) ?
			    kipp->ki_lockname : "-");
		} else {
			xo_emit("{:wait_channel/%-9s/%s} ",
			    strlen(kipp->ki_wmesg) ? kipp->ki_wmesg : "-");
		}
		xo_close_container(threadid);
		free(threadid);
		xo_emit("\n");
	}
	xo_close_container("threads");
	procstat_freeprocs(procstat, kip);
}