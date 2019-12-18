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
struct kinfo_proc {char* ki_pid; char* ki_tid; char* ki_comm; } ;
struct kinfo_kstack {char* kkst_tid; int kkst_state; int /*<<< orphan*/  kkst_trace; } ;

/* Variables and functions */
 int KERN_PROC_INC_THREAD ; 
 int KERN_PROC_PID ; 
 int KKST_MAXLEN ; 
#define  KKST_STATE_RUNNING 130 
#define  KKST_STATE_STACKOK 129 
#define  KKST_STATE_SWAPPED 128 
 int PS_OPT_NOHEADER ; 
 int PS_OPT_VERBOSE ; 
 int /*<<< orphan*/  kinfo_kstack_sort (struct kinfo_kstack*,unsigned int) ; 
 char* kinfo_proc_thread_name (struct kinfo_proc*) ; 
 int /*<<< orphan*/  kstack_cleanup (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kstack_cleanup_encoded (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  procstat_freekstack (struct procstat*,struct kinfo_kstack*) ; 
 int /*<<< orphan*/  procstat_freeprocs (struct procstat*,struct kinfo_proc*) ; 
 struct kinfo_kstack* procstat_getkstack (struct procstat*,struct kinfo_proc*,unsigned int*) ; 
 struct kinfo_proc* procstat_getprocs (struct procstat*,int,char*,unsigned int*) ; 
 int procstat_opts ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,char*,...) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 

void
procstat_kstack(struct procstat *procstat, struct kinfo_proc *kipp)
{
	struct kinfo_kstack *kkstp, *kkstp_free;
	struct kinfo_proc *kip, *kip_free;
	char trace[KKST_MAXLEN], encoded_trace[KKST_MAXLEN];
	unsigned int i, j;
	unsigned int kip_count, kstk_count;

	if ((procstat_opts & PS_OPT_NOHEADER) == 0)
		xo_emit("{T:/%5s %6s %-19s %-19s %-29s}\n", "PID", "TID", "COMM",
		    "TDNAME", "KSTACK");

	kkstp = kkstp_free = procstat_getkstack(procstat, kipp, &kstk_count);
	if (kkstp == NULL)
		return;

	/*
	 * We need to re-query for thread information, so don't use *kipp.
	 */
	kip = kip_free = procstat_getprocs(procstat,
	    KERN_PROC_PID | KERN_PROC_INC_THREAD, kipp->ki_pid, &kip_count);

	if (kip == NULL) {
		procstat_freekstack(procstat, kkstp_free);
		return;
	}

	kinfo_kstack_sort(kkstp, kstk_count);
	for (i = 0; i < kstk_count; i++) {
		kkstp = &kkstp_free[i];

		/*
		 * Look up the specific thread using its tid so we can
		 * display the per-thread command line.
		 */
		kipp = NULL;
		for (j = 0; j < kip_count; j++) {
			kipp = &kip_free[j];
			if (kkstp->kkst_tid == kipp->ki_tid)
				break;
		}
		if (kipp == NULL)
			continue;

		xo_emit("{k:process_id/%5d/%d} ", kipp->ki_pid);
		xo_emit("{:thread_id/%6d/%d} ", kkstp->kkst_tid);
		xo_emit("{:command/%-19s/%s} ", kipp->ki_comm);
		xo_emit("{:thread_name/%-19s/%s} ",
                    kinfo_proc_thread_name(kipp));

		switch (kkstp->kkst_state) {
		case KKST_STATE_RUNNING:
			xo_emit("{:state/%-29s/%s}\n", "<running>");
			continue;

		case KKST_STATE_SWAPPED:
			xo_emit("{:state/%-29s/%s}\n", "<swapped>");
			continue;

		case KKST_STATE_STACKOK:
			break;

		default:
			xo_emit("{:state/%-29s/%s}\n", "<unknown>");
			continue;
		}

		/*
		 * The kernel generates a trace with carriage returns between
		 * entries, but for a more compact view, we convert carriage
		 * returns to spaces.
		 */
		kstack_cleanup(kkstp->kkst_trace, trace,
		    (procstat_opts & PS_OPT_VERBOSE) != 0 ? 2 : 1);
		xo_open_list("trace");
		kstack_cleanup_encoded(kkstp->kkst_trace, encoded_trace,
		    (procstat_opts & PS_OPT_VERBOSE) != 0 ? 2 : 1);
		xo_close_list("trace");
		xo_emit("{d:trace/%-29s}\n", trace);
	}
	procstat_freekstack(procstat, kkstp_free);
	procstat_freeprocs(procstat, kip_free);
}