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
struct TYPE_7__ {TYPE_1__* settings; } ;
struct TYPE_6__ {scalar_t__ treeView; } ;
typedef  TYPE_2__ State ;
typedef  int /*<<< orphan*/  Htop_Reaction ;

/* Variables and functions */
 int /*<<< orphan*/  actionExpandOrCollapse (TYPE_2__*) ; 
 int /*<<< orphan*/  actionSetSortColumn (TYPE_2__*) ; 

__attribute__((used)) static Htop_Reaction actionExpandCollapseOrSortColumn(State* st) {
   return st->settings->treeView ? actionExpandOrCollapse(st) : actionSetSortColumn(st);
}