#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_window_t ;
struct TYPE_5__ {int /*<<< orphan*/  sequence; } ;
typedef  TYPE_1__ xcb_void_cookie_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct TYPE_6__ {int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ Rect ;

/* Variables and functions */
 int XCB_CONFIG_WINDOW_HEIGHT ; 
 int XCB_CONFIG_WINDOW_WIDTH ; 
 int XCB_CONFIG_WINDOW_X ; 
 int XCB_CONFIG_WINDOW_Y ; 
 int /*<<< orphan*/  add_ignore_event (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ xcb_configure_window (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void xcb_set_window_rect(xcb_connection_t *conn, xcb_window_t window, Rect r) {
    xcb_void_cookie_t cookie;
    cookie = xcb_configure_window(conn, window,
                                  XCB_CONFIG_WINDOW_X |
                                      XCB_CONFIG_WINDOW_Y |
                                      XCB_CONFIG_WINDOW_WIDTH |
                                      XCB_CONFIG_WINDOW_HEIGHT,
                                  &(r.x));
    /* ignore events which are generated because we configured a window */
    add_ignore_event(cookie.sequence, -1);
}