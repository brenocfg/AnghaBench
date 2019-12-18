#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ kd; struct TYPE_3__* cpus; } ;
typedef  TYPE_1__ SolarisProcessList ;
typedef  int /*<<< orphan*/  ProcessList ;

/* Variables and functions */
 int /*<<< orphan*/  ProcessList_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  kstat_close (scalar_t__) ; 

void ProcessList_delete(ProcessList* pl) {
   SolarisProcessList* spl = (SolarisProcessList*) pl;
   ProcessList_done(pl);
   free(spl->cpus);
   if (spl->kd) kstat_close(spl->kd);
   free(spl);
}