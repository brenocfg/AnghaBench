#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  window; int /*<<< orphan*/  sequence; } ;
typedef  TYPE_1__ xcb_map_request_event_t ;
typedef  int /*<<< orphan*/  xcb_get_window_attributes_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_ignore_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  manage_window (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xcb_get_window_attributes_unchecked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_map_request(xcb_map_request_event_t *event) {
    xcb_get_window_attributes_cookie_t cookie;

    cookie = xcb_get_window_attributes_unchecked(conn, event->window);

    DLOG("window = 0x%08x, serial is %d.\n", event->window, event->sequence);
    add_ignore_event(event->sequence, -1);

    manage_window(event->window, cookie, false);
}