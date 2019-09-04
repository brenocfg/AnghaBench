#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t num_windows; TYPE_1__* windows; } ;
typedef  TYPE_2__ Tab ;
struct TYPE_10__ {int has_pending_closes; size_t num_os_windows; TYPE_3__* os_windows; } ;
struct TYPE_9__ {size_t num_tabs; int /*<<< orphan*/  id; TYPE_2__* tabs; int /*<<< orphan*/  window_height; int /*<<< orphan*/  window_width; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ OSWindow ;
typedef  int /*<<< orphan*/  ChildMonitor ;

/* Variables and functions */
 int /*<<< orphan*/  call_boss (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_os_window (TYPE_3__*) ; 
 TYPE_5__ global_state ; 
 int /*<<< orphan*/  mark_child_for_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_os_window_closed ; 
 int /*<<< orphan*/  remove_os_window (int /*<<< orphan*/ ) ; 
 scalar_t__ should_os_window_close (TYPE_3__*) ; 

__attribute__((used)) static inline bool
process_pending_closes(ChildMonitor *self) {
    global_state.has_pending_closes = false;
    bool has_open_windows = false;
    for (size_t w = global_state.num_os_windows; w > 0; w--) {
        OSWindow *os_window = global_state.os_windows + w - 1;
        if (should_os_window_close(os_window)) {
            destroy_os_window(os_window);
            call_boss(on_os_window_closed, "Kii", os_window->id, os_window->window_width, os_window->window_height);
            for (size_t t=0; t < os_window->num_tabs; t++) {
                Tab *tab = os_window->tabs + t;
                for (size_t w = 0; w < tab->num_windows; w++) mark_child_for_close(self, tab->windows[w].id);
            }
            remove_os_window(os_window->id);
        } else has_open_windows = true;
    }
#ifdef __APPLE__
    if (!OPT(macos_quit_when_last_window_closed)) {
        if (!has_open_windows && !application_quit_requested()) has_open_windows = true;
    }
#endif
    return has_open_windows;
}