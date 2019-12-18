#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int updated; int show; } ;
struct TYPE_7__ {int /*<<< orphan*/  processes; scalar_t__ runningTasks; scalar_t__ kernelThreads; scalar_t__ userlandThreads; scalar_t__ totalTasks; } ;
typedef  TYPE_1__ ProcessList ;
typedef  TYPE_2__ Process ;

/* Variables and functions */
 int /*<<< orphan*/  ProcessList_goThroughEntries (TYPE_1__*) ; 
 int /*<<< orphan*/  ProcessList_remove (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ Vector_get (int /*<<< orphan*/ ,int) ; 
 int Vector_size (int /*<<< orphan*/ ) ; 

void ProcessList_scan(ProcessList* this) {

   // mark all process as "dirty"
   for (int i = 0; i < Vector_size(this->processes); i++) {
      Process* p = (Process*) Vector_get(this->processes, i);
      p->updated = false;
      p->show = true;
   }

   this->totalTasks = 0;
   this->userlandThreads = 0;
   this->kernelThreads = 0;
   this->runningTasks = 0;

   ProcessList_goThroughEntries(this);
   
   for (int i = Vector_size(this->processes) - 1; i >= 0; i--) {
      Process* p = (Process*) Vector_get(this->processes, i);
      if (p->updated == false)
         ProcessList_remove(this, p);
      else
         p->updated = false;
   }
}