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
struct TYPE_3__ {int /*<<< orphan*/  panel; int /*<<< orphan*/  header; int /*<<< orphan*/  pl; int /*<<< orphan*/  settings; } ;
typedef  TYPE_1__ State ;
typedef  int Htop_Reaction ;

/* Variables and functions */
 int /*<<< orphan*/  Action_runSetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COLS ; 
 int HTOP_REDRAW_BAR ; 
 int HTOP_REFRESH ; 
 int HTOP_UPDATE_PANELHDR ; 
 int Header_calculateHeight (int /*<<< orphan*/ ) ; 
 int LINES ; 
 int /*<<< orphan*/  Panel_move (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Panel_resize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static Htop_Reaction actionSetup(State* st) {
   Action_runSetup(st->settings, st->header, st->pl);
   // TODO: shouldn't need this, colors should be dynamic
   int headerHeight = Header_calculateHeight(st->header);
   Panel_move(st->panel, 0, headerHeight);
   Panel_resize(st->panel, COLS, LINES-headerHeight-1);
   return HTOP_REFRESH | HTOP_REDRAW_BAR | HTOP_UPDATE_PANELHDR;
}