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
typedef  int pid_t ;
typedef  int /*<<< orphan*/  ChildMonitor ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  WNOHANG ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  mark_child_for_removal (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mark_monitored_pids (int,int) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
reap_children(ChildMonitor *self, bool enable_close_on_child_death) {
    int status;
    pid_t pid;
    (void)self;
    while(true) {
        pid = waitpid(-1, &status, WNOHANG);
        if (pid == -1) {
            if (errno != EINTR) break;
        } else if (pid > 0) {
            if (enable_close_on_child_death) mark_child_for_removal(self, pid);
            mark_monitored_pids(pid, status);
        } else break;
    }
}