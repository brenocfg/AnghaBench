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
struct TYPE_6__ {int /*<<< orphan*/  cell_y; int /*<<< orphan*/  cell_x; } ;
struct TYPE_5__ {int /*<<< orphan*/ * screen; } ;
struct TYPE_7__ {TYPE_2__ mouse_pos; TYPE_1__ render_data; } ;
typedef  TYPE_3__ Window ;
typedef  int /*<<< orphan*/  Screen ;

/* Variables and functions */
 scalar_t__ screen_has_selection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  screen_update_selection (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
extend_selection(Window *w) {
    Screen *screen = w->render_data.screen;
    if (screen_has_selection(screen)) {
        screen_update_selection(screen, w->mouse_pos.cell_x, w->mouse_pos.cell_y, true);
    }
}