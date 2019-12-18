#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ y; } ;
struct TYPE_4__ {TYPE_3__* panel; } ;
typedef  TYPE_1__ State ;
typedef  int /*<<< orphan*/  Htop_Reaction ;

/* Variables and functions */
 int /*<<< orphan*/  COLS ; 
 int /*<<< orphan*/  HTOP_REDRAW_BAR ; 
 scalar_t__ LINES ; 
 int /*<<< orphan*/  Panel_resize (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  clear () ; 

__attribute__((used)) static Htop_Reaction actionResize(State* st) {
   clear();
   Panel_resize(st->panel, COLS, LINES-(st->panel->y)-1);
   return HTOP_REDRAW_BAR;
}