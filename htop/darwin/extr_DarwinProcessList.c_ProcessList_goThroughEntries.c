#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_18__ {int /*<<< orphan*/  p_pid; } ;
struct kinfo_proc {TYPE_2__ kp_proc; } ;
struct TYPE_22__ {scalar_t__* cpu_ticks; } ;
struct TYPE_16__ {int /*<<< orphan*/  st_uid; int /*<<< orphan*/  user; } ;
struct TYPE_21__ {TYPE_11__ super; } ;
struct TYPE_17__ {int cpuCount; } ;
struct TYPE_20__ {TYPE_8__* prev_load; TYPE_8__* curr_load; scalar_t__ global_diff; TYPE_1__ super; int /*<<< orphan*/  vm_stats; } ;
struct TYPE_19__ {int /*<<< orphan*/  usersTable; scalar_t__ totalTasks; scalar_t__ runningTasks; scalar_t__ userlandThreads; scalar_t__ kernelThreads; } ;
typedef  int /*<<< orphan*/  Process_New ;
typedef  TYPE_3__ ProcessList ;
typedef  TYPE_4__ DarwinProcessList ;
typedef  TYPE_5__ DarwinProcess ;

/* Variables and functions */
 size_t CPU_STATE_MAX ; 
 scalar_t__ CompareKernelVersion (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ DarwinProcess_new ; 
 int /*<<< orphan*/  DarwinProcess_scanThreads (TYPE_5__*) ; 
 int /*<<< orphan*/  DarwinProcess_setFromKInfoProc (TYPE_11__*,struct kinfo_proc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DarwinProcess_setFromLibprocPidinfo (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ProcessList_add (TYPE_3__*,TYPE_11__*) ; 
 int /*<<< orphan*/  ProcessList_allocateCPULoadInfo (TYPE_8__**) ; 
 int /*<<< orphan*/  ProcessList_freeCPULoadInfo (TYPE_8__**) ; 
 struct kinfo_proc* ProcessList_getKInfoProcs (size_t*) ; 
 scalar_t__ ProcessList_getProcess (TYPE_3__*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcessList_getVMStats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UsersTable_getRef (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct kinfo_proc*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

void ProcessList_goThroughEntries(ProcessList* super) {
    DarwinProcessList *dpl = (DarwinProcessList *)super;
	bool preExisting = true;
	struct kinfo_proc *ps;
	size_t count;
    DarwinProcess *proc;
    struct timeval tv;

    gettimeofday(&tv, NULL); /* Start processing time */

    /* Update the global data (CPU times and VM stats) */
    ProcessList_freeCPULoadInfo(&dpl->prev_load);
    dpl->prev_load = dpl->curr_load;
    ProcessList_allocateCPULoadInfo(&dpl->curr_load);
    ProcessList_getVMStats(&dpl->vm_stats);

    /* Get the time difference */
    dpl->global_diff = 0;
    for(int i = 0; i < dpl->super.cpuCount; ++i) {
        for(size_t j = 0; j < CPU_STATE_MAX; ++j) {
            dpl->global_diff += dpl->curr_load[i].cpu_ticks[j] - dpl->prev_load[i].cpu_ticks[j];
        }
    }

    /* Clear the thread counts */
    super->kernelThreads = 0;
    super->userlandThreads = 0;
    super->totalTasks = 0;
    super->runningTasks = 0;

    /* We use kinfo_procs for initial data since :
     *
     * 1) They always succeed.
     * 2) The contain the basic information.
     *
     * We attempt to fill-in additional information with libproc.
     */
    ps = ProcessList_getKInfoProcs(&count);

    for(size_t i = 0; i < count; ++i) {
       proc = (DarwinProcess *)ProcessList_getProcess(super, ps[i].kp_proc.p_pid, &preExisting, (Process_New)DarwinProcess_new);

       DarwinProcess_setFromKInfoProc(&proc->super, &ps[i], tv.tv_sec, preExisting);
       DarwinProcess_setFromLibprocPidinfo(proc, dpl);

       // Disabled for High Sierra due to bug in macOS High Sierra
       bool isScanThreadSupported  = ! ( CompareKernelVersion(17, 0, 0) >= 0 && CompareKernelVersion(17, 5, 0) < 0);

       if (isScanThreadSupported){
           DarwinProcess_scanThreads(proc);
       }

       super->totalTasks += 1;

       if(!preExisting) {
           proc->super.user = UsersTable_getRef(super->usersTable, proc->super.st_uid);

           ProcessList_add(super, &proc->super);
       }
    }

    free(ps);
}