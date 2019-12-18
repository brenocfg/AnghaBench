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
struct ev_prepare {int dummy; } ;
struct ev_io {int dummy; } ;
typedef  int /*<<< orphan*/  placeholder_state ;

/* Variables and functions */
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lsan_do_leak_check () ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ev_io_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_io_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ev_io_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ev_prepare_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_prepare_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ev_prepare_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  main_loop ; 
 int /*<<< orphan*/ * restore_conn ; 
 int /*<<< orphan*/  restore_xcb_got_event ; 
 int /*<<< orphan*/  restore_xcb_prepare_cb ; 
 int /*<<< orphan*/ * scalloc (int,int) ; 
 int /*<<< orphan*/  state_head ; 
 int /*<<< orphan*/ * xcb_connect (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ xcb_connection_has_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_get_file_descriptor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xcb_prepare ; 
 int /*<<< orphan*/ * xcb_watcher ; 

void restore_connect(void) {
    if (restore_conn != NULL) {
        /* This is not the initial connect, but a reconnect, most likely
         * because our X11 connection was killed (e.g. by a user with xkill. */
        ev_io_stop(main_loop, xcb_watcher);
        ev_prepare_stop(main_loop, xcb_prepare);

        placeholder_state *state;
        while (!TAILQ_EMPTY(&state_head)) {
            state = TAILQ_FIRST(&state_head);
            TAILQ_REMOVE(&state_head, state, state);
            free(state);
        }

        /* xcb_disconnect leaks memory in libxcb versions earlier than 1.11,
         * but it’s the right function to call. See
         * https://cgit.freedesktop.org/xcb/libxcb/commit/src/xcb_conn.c?id=4dcbfd77b
         */
        xcb_disconnect(restore_conn);
        free(xcb_watcher);
        free(xcb_prepare);
    }

    int screen;
    restore_conn = xcb_connect(NULL, &screen);
    if (restore_conn == NULL || xcb_connection_has_error(restore_conn)) {
        if (restore_conn != NULL) {
            xcb_disconnect(restore_conn);
        }
#ifdef I3_ASAN_ENABLED
        __lsan_do_leak_check();
#endif
        errx(EXIT_FAILURE, "Cannot open display");
    }

    xcb_watcher = scalloc(1, sizeof(struct ev_io));
    xcb_prepare = scalloc(1, sizeof(struct ev_prepare));

    ev_io_init(xcb_watcher, restore_xcb_got_event, xcb_get_file_descriptor(restore_conn), EV_READ);
    ev_io_start(main_loop, xcb_watcher);

    ev_prepare_init(xcb_prepare, restore_xcb_prepare_cb);
    ev_prepare_start(main_loop, xcb_prepare);
}