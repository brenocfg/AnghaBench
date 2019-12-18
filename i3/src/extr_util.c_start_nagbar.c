#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int pid_t ;
struct TYPE_7__ {int* data; } ;
typedef  TYPE_1__ ev_cleanup ;
struct TYPE_8__ {int* data; } ;
typedef  TYPE_2__ ev_child ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,int) ; 
 int /*<<< orphan*/  ev_child_init (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_child_start (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ev_cleanup_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_cleanup_start (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  exec_i3_utility (char*,char**) ; 
 int fork () ; 
 int /*<<< orphan*/  main_loop ; 
 int /*<<< orphan*/  nagbar_cleanup ; 
 int /*<<< orphan*/  nagbar_exited ; 
 void* smalloc (int) ; 
 int /*<<< orphan*/  warn (char*) ; 

void start_nagbar(pid_t *nagbar_pid, char *argv[]) {
    if (*nagbar_pid != -1) {
        DLOG("i3-nagbar already running (PID %d), not starting again.\n", *nagbar_pid);
        return;
    }

    *nagbar_pid = fork();
    if (*nagbar_pid == -1) {
        warn("Could not fork()");
        return;
    }

    /* child */
    if (*nagbar_pid == 0)
        exec_i3_utility("i3-nagbar", argv);

    DLOG("Starting i3-nagbar with PID %d\n", *nagbar_pid);

    /* parent */
    /* install a child watcher */
    ev_child *child = smalloc(sizeof(ev_child));
    ev_child_init(child, &nagbar_exited, *nagbar_pid, 0);
    child->data = nagbar_pid;
    ev_child_start(main_loop, child);

    /* install a cleanup watcher (will be called when i3 exits and i3-nagbar is
     * still running) */
    ev_cleanup *cleanup = smalloc(sizeof(ev_cleanup));
    ev_cleanup_init(cleanup, nagbar_cleanup);
    cleanup->data = nagbar_pid;
    ev_cleanup_start(main_loop, cleanup);
}