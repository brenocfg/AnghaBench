#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int pri_level; scalar_t__ pri_class; } ;
struct TYPE_18__ {int /*<<< orphan*/  tv_sec; } ;
struct kinfo_proc {int ki_pid; scalar_t__ ki_jid; int ki_flag; scalar_t__ ki_ppid; scalar_t__ ki_uid; int ki_size; double ki_rssize; int ki_runtime; int ki_nice; int ki_stat; TYPE_1__ ki_pri; int /*<<< orphan*/  ki_comm; scalar_t__ ki_pctcpu; int /*<<< orphan*/  ki_numthreads; TYPE_2__ ki_start; int /*<<< orphan*/  ki_pgid; int /*<<< orphan*/  ki_tdev; int /*<<< orphan*/  ki_sid; int /*<<< orphan*/  ki_tpgid; } ;
struct TYPE_23__ {scalar_t__ jid; int kernel; void* jname; } ;
struct TYPE_22__ {int /*<<< orphan*/  kd; } ;
struct TYPE_21__ {int show; int pid; scalar_t__ ppid; int tgid; scalar_t__ st_uid; int m_size; double m_resident; double percent_mem; int time; double percent_cpu; int priority; int nice; char state; int updated; int /*<<< orphan*/  nlwp; int /*<<< orphan*/  basenameOffset; void* comm; void* user; int /*<<< orphan*/  starttime_ctime; int /*<<< orphan*/  pgrp; int /*<<< orphan*/  tty_nr; int /*<<< orphan*/  session; int /*<<< orphan*/  tpgid; } ;
struct TYPE_20__ {int cpuCount; int /*<<< orphan*/  runningTasks; int /*<<< orphan*/  totalTasks; int /*<<< orphan*/  kernelThreads; scalar_t__ totalMem; int /*<<< orphan*/  usersTable; TYPE_3__* settings; } ;
struct TYPE_19__ {int hideKernelThreads; int hideUserlandThreads; scalar_t__ updateProcessNames; } ;
typedef  TYPE_3__ Settings ;
typedef  int /*<<< orphan*/  Process_New ;
typedef  TYPE_4__ ProcessList ;
typedef  TYPE_5__ Process ;
typedef  TYPE_6__ FreeBSDProcessList ;
typedef  TYPE_7__ FreeBSDProcess ;

/* Variables and functions */
 void* FreeBSDProcessList_readJailName (struct kinfo_proc*) ; 
 void* FreeBSDProcessList_readProcessName (int /*<<< orphan*/ ,struct kinfo_proc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBSDProcessList_scanCPUTime (TYPE_4__*) ; 
 int /*<<< orphan*/  FreeBSDProcessList_scanMemoryInfo (TYPE_4__*) ; 
 scalar_t__ FreeBSDProcess_new ; 
 int /*<<< orphan*/  KERN_PROC_PROC ; 
 int NZERO ; 
 double PAGE_SIZE_KB ; 
 int PRIO_MAX ; 
 int PRIO_MIN ; 
 scalar_t__ PRI_IS_REALTIME (scalar_t__) ; 
 int PRI_MAX_REALTIME ; 
 int PRI_MIN_IDLE ; 
 scalar_t__ PRI_TIMESHARE ; 
 int PZERO ; 
 int P_SYSTEM ; 
 int /*<<< orphan*/  ProcessList_add (TYPE_4__*,TYPE_5__*) ; 
 TYPE_5__* ProcessList_getProcess (TYPE_4__*,int,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ Process_isKernelThread (TYPE_7__*) ; 
 scalar_t__ Process_isUserlandThread (TYPE_5__*) ; 
#define  SIDL 134 
#define  SLOCK 133 
#define  SRUN 132 
#define  SSLEEP 131 
#define  SSTOP 130 
#define  SWAIT 129 
#define  SZOMB 128 
 void* UsersTable_getRef (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ kernelFScale ; 
 struct kinfo_proc* kvm_getprocs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int pageSizeKb ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

void ProcessList_goThroughEntries(ProcessList* this) {
   FreeBSDProcessList* fpl = (FreeBSDProcessList*) this;
   Settings* settings = this->settings;
   bool hideKernelThreads = settings->hideKernelThreads;
   bool hideUserlandThreads = settings->hideUserlandThreads;

   FreeBSDProcessList_scanMemoryInfo(this);
   FreeBSDProcessList_scanCPUTime(this);

   int cpus = this->cpuCount;
   int count = 0;
   struct kinfo_proc* kprocs = kvm_getprocs(fpl->kd, KERN_PROC_PROC, 0, &count);

   for (int i = 0; i < count; i++) {
      struct kinfo_proc* kproc = &kprocs[i];
      bool preExisting = false;
      bool isIdleProcess = false;
      Process* proc = ProcessList_getProcess(this, kproc->ki_pid, &preExisting, (Process_New) FreeBSDProcess_new);
      FreeBSDProcess* fp = (FreeBSDProcess*) proc;

      proc->show = ! ((hideKernelThreads && Process_isKernelThread(fp)) || (hideUserlandThreads && Process_isUserlandThread(proc)));

      if (!preExisting) {
         fp->jid = kproc->ki_jid;
         proc->pid = kproc->ki_pid;
         if ( ! ((kproc->ki_pid == 0) || (kproc->ki_pid == 1) ) && kproc->ki_flag & P_SYSTEM)
           fp->kernel = 1;
         else
           fp->kernel = 0;
         proc->ppid = kproc->ki_ppid;
         proc->tpgid = kproc->ki_tpgid;
         proc->tgid = kproc->ki_pid;
         proc->session = kproc->ki_sid;
         proc->tty_nr = kproc->ki_tdev;
         proc->pgrp = kproc->ki_pgid;
         proc->st_uid = kproc->ki_uid;
         proc->starttime_ctime = kproc->ki_start.tv_sec;
         proc->user = UsersTable_getRef(this->usersTable, proc->st_uid);
         ProcessList_add((ProcessList*)this, proc);
         proc->comm = FreeBSDProcessList_readProcessName(fpl->kd, kproc, &proc->basenameOffset);
         fp->jname = FreeBSDProcessList_readJailName(kproc);
      } else {
         if(fp->jid != kproc->ki_jid) {
            // process can enter jail anytime
            fp->jid = kproc->ki_jid;
            free(fp->jname);
            fp->jname = FreeBSDProcessList_readJailName(kproc);
         }
         if (proc->ppid != kproc->ki_ppid) {
            // if there are reapers in the system, process can get reparented anytime
            proc->ppid = kproc->ki_ppid;
         }
         if(proc->st_uid != kproc->ki_uid) {
            // some processes change users (eg. to lower privs)
            proc->st_uid = kproc->ki_uid;
            proc->user = UsersTable_getRef(this->usersTable, proc->st_uid);
         }
         if (settings->updateProcessNames) {
            free(proc->comm);
            proc->comm = FreeBSDProcessList_readProcessName(fpl->kd, kproc, &proc->basenameOffset);
         }
      }

      // from FreeBSD source /src/usr.bin/top/machine.c
      proc->m_size = kproc->ki_size / 1024 / pageSizeKb;
      proc->m_resident = kproc->ki_rssize;
      proc->percent_mem = (proc->m_resident * PAGE_SIZE_KB) / (double)(this->totalMem) * 100.0;
      proc->nlwp = kproc->ki_numthreads;
      proc->time = (kproc->ki_runtime + 5000) / 10000;

      proc->percent_cpu = 100.0 * ((double)kproc->ki_pctcpu / (double)kernelFScale);
      proc->percent_mem = 100.0 * (proc->m_resident * PAGE_SIZE_KB) / (double)(this->totalMem);

      if (proc->percent_cpu > 0.1) {
         // system idle process should own all CPU time left regardless of CPU count
         if ( strcmp("idle", kproc->ki_comm) == 0 ) {
            isIdleProcess = true;
         }
      }

      proc->priority = kproc->ki_pri.pri_level - PZERO;

      if (strcmp("intr", kproc->ki_comm) == 0 && kproc->ki_flag & P_SYSTEM) {
         proc->nice = 0; //@etosan: intr kernel process (not thread) has weird nice value
      } else if (kproc->ki_pri.pri_class == PRI_TIMESHARE) {
         proc->nice = kproc->ki_nice - NZERO;
      } else if (PRI_IS_REALTIME(kproc->ki_pri.pri_class)) {
         proc->nice = PRIO_MIN - 1 - (PRI_MAX_REALTIME - kproc->ki_pri.pri_level);
      } else {
         proc->nice = PRIO_MAX + 1 + kproc->ki_pri.pri_level - PRI_MIN_IDLE;
      }

      switch (kproc->ki_stat) {
      case SIDL:   proc->state = 'I'; break;
      case SRUN:   proc->state = 'R'; break;
      case SSLEEP: proc->state = 'S'; break;
      case SSTOP:  proc->state = 'T'; break;
      case SZOMB:  proc->state = 'Z'; break;
      case SWAIT:  proc->state = 'D'; break;
      case SLOCK:  proc->state = 'L'; break;
      default:     proc->state = '?';
      }

      if (Process_isKernelThread(fp)) {
         this->kernelThreads++;
      }

      this->totalTasks++;
      if (proc->state == 'R')
         this->runningTasks++;
      proc->updated = true;
   }
}