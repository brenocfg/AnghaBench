#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_16__ ;
typedef  struct TYPE_19__   TYPE_15__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  color_type ;
struct TYPE_23__ {int /*<<< orphan*/  last_cursor_shape; int /*<<< orphan*/  last_cursor_y; int /*<<< orphan*/  last_cursor_x; int /*<<< orphan*/  cursor_visible_at_last_render; scalar_t__ visible; } ;
typedef  TYPE_3__ Window ;
struct TYPE_26__ {int is_dirty; int /*<<< orphan*/  rect_buf; int /*<<< orphan*/  num_border_rects; int /*<<< orphan*/  vao_idx; } ;
struct TYPE_24__ {unsigned int num_windows; unsigned int active_window; TYPE_3__* windows; TYPE_6__ border_rects; } ;
typedef  TYPE_4__ Tab ;
struct TYPE_25__ {int active_tab; scalar_t__ num_tabs; int last_active_tab; scalar_t__ last_num_tabs; unsigned int last_active_window_id; int is_damaged; int /*<<< orphan*/  is_focused; int /*<<< orphan*/  focused_at_last_render; int /*<<< orphan*/  viewport_height; int /*<<< orphan*/  viewport_width; TYPE_4__* tabs; int /*<<< orphan*/  clear_count; } ;
struct TYPE_22__ {int /*<<< orphan*/  shape; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  is_visible; } ;
struct TYPE_21__ {double visual_bell_duration; } ;
struct TYPE_20__ {TYPE_11__* screen; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; int /*<<< orphan*/  ystart; int /*<<< orphan*/  xstart; int /*<<< orphan*/  vao_idx; } ;
struct TYPE_19__ {TYPE_11__* screen; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; int /*<<< orphan*/  ystart; int /*<<< orphan*/  xstart; int /*<<< orphan*/  gvao_idx; int /*<<< orphan*/  vao_idx; } ;
struct TYPE_18__ {double start_visual_bell_at; TYPE_2__ cursor_render_info; } ;
struct TYPE_17__ {TYPE_1__ opts; } ;
typedef  TYPE_5__ OSWindow ;
typedef  TYPE_6__ BorderRects ;

/* Variables and functions */
 scalar_t__ OPT (int /*<<< orphan*/ ) ; 
 TYPE_16__ TD ; 
 scalar_t__ USE_RENDER_FRAMES ; 
 TYPE_15__ WD ; 
 int /*<<< orphan*/  blank_os_window (TYPE_5__*) ; 
 int /*<<< orphan*/  draw_borders (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,TYPE_5__*) ; 
 int /*<<< orphan*/  draw_cells (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_11__*,TYPE_5__*,int,int) ; 
 TYPE_10__ global_state ; 
 int /*<<< orphan*/  request_frame_render (TYPE_5__*) ; 
 int /*<<< orphan*/  set_maximum_wait (double) ; 
 int /*<<< orphan*/  swap_window_buffers (TYPE_5__*) ; 
 int /*<<< orphan*/  tab_bar_min_tabs ; 

__attribute__((used)) static inline void
render_os_window(OSWindow *os_window, double now, unsigned int active_window_id, color_type active_window_bg, unsigned int num_visible_windows) {
    // ensure all pixels are cleared to background color at least once in every buffer
    if (os_window->clear_count++ < 3) blank_os_window(os_window);
    Tab *tab = os_window->tabs + os_window->active_tab;
    BorderRects *br = &tab->border_rects;
    draw_borders(br->vao_idx, br->num_border_rects, br->rect_buf, br->is_dirty, os_window->viewport_width, os_window->viewport_height, active_window_bg, num_visible_windows, os_window);
    if (TD.screen && os_window->num_tabs >= OPT(tab_bar_min_tabs)) draw_cells(TD.vao_idx, 0, TD.xstart, TD.ystart, TD.dx, TD.dy, TD.screen, os_window, true, false);
    for (unsigned int i = 0; i < tab->num_windows; i++) {
        Window *w = tab->windows + i;
        if (w->visible && WD.screen) {
            bool is_active_window = i == tab->active_window;
            draw_cells(WD.vao_idx, WD.gvao_idx, WD.xstart, WD.ystart, WD.dx, WD.dy, WD.screen, os_window, is_active_window, true);
            if (WD.screen->start_visual_bell_at != 0) {
                double bell_left = global_state.opts.visual_bell_duration - (now - WD.screen->start_visual_bell_at);
                set_maximum_wait(bell_left);
            }
            w->cursor_visible_at_last_render = WD.screen->cursor_render_info.is_visible; w->last_cursor_x = WD.screen->cursor_render_info.x; w->last_cursor_y = WD.screen->cursor_render_info.y; w->last_cursor_shape = WD.screen->cursor_render_info.shape;
        }
    }
    swap_window_buffers(os_window);
    br->is_dirty = false;
    os_window->last_active_tab = os_window->active_tab; os_window->last_num_tabs = os_window->num_tabs; os_window->last_active_window_id = active_window_id;
    os_window->focused_at_last_render = os_window->is_focused;
    os_window->is_damaged = false;
    if (USE_RENDER_FRAMES) request_frame_render(os_window);
#undef WD
#undef TD
}