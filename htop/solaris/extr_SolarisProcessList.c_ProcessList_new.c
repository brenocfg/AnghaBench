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
struct TYPE_7__ {int cpuCount; } ;
struct TYPE_6__ {void* cpus; int /*<<< orphan*/  kd; } ;
typedef  TYPE_1__ SolarisProcessList ;
typedef  TYPE_2__ ProcessList ;
typedef  int /*<<< orphan*/  Hashtable ;
typedef  int /*<<< orphan*/  CPUData ;

/* Variables and functions */
 int /*<<< orphan*/  Class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcessList_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SolarisProcess ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int /*<<< orphan*/  kstat_open () ; 
 int sysconf (int /*<<< orphan*/ ) ; 
 TYPE_1__* xCalloc (int,int) ; 
 void* xRealloc (void*,int) ; 

ProcessList* ProcessList_new(UsersTable* usersTable, Hashtable* pidWhiteList, uid_t userId) {
   SolarisProcessList* spl = xCalloc(1, sizeof(SolarisProcessList));
   ProcessList* pl = (ProcessList*) spl;
   ProcessList_init(pl, Class(SolarisProcess), usersTable, pidWhiteList, userId);

   spl->kd = kstat_open();

   pl->cpuCount = sysconf(_SC_NPROCESSORS_ONLN);

   if (pl->cpuCount == 1 ) {
      spl->cpus = xRealloc(spl->cpus, sizeof(CPUData));
   } else {
      spl->cpus = xRealloc(spl->cpus, (pl->cpuCount + 1) * sizeof(CPUData));
   }

   return pl;
}