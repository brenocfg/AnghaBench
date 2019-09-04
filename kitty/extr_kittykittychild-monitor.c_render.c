#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  color_type ;
struct TYPE_14__ {scalar_t__ in_progress; } ;
struct TYPE_15__ {scalar_t__ render_state; int is_damaged; int viewport_size_dirty; unsigned int last_active_window_id; scalar_t__ last_active_tab; scalar_t__ active_tab; scalar_t__ focused_at_last_render; scalar_t__ is_focused; int /*<<< orphan*/  id; int /*<<< orphan*/  fonts_data; int /*<<< orphan*/  offscreen_texture_id; int /*<<< orphan*/  viewport_height; int /*<<< orphan*/  viewport_width; scalar_t__ clear_count; TYPE_1__ live_resize; int /*<<< orphan*/  num_tabs; } ;
struct TYPE_13__ {size_t num_os_windows; TYPE_2__* os_windows; } ;
typedef  TYPE_2__ OSWindow ;

/* Variables and functions */
 double OPT (int /*<<< orphan*/ ) ; 
 scalar_t__ RENDER_FRAME_NOT_REQUESTED ; 
 scalar_t__ RENDER_FRAME_READY ; 
 scalar_t__ USE_RENDER_FRAMES ; 
 int /*<<< orphan*/  blank_os_window (TYPE_2__*) ; 
 int /*<<< orphan*/  draw_resizing_text (TYPE_2__*) ; 
 TYPE_10__ global_state ; 
 double last_render_at ; 
 int /*<<< orphan*/  log_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_os_window_context_current (TYPE_2__*) ; 
 scalar_t__ prepare_to_render_os_window (TYPE_2__*,double,unsigned int*,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  render_os_window (TYPE_2__*,double,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  repaint_delay ; 
 int /*<<< orphan*/  request_frame_render (TYPE_2__*) ; 
 int /*<<< orphan*/  set_maximum_wait (double) ; 
 int /*<<< orphan*/  should_os_window_be_rendered (TYPE_2__*) ; 
 int /*<<< orphan*/  swap_window_buffers (TYPE_2__*) ; 
 int /*<<< orphan*/  update_os_window_title (TYPE_2__*) ; 
 int /*<<< orphan*/  update_surface_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
render(double now) {
    double time_since_last_render = now - last_render_at;
    if (time_since_last_render < OPT(repaint_delay)) {
        set_maximum_wait(OPT(repaint_delay) - time_since_last_render);
        return;
    }

    for (size_t i = 0; i < global_state.num_os_windows; i++) {
        OSWindow *w = global_state.os_windows + i;
        if (!w->num_tabs) continue;
        if (!should_os_window_be_rendered(w)) {
            update_os_window_title(w);
            continue;
        }
        if (USE_RENDER_FRAMES && w->render_state != RENDER_FRAME_READY) {
            if (w->render_state == RENDER_FRAME_NOT_REQUESTED) request_frame_render(w);
            continue;
        }
        make_os_window_context_current(w);
        if (w->live_resize.in_progress) {
            blank_os_window(w);
            draw_resizing_text(w);
            swap_window_buffers(w);
            if (USE_RENDER_FRAMES) request_frame_render(w);
            continue;
        }
        bool needs_render = w->is_damaged;
        if (w->viewport_size_dirty) {
            w->clear_count = 0;
            update_surface_size(w->viewport_width, w->viewport_height, w->offscreen_texture_id);
            w->viewport_size_dirty = false;
            needs_render = true;
        }
        unsigned int active_window_id = 0, num_visible_windows = 0;
        color_type active_window_bg = 0;
        if (!w->fonts_data) { log_error("No fonts data found for window id: %llu", w->id); continue; }
        if (prepare_to_render_os_window(w, now, &active_window_id, &active_window_bg, &num_visible_windows)) needs_render = true;
        if (w->last_active_window_id != active_window_id || w->last_active_tab != w->active_tab || w->focused_at_last_render != w->is_focused) needs_render = true;
        if (needs_render) render_os_window(w, now, active_window_id, active_window_bg, num_visible_windows);
    }
    last_render_at = now;
#undef TD
}