#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  cell_y; int /*<<< orphan*/  cell_x; } ;
struct TYPE_10__ {TYPE_5__* screen; } ;
struct TYPE_13__ {TYPE_3__ mouse_pos; scalar_t__ id; scalar_t__ last_drag_scroll_at; TYPE_1__ render_data; } ;
typedef  TYPE_4__ Window ;
struct TYPE_15__ {scalar_t__ active_drag_in_window; } ;
struct TYPE_11__ {scalar_t__ in_progress; } ;
struct TYPE_14__ {TYPE_2__ selection; } ;
typedef  TYPE_5__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  EXTEND_CELL ; 
 int GLFW_MOD_SHIFT ; 
 scalar_t__ OPT (int /*<<< orphan*/ ) ; 
 TYPE_9__ global_state ; 
 int /*<<< orphan*/  rectangle_select_modifiers ; 
 int /*<<< orphan*/  screen_start_selection (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_update_selection (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
update_drag(bool from_button, Window *w, bool is_release, int modifiers) {
    Screen *screen = w->render_data.screen;
    if (from_button) {
        if (is_release) {
            global_state.active_drag_in_window = 0;
            w->last_drag_scroll_at = 0;
            if (screen->selection.in_progress)
                screen_update_selection(screen, w->mouse_pos.cell_x, w->mouse_pos.cell_y, true);
        }
        else {
            global_state.active_drag_in_window = w->id;
            screen_start_selection(screen, w->mouse_pos.cell_x, w->mouse_pos.cell_y, modifiers == (int)OPT(rectangle_select_modifiers) || modifiers == ((int)OPT(rectangle_select_modifiers) | GLFW_MOD_SHIFT), EXTEND_CELL);
        }
    } else if (screen->selection.in_progress) {
        screen_update_selection(screen, w->mouse_pos.cell_x, w->mouse_pos.cell_y, false);
    }
}