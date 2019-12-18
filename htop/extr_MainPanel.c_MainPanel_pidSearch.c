#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pid_t ;
struct TYPE_5__ {int pidSearch; } ;
struct TYPE_4__ {scalar_t__ pid; } ;
typedef  TYPE_1__ Process ;
typedef  int /*<<< orphan*/  Panel ;
typedef  TYPE_2__ MainPanel ;

/* Variables and functions */
 scalar_t__ Panel_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Panel_setSelected (int /*<<< orphan*/ *,int) ; 
 int Panel_size (int /*<<< orphan*/ *) ; 

void MainPanel_pidSearch(MainPanel* this, int ch) {
   Panel* super = (Panel*) this;
   pid_t pid = ch-48 + this->pidSearch;
   for (int i = 0; i < Panel_size(super); i++) {
      Process* p = (Process*) Panel_get(super, i);
      if (p && p->pid == pid) {
         Panel_setSelected(super, i);
         break;
      }
   }
   this->pidSearch = pid * 10;
   if (this->pidSearch > 10000000) {
      this->pidSearch = 0;
   }
}