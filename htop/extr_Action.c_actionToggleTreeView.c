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
struct TYPE_5__ {int /*<<< orphan*/  pl; TYPE_1__* settings; } ;
struct TYPE_4__ {int treeView; int direction; } ;
typedef  TYPE_2__ State ;
typedef  int Htop_Reaction ;

/* Variables and functions */
 int HTOP_KEEP_FOLLOWING ; 
 int HTOP_REDRAW_BAR ; 
 int HTOP_REFRESH ; 
 int HTOP_SAVE_SETTINGS ; 
 int HTOP_UPDATE_PANELHDR ; 
 int /*<<< orphan*/  ProcessList_expandTree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Htop_Reaction actionToggleTreeView(State* st) {
   st->settings->treeView = !st->settings->treeView;
   if (st->settings->treeView) st->settings->direction = 1;
   ProcessList_expandTree(st->pl);
   return HTOP_REFRESH | HTOP_SAVE_SETTINGS | HTOP_KEEP_FOLLOWING | HTOP_REDRAW_BAR | HTOP_UPDATE_PANELHDR;
}