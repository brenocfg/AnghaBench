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
struct TYPE_5__ {scalar_t__ panel; TYPE_1__* pl; } ;
struct TYPE_4__ {int /*<<< orphan*/  following; } ;
typedef  TYPE_2__ State ;
typedef  int /*<<< orphan*/  MainPanel ;
typedef  int /*<<< orphan*/  Htop_Reaction ;

/* Variables and functions */
 int /*<<< orphan*/ * CRT_colors ; 
 int /*<<< orphan*/  HTOP_KEEP_FOLLOWING ; 
 int /*<<< orphan*/  MainPanel_selectedPid (int /*<<< orphan*/ *) ; 
 size_t PANEL_SELECTION_FOLLOW ; 
 int /*<<< orphan*/  Panel_setSelectionColor (scalar_t__,int /*<<< orphan*/ ) ; 

Htop_Reaction Action_follow(State* st) {
   st->pl->following = MainPanel_selectedPid((MainPanel*)st->panel);
   Panel_setSelectionColor(st->panel, CRT_colors[PANEL_SELECTION_FOLLOW]);
   return HTOP_KEEP_FOLLOWING;
}