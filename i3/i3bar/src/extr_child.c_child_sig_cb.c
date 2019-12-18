#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ev_loop {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rstatus; } ;
typedef  TYPE_1__ ev_child ;
struct TYPE_5__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELOG (char*,int /*<<< orphan*/ ,int) ; 
 int WEXITSTATUS (int /*<<< orphan*/ ) ; 
 TYPE_3__ child ; 
 int /*<<< orphan*/  cleanup () ; 
 int /*<<< orphan*/  draw_bars (int) ; 
 int /*<<< orphan*/  set_statusline_error (char*,int) ; 

__attribute__((used)) static void child_sig_cb(struct ev_loop *loop, ev_child *watcher, int revents) {
    int exit_status = WEXITSTATUS(watcher->rstatus);

    ELOG("Child (pid: %d) unexpectedly exited with status %d\n",
         child.pid,
         exit_status);

    /* this error is most likely caused by a user giving a nonexecutable or
     * nonexistent file, so we will handle those cases separately. */
    if (exit_status == 126)
        set_statusline_error("status_command is not executable (exit %d)", exit_status);
    else if (exit_status == 127)
        set_statusline_error("status_command not found or is missing a library dependency (exit %d)", exit_status);
    else
        set_statusline_error("status_command process exited unexpectedly (exit %d)", exit_status);

    cleanup();
    draw_bars(false);
}