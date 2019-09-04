#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int has_pending_resizes; TYPE_2__* callback_os_window; } ;
struct TYPE_5__ {int in_progress; int /*<<< orphan*/  num_of_resize_events; void* height; void* width; int /*<<< orphan*/  last_resize_event_at; } ;
struct TYPE_6__ {int /*<<< orphan*/  offscreen_texture_id; TYPE_1__ live_resize; } ;
typedef  TYPE_2__ OSWindow ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 void* MAX (int /*<<< orphan*/ ,int) ; 
 TYPE_4__ global_state ; 
 int /*<<< orphan*/  log_error (char*,int,int) ; 
 int /*<<< orphan*/  make_os_window_context_current (TYPE_2__*) ; 
 int min_height ; 
 int min_width ; 
 int /*<<< orphan*/  monotonic () ; 
 int /*<<< orphan*/  request_tick_callback () ; 
 int /*<<< orphan*/  set_callback_window (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_surface_size (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
framebuffer_size_callback(GLFWwindow *w, int width, int height) {
    if (!set_callback_window(w)) return;
    if (width >= min_width && height >= min_height) {
        OSWindow *window = global_state.callback_os_window;
        global_state.has_pending_resizes = true;
        window->live_resize.in_progress = true;
        window->live_resize.last_resize_event_at = monotonic();
        window->live_resize.width = MAX(0, width); window->live_resize.height = MAX(0, height);
        window->live_resize.num_of_resize_events++;
        make_os_window_context_current(window);
        update_surface_size(width, height, window->offscreen_texture_id);
        request_tick_callback();
    } else log_error("Ignoring resize request for tiny size: %dx%d", width, height);
    global_state.callback_os_window = NULL;
}