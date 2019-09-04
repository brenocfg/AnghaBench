#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int terminate; scalar_t__ has_pending_closes; scalar_t__ has_pending_resizes; } ;
typedef  int /*<<< orphan*/  ChildMonitor ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  close_all_windows () ; 
 TYPE_1__ global_state ; 
 int maximum_wait ; 
 double monotonic () ; 
 int /*<<< orphan*/  parse_input (int /*<<< orphan*/ *) ; 
 int process_pending_closes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_pending_resizes (double) ; 
 int /*<<< orphan*/  render (double) ; 
 int /*<<< orphan*/  report_reaped_pids () ; 
 int /*<<< orphan*/  state_check_timer ; 
 int /*<<< orphan*/  stop_main_loop () ; 
 int /*<<< orphan*/  update_main_loop_timer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
process_global_state(void *data) {
    ChildMonitor *self = data;
    maximum_wait = -1;
    bool state_check_timer_enabled = false;

    double now = monotonic();
    if (global_state.has_pending_resizes) process_pending_resizes(now);
    render(now);
#ifdef __APPLE__
        if (cocoa_pending_actions) {
            if (cocoa_pending_actions & PREFERENCES_WINDOW) { call_boss(edit_config_file, NULL); }
            if (cocoa_pending_actions & NEW_OS_WINDOW) { call_boss(new_os_window, NULL); }
            if (cocoa_pending_actions_wd) {
                if (cocoa_pending_actions & NEW_OS_WINDOW_WITH_WD) { call_boss(new_os_window_with_wd, "s", cocoa_pending_actions_wd); }
                if (cocoa_pending_actions & NEW_TAB_WITH_WD) { call_boss(new_tab_with_wd, "s", cocoa_pending_actions_wd); }
                free(cocoa_pending_actions_wd);
                cocoa_pending_actions_wd = NULL;
            }
            cocoa_pending_actions = 0;
        }
#endif
    parse_input(self);
    if (global_state.terminate) {
        global_state.terminate = false;
        close_all_windows();
#ifdef __APPLE__
        request_application_quit();
#endif
    }
    report_reaped_pids();
    bool has_open_windows = true;
    if (global_state.has_pending_closes) has_open_windows = process_pending_closes(self);
    if (has_open_windows) {
        if (maximum_wait >= 0) {
            state_check_timer_enabled = true;
        }
    } else {
        stop_main_loop();
    }
    update_main_loop_timer(state_check_timer, MAX(0, maximum_wait), state_check_timer_enabled);
}