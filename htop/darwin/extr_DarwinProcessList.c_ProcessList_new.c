#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  UsersTable ;
struct TYPE_6__ {scalar_t__ runningTasks; scalar_t__ totalTasks; scalar_t__ userlandThreads; scalar_t__ kernelThreads; int /*<<< orphan*/  cpuCount; } ;
struct TYPE_7__ {TYPE_1__ super; int /*<<< orphan*/  vm_stats; int /*<<< orphan*/  curr_load; int /*<<< orphan*/  host_info; int /*<<< orphan*/  prev_load; } ;
typedef  TYPE_1__ ProcessList ;
typedef  int /*<<< orphan*/  Hashtable ;
typedef  TYPE_2__ DarwinProcessList ;

/* Variables and functions */
 int /*<<< orphan*/  Class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Process ; 
 int /*<<< orphan*/  ProcessList_allocateCPULoadInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ProcessList_getHostInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ProcessList_getVMStats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ProcessList_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* xCalloc (int,int) ; 

ProcessList* ProcessList_new(UsersTable* usersTable, Hashtable* pidWhiteList, uid_t userId) {
   DarwinProcessList* this = xCalloc(1, sizeof(DarwinProcessList));

   ProcessList_init(&this->super, Class(Process), usersTable, pidWhiteList, userId);

   /* Initialize the CPU information */
   this->super.cpuCount = ProcessList_allocateCPULoadInfo(&this->prev_load);
   ProcessList_getHostInfo(&this->host_info);
   ProcessList_allocateCPULoadInfo(&this->curr_load);

   /* Initialize the VM statistics */
   ProcessList_getVMStats(&this->vm_stats);

   this->super.kernelThreads = 0;
   this->super.userlandThreads = 0;
   this->super.totalTasks = 0;
   this->super.runningTasks = 0;

   return &this->super;
}