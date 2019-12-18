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
typedef  scalar_t__ pid_t ;
struct TYPE_3__ {scalar_t__ pid; int showChildren; } ;
typedef  TYPE_1__ Process ;
typedef  int /*<<< orphan*/  Panel ;

/* Variables and functions */
 scalar_t__ Panel_get (int /*<<< orphan*/ *,int) ; 
 scalar_t__ Panel_getSelected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Panel_setSelected (int /*<<< orphan*/ *,int) ; 
 int Panel_size (int /*<<< orphan*/ *) ; 
 scalar_t__ Process_getParentPid (TYPE_1__*) ; 

__attribute__((used)) static bool collapseIntoParent(Panel* panel) {
   Process* p = (Process*) Panel_getSelected(panel);
   if (!p) return false;
   pid_t ppid = Process_getParentPid(p);
   for (int i = 0; i < Panel_size(panel); i++) {
      Process* q = (Process*) Panel_get(panel, i);
      if (q->pid == ppid) {
         q->showChildren = false;
         Panel_setSelected(panel, i);
         return true;
      }
   }
   return false;
}