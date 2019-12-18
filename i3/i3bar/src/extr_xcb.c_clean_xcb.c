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
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cursor ; 
 int /*<<< orphan*/  ev_io_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_prepare_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_font () ; 
 int /*<<< orphan*/  free_outputs () ; 
 int /*<<< orphan*/  main_loop ; 
 int /*<<< orphan*/  xcb_aux_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_connection ; 
 int /*<<< orphan*/  xcb_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_free_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_io ; 
 int /*<<< orphan*/  xcb_prep ; 

void clean_xcb(void) {
    free_outputs();

    free_font();

    xcb_free_cursor(xcb_connection, cursor);
    xcb_flush(xcb_connection);
    xcb_aux_sync(xcb_connection);
    xcb_disconnect(xcb_connection);

    ev_prepare_stop(main_loop, xcb_prep);
    ev_io_stop(main_loop, xcb_io);

    FREE(xcb_prep);
    FREE(xcb_io);
}