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
struct sbuf {int dummy; } ;
struct procstat {int dummy; } ;
struct kinfo_proc {char* ki_comm; int ki_oncpu; int ki_lastcpu; int /*<<< orphan*/  ki_tid; int /*<<< orphan*/  ki_pid; } ;
typedef  int /*<<< orphan*/  mask ;
typedef  int /*<<< orphan*/  cpusetid_t ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUSET_INVALID ; 
 scalar_t__ CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_LEVEL_CPUSET ; 
 int /*<<< orphan*/  CPU_LEVEL_WHICH ; 
 int CPU_SETSIZE ; 
 int /*<<< orphan*/  CPU_WHICH_TID ; 
 int KERN_PROC_INC_THREAD ; 
 int KERN_PROC_PID ; 
 int PS_OPT_NOHEADER ; 
 scalar_t__ cpuset_getaffinity (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ cpuset_getid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kinfo_proc_sort (struct kinfo_proc*,unsigned int) ; 
 int /*<<< orphan*/  kinfo_proc_thread_name (struct kinfo_proc*) ; 
 int /*<<< orphan*/  procstat_freeprocs (struct procstat*,struct kinfo_proc*) ; 
 struct kinfo_proc* procstat_getprocs (struct procstat*,int,int /*<<< orphan*/ ,unsigned int*) ; 
 int procstat_opts ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 scalar_t__ sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int,...) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 
 int /*<<< orphan*/  xo_err (int,char*) ; 

void
procstat_cs(struct procstat *procstat, struct kinfo_proc *kipp)
{
	cpusetid_t cs;
	cpuset_t mask;
	struct kinfo_proc *kip;
	struct sbuf *cpusetbuf;
	unsigned int count, i;
	int once, twice, lastcpu, cpu;

	if ((procstat_opts & PS_OPT_NOHEADER) == 0)
		xo_emit("{T:/%5s %6s %-19s %-19s %2s %4s %-7s}\n", "PID",
		    "TID", "COMM", "TDNAME", "CPU", "CSID", "CPU MASK");

	kip = procstat_getprocs(procstat, KERN_PROC_PID | KERN_PROC_INC_THREAD,
	    kipp->ki_pid, &count);
	if (kip == NULL)
		return;
	kinfo_proc_sort(kip, count);
	for (i = 0; i < count; i++) {
		kipp = &kip[i];
		xo_emit("{k:process_id/%5d/%d} ", kipp->ki_pid);
		xo_emit("{:thread_id/%6d/%d} ", kipp->ki_tid);
		xo_emit("{:command/%-19s/%s} ", strlen(kipp->ki_comm) ?
		    kipp->ki_comm : "-");
		xo_emit("{:thread_name/%-19s/%s} ",
                    kinfo_proc_thread_name(kipp));
		if (kipp->ki_oncpu != 255)
			xo_emit("{:cpu/%3d/%d} ", kipp->ki_oncpu);
		else if (kipp->ki_lastcpu != 255)
			xo_emit("{:cpu/%3d/%d} ", kipp->ki_lastcpu);
		else
			xo_emit("{:cpu/%3s/%s} ", "-");
		if (cpuset_getid(CPU_LEVEL_CPUSET, CPU_WHICH_TID,
		    kipp->ki_tid, &cs) != 0) {
			cs = CPUSET_INVALID;
		}
		xo_emit("{:cpu_set_id/%4d/%d} ", cs);
		if ((cs != CPUSET_INVALID) && 
		    (cpuset_getaffinity(CPU_LEVEL_WHICH, CPU_WHICH_TID,
		    kipp->ki_tid, sizeof(mask), &mask) == 0)) {
			lastcpu = -1;
			once = 0;
			twice = 0;
			cpusetbuf = sbuf_new_auto();
			for (cpu = 0; cpu < CPU_SETSIZE; cpu++) {
				if (CPU_ISSET(cpu, &mask)) {
					if (once == 0) {
						sbuf_printf(cpusetbuf, "%d",
						    cpu);
						once = 1;
					} else if (cpu == lastcpu + 1) {
						twice = 1;
					} else if (twice == 1) {
						sbuf_printf(cpusetbuf, "-%d,%d",
						    lastcpu, cpu);
						twice = 0;
					} else
						sbuf_printf(cpusetbuf, ",%d",
						    cpu);
					lastcpu = cpu;
				}
			}
			if (once && twice)
				sbuf_printf(cpusetbuf, "-%d", lastcpu);
			if (sbuf_finish(cpusetbuf) != 0)
				xo_err(1, "Could not generate output");
			xo_emit("{:cpu_set/%s}", sbuf_data(cpusetbuf));
			sbuf_delete(cpusetbuf);
		}
		xo_emit("\n");
	}
	procstat_freeprocs(procstat, kip);
}