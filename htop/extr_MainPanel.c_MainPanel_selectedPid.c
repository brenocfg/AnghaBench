#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int pid; } ;
typedef  TYPE_1__ Process ;
typedef  int /*<<< orphan*/  Panel ;
typedef  int /*<<< orphan*/  MainPanel ;

/* Variables and functions */
 scalar_t__ Panel_getSelected (int /*<<< orphan*/ *) ; 

int MainPanel_selectedPid(MainPanel* this) {
   Process* p = (Process*) Panel_getSelected((Panel*)this);
   if (p) {
      return p->pid;
   }
   return -1;
}