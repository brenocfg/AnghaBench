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
struct TYPE_3__ {int direction; int treeView; int /*<<< orphan*/  sortKey; } ;
typedef  TYPE_1__ Settings ;
typedef  int /*<<< orphan*/  ProcessField ;
typedef  int Htop_Reaction ;

/* Variables and functions */
 int HTOP_KEEP_FOLLOWING ; 
 int HTOP_REFRESH ; 
 int HTOP_SAVE_SETTINGS ; 
 int HTOP_UPDATE_PANELHDR ; 

Htop_Reaction Action_setSortKey(Settings* settings, ProcessField sortKey) {
   settings->sortKey = sortKey;
   settings->direction = 1;
   settings->treeView = false;
   return HTOP_REFRESH | HTOP_SAVE_SETTINGS | HTOP_UPDATE_PANELHDR | HTOP_KEEP_FOLLOWING;
}