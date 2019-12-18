#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_7__ {int slk_format; TYPE_2__* _slk; } ;
struct TYPE_6__ {int maxlab; TYPE_1__* ent; } ;
struct TYPE_5__ {int /*<<< orphan*/  ent_x; } ;
typedef  TYPE_3__ SCREEN ;

/* Variables and functions */
 TYPE_3__* _nc_screen_of (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getmaxx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvwhline (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
slk_paint_info(WINDOW *win)
{
    SCREEN *sp = _nc_screen_of(win);

    if (win && sp && (sp->slk_format == 4)) {
	int i;

	(void) mvwhline(win, 0, 0, 0, getmaxx(win));
	wmove(win, 0, 0);

	for (i = 0; i < sp->_slk->maxlab; i++) {
	    mvwprintw(win, 0, sp->_slk->ent[i].ent_x, "F%d", i + 1);
	}
    }
}