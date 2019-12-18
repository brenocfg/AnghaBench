#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_10__ {scalar_t__ pid; int showChildren; scalar_t__ indent; int /*<<< orphan*/  show; } ;
struct TYPE_9__ {int /*<<< orphan*/ * processes2; int /*<<< orphan*/ * processes; TYPE_1__* settings; } ;
struct TYPE_8__ {int direction; int sortKey; int /*<<< orphan*/  treeView; } ;
typedef  TYPE_2__ ProcessList ;
typedef  TYPE_3__ Process ;

/* Variables and functions */
 int PID ; 
 int /*<<< orphan*/  ProcessList_buildTree (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ Process_getParentPid (TYPE_3__*) ; 
 int /*<<< orphan*/  Vector_add (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ Vector_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Vector_insertionSort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Vector_quickSort (int /*<<< orphan*/ *) ; 
 int Vector_size (int /*<<< orphan*/ *) ; 
 scalar_t__ Vector_take (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 

void ProcessList_sort(ProcessList* this) {
   if (!this->settings->treeView) {
      Vector_insertionSort(this->processes);
   } else {
      // Save settings
      int direction = this->settings->direction;
      int sortKey = this->settings->sortKey;
      // Sort by PID
      this->settings->sortKey = PID;
      this->settings->direction = 1;
      Vector_quickSort(this->processes);
      // Restore settings
      this->settings->sortKey = sortKey;
      this->settings->direction = direction;
      int vsize = Vector_size(this->processes);
      // Find all processes whose parent is not visible
      int size;
      while ((size = Vector_size(this->processes))) {
         int i;
         for (i = 0; i < size; i++) {
            Process* process = (Process*)(Vector_get(this->processes, i));
            // Immediately consume not shown processes
            if (!process->show) {
               process = (Process*)(Vector_take(this->processes, i));
               process->indent = 0;
               Vector_add(this->processes2, process);
               ProcessList_buildTree(this, process->pid, 0, 0, direction, false);
               break;
            }
            pid_t ppid = Process_getParentPid(process);
            // Bisect the process vector to find parent
            int l = 0, r = size;
            // If PID corresponds with PPID (e.g. "kernel_task" (PID:0, PPID:0)
            // on Mac OS X 10.11.6) cancel bisecting and regard this process as
            // root.
            if (process->pid == ppid)
               r = 0;
            while (l < r) {
               int c = (l + r) / 2;
               pid_t pid = ((Process*)(Vector_get(this->processes, c)))->pid;
               if (ppid == pid) {
                  break;
               } else if (ppid < pid) {
                  r = c;
               } else {
                  l = c + 1;
               }
            }
            // If parent not found, then construct the tree with this root
            if (l >= r) {
               process = (Process*)(Vector_take(this->processes, i));
               process->indent = 0;
               Vector_add(this->processes2, process);
               ProcessList_buildTree(this, process->pid, 0, 0, direction, process->showChildren);
               break;
            }
         }
         // There should be no loop in the process tree
         assert(i < size);
      }
      assert(Vector_size(this->processes2) == vsize); (void)vsize;
      assert(Vector_size(this->processes) == 0);
      // Swap listings around
      Vector* t = this->processes;
      this->processes = this->processes2;
      this->processes2 = t;
   }
}