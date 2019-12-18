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
struct TYPE_2__ {int /*<<< orphan*/  ipc_socket_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHUTDOWN_REASON_EXIT ; 
 int /*<<< orphan*/  __lsan_do_leak_check () ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  ev_loop_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ipc_shutdown (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  main_loop ; 
 int /*<<< orphan*/  shm_unlink (char*) ; 
 char* shmlogname ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_disconnect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i3_exit(void) {
    if (*shmlogname != '\0') {
        fprintf(stderr, "Closing SHM log \"%s\"\n", shmlogname);
        fflush(stderr);
        shm_unlink(shmlogname);
    }
    ipc_shutdown(SHUTDOWN_REASON_EXIT, -1);
    unlink(config.ipc_socket_path);
    xcb_disconnect(conn);

/* We need ev >= 4 for the following code. Since it is not *that* important (it
 * only makes sure that there are no i3-nagbar instances left behind) we still
 * support old systems with libev 3. */
#if EV_VERSION_MAJOR >= 4
    ev_loop_destroy(main_loop);
#endif

#ifdef I3_ASAN_ENABLED
    __lsan_do_leak_check();
#endif
}