#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_18__ ;
typedef  struct TYPE_22__   TYPE_17__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  double color_type ;
struct TYPE_27__ {TYPE_10__* screen; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; int /*<<< orphan*/  ystart; int /*<<< orphan*/  xstart; int /*<<< orphan*/  gvao_idx; int /*<<< orphan*/  vao_idx; } ;
struct TYPE_28__ {double last_drag_scroll_at; unsigned int id; int cursor_visible_at_last_render; scalar_t__ last_cursor_x; scalar_t__ last_cursor_y; scalar_t__ last_cursor_shape; TYPE_4__ render_data; scalar_t__ visible; } ;
typedef  TYPE_5__ Window ;
struct TYPE_29__ {unsigned int num_windows; unsigned int active_window; TYPE_5__* windows; } ;
typedef  TYPE_6__ Tab ;
struct TYPE_24__ {TYPE_10__* screen; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; int /*<<< orphan*/  ystart; int /*<<< orphan*/  xstart; int /*<<< orphan*/  vao_idx; } ;
struct TYPE_30__ {int needs_render; double num_tabs; int tab_bar_data_updated; double last_mouse_activity_at; int active_tab; TYPE_6__* tabs; TYPE_1__ tab_bar_render_data; int /*<<< orphan*/  id; } ;
struct TYPE_26__ {int /*<<< orphan*/  default_bg; } ;
struct TYPE_25__ {int /*<<< orphan*/  default_bg; } ;
struct TYPE_23__ {int is_visible; scalar_t__ x; scalar_t__ y; scalar_t__ shape; } ;
struct TYPE_22__ {TYPE_3__ configured; TYPE_2__ overridden; } ;
struct TYPE_21__ {scalar_t__ start_visual_bell_at; TYPE_18__ cursor_render_info; TYPE_17__* color_profile; } ;
typedef  TYPE_7__ OSWindow ;

/* Variables and functions */
 double OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  background ; 
 int /*<<< orphan*/  call_boss (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  collect_cursor_info (TYPE_18__*,TYPE_5__*,double,TYPE_7__*) ; 
 double colorprofile_to_color (TYPE_17__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ drag_scroll (TYPE_5__*,TYPE_7__*) ; 
 int /*<<< orphan*/  hide_mouse (TYPE_7__*) ; 
 int /*<<< orphan*/  is_mouse_hidden (TYPE_7__*) ; 
 int /*<<< orphan*/  mouse_hide_wait ; 
 scalar_t__ send_cell_data_to_gpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_10__*,TYPE_7__*) ; 
 int /*<<< orphan*/  set_maximum_wait (double) ; 
 int /*<<< orphan*/  tab_bar_min_tabs ; 
 int /*<<< orphan*/  update_tab_bar_data ; 
 int /*<<< orphan*/  update_window_title (TYPE_5__*,TYPE_7__*) ; 

__attribute__((used)) static inline bool
prepare_to_render_os_window(OSWindow *os_window, double now, unsigned int *active_window_id, color_type *active_window_bg, unsigned int *num_visible_windows) {
#define TD os_window->tab_bar_render_data
    bool needs_render = os_window->needs_render;
    os_window->needs_render = false;
    if (TD.screen && os_window->num_tabs >= OPT(tab_bar_min_tabs)) {
        if (!os_window->tab_bar_data_updated) {
            call_boss(update_tab_bar_data, "K", os_window->id);
            os_window->tab_bar_data_updated = true;
        }
        if (send_cell_data_to_gpu(TD.vao_idx, 0, TD.xstart, TD.ystart, TD.dx, TD.dy, TD.screen, os_window)) needs_render = true;
    }
    if (OPT(mouse_hide_wait) > 0 && !is_mouse_hidden(os_window)) {
        if (now - os_window->last_mouse_activity_at >= OPT(mouse_hide_wait)) hide_mouse(os_window);
        else set_maximum_wait(OPT(mouse_hide_wait) - now + os_window->last_mouse_activity_at);
    }
    Tab *tab = os_window->tabs + os_window->active_tab;
    *active_window_bg = OPT(background);
    for (unsigned int i = 0; i < tab->num_windows; i++) {
        Window *w = tab->windows + i;
#define WD w->render_data
        if (w->visible && WD.screen) {
            *num_visible_windows += 1;
            if (w->last_drag_scroll_at > 0) {
                if (now - w->last_drag_scroll_at >= 0.02) {
                    if (drag_scroll(w, os_window)) {
                        w->last_drag_scroll_at = now;
                        set_maximum_wait(0.02);
                        needs_render = true;
                    } else w->last_drag_scroll_at = 0;
                } else set_maximum_wait(now - w->last_drag_scroll_at);
            }
            bool is_active_window = i == tab->active_window;
            if (is_active_window) {
                *active_window_id = w->id;
                collect_cursor_info(&WD.screen->cursor_render_info, w, now, os_window);
                if (w->cursor_visible_at_last_render != WD.screen->cursor_render_info.is_visible || w->last_cursor_x != WD.screen->cursor_render_info.x || w->last_cursor_y != WD.screen->cursor_render_info.y || w->last_cursor_shape != WD.screen->cursor_render_info.shape) needs_render = true;
                update_window_title(w, os_window);
                *active_window_bg = colorprofile_to_color(WD.screen->color_profile, WD.screen->color_profile->overridden.default_bg, WD.screen->color_profile->configured.default_bg);
            } else WD.screen->cursor_render_info.is_visible = false;
            if (send_cell_data_to_gpu(WD.vao_idx, WD.gvao_idx, WD.xstart, WD.ystart, WD.dx, WD.dy, WD.screen, os_window)) needs_render = true;
            if (WD.screen->start_visual_bell_at != 0) needs_render = true;
        }
    }
    return needs_render;
}