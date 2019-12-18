#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct proc_taskinfo {int pti_total_system; int pti_total_user; int pti_virtual_size; int pti_resident_size; scalar_t__ pti_numrunning; scalar_t__ pti_threadnum; int /*<<< orphan*/  pti_faults; } ;
typedef  int /*<<< orphan*/  pti ;
struct TYPE_8__ {double percent_cpu; int time; int m_size; int m_resident; double percent_mem; int /*<<< orphan*/  majflt; scalar_t__ nlwp; int /*<<< orphan*/  pid; } ;
struct TYPE_12__ {int utime; int stime; TYPE_1__ super; } ;
struct TYPE_10__ {int /*<<< orphan*/  runningTasks; int /*<<< orphan*/  totalTasks; int /*<<< orphan*/  userlandThreads; int /*<<< orphan*/  kernelThreads; scalar_t__ cpuCount; } ;
struct TYPE_9__ {scalar_t__ max_mem; } ;
struct TYPE_11__ {TYPE_3__ super; TYPE_2__ host_info; scalar_t__ global_diff; } ;
typedef  TYPE_4__ DarwinProcessList ;
typedef  TYPE_5__ DarwinProcess ;

/* Variables and functions */
 int PAGE_SIZE_KB ; 
 int /*<<< orphan*/  PROC_PIDTASKINFO ; 
 int proc_pidinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct proc_taskinfo*,int) ; 

void DarwinProcess_setFromLibprocPidinfo(DarwinProcess *proc, DarwinProcessList *dpl) {
   struct proc_taskinfo pti;

   if(sizeof(pti) == proc_pidinfo(proc->super.pid, PROC_PIDTASKINFO, 0, &pti, sizeof(pti))) {
      if(0 != proc->utime || 0 != proc->stime) {
         uint64_t diff = (pti.pti_total_system - proc->stime)
                  + (pti.pti_total_user - proc->utime);

         proc->super.percent_cpu = (double)diff * (double)dpl->super.cpuCount
                  / ((double)dpl->global_diff * 100000.0);

//       fprintf(stderr, "%f %llu %llu %llu %llu %llu\n", proc->super.percent_cpu,
//               proc->stime, proc->utime, pti.pti_total_system, pti.pti_total_user, dpl->global_diff);
//       exit(7);
      }

      proc->super.time = (pti.pti_total_system + pti.pti_total_user) / 10000000;
      proc->super.nlwp = pti.pti_threadnum;
      proc->super.m_size = pti.pti_virtual_size / 1024 / PAGE_SIZE_KB;
      proc->super.m_resident = pti.pti_resident_size / 1024 / PAGE_SIZE_KB;
      proc->super.majflt = pti.pti_faults;
      proc->super.percent_mem = (double)pti.pti_resident_size * 100.0
              / (double)dpl->host_info.max_mem;

      proc->stime = pti.pti_total_system;
      proc->utime = pti.pti_total_user;

      dpl->super.kernelThreads += 0; /*pti.pti_threads_system;*/
      dpl->super.userlandThreads += pti.pti_threadnum; /*pti.pti_threads_user;*/
      dpl->super.totalTasks += pti.pti_threadnum;
      dpl->super.runningTasks += pti.pti_numrunning;
   }
}