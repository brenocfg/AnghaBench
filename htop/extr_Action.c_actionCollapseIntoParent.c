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
struct TYPE_5__ {int /*<<< orphan*/  panel; TYPE_1__* settings; } ;
struct TYPE_4__ {int /*<<< orphan*/  treeView; } ;
typedef  TYPE_2__ State ;
typedef  int /*<<< orphan*/  Htop_Reaction ;

/* Variables and functions */
 int /*<<< orphan*/  HTOP_OK ; 
 int /*<<< orphan*/  HTOP_RECALCULATE ; 
 int collapseIntoParent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Htop_Reaction actionCollapseIntoParent(State* st) {
   if (!st->settings->treeView) {
      return HTOP_OK;
   }
   bool changed = collapseIntoParent(st->panel);
   return changed ? HTOP_RECALCULATE : HTOP_OK;
}