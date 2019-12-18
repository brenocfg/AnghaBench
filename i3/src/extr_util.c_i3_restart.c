#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  LOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHUTDOWN_REASON_RESTART ; 
 int /*<<< orphan*/ * add_argument (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  command_error_nagbar_pid ; 
 int /*<<< orphan*/  config_error_nagbar_pid ; 
 int /*<<< orphan*/  execvp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ get_debug_logging () ; 
 int /*<<< orphan*/  ipc_shutdown (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kill_nagbar (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  restore_geometry () ; 
 int /*<<< orphan*/ * start_argv ; 
 char* store_restart_layout () ; 

void i3_restart(bool forget_layout) {
    char *restart_filename = forget_layout ? NULL : store_restart_layout();

    kill_nagbar(&config_error_nagbar_pid, true);
    kill_nagbar(&command_error_nagbar_pid, true);

    restore_geometry();

    ipc_shutdown(SHUTDOWN_REASON_RESTART, -1);

    LOG("restarting \"%s\"...\n", start_argv[0]);
    /* make sure -a is in the argument list or add it */
    start_argv = add_argument(start_argv, "-a", NULL, NULL);

    /* make debuglog-on persist */
    if (get_debug_logging()) {
        start_argv = add_argument(start_argv, "-d", "all", NULL);
    }

    /* replace -r <file> so that the layout is restored */
    if (restart_filename != NULL) {
        start_argv = add_argument(start_argv, "--restart", restart_filename, "-r");
    }

    execvp(start_argv[0], start_argv);

    /* not reached */
}