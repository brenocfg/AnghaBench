#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* xcb_window_t ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ xcb_rectangle_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct TYPE_5__ {int border_width; int override_redirect; int /*<<< orphan*/  above_sibling; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  response_type; void* window; void* event; } ;
typedef  TYPE_2__ xcb_configure_notify_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  XCB_CONFIGURE_NOTIFY ; 
 int /*<<< orphan*/  XCB_EVENT_MASK_STRUCTURE_NOTIFY ; 
 int /*<<< orphan*/  XCB_NONE ; 
 int /*<<< orphan*/  free (void*) ; 
 void* scalloc (int,int) ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_send_event (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ,char*) ; 

void fake_configure_notify(xcb_connection_t *conn, xcb_rectangle_t r, xcb_window_t window, int border_width) {
    /* Every X11 event is 32 bytes long. Therefore, XCB will copy 32 bytes.
     * In order to properly initialize these bytes, we allocate 32 bytes even
     * though we only need less for an xcb_configure_notify_event_t */
    void *event = scalloc(32, 1);
    xcb_configure_notify_event_t *generated_event = event;

    generated_event->event = window;
    generated_event->window = window;
    generated_event->response_type = XCB_CONFIGURE_NOTIFY;

    generated_event->x = r.x;
    generated_event->y = r.y;
    generated_event->width = r.width;
    generated_event->height = r.height;

    generated_event->border_width = border_width;
    generated_event->above_sibling = XCB_NONE;
    generated_event->override_redirect = false;

    xcb_send_event(conn, false, window, XCB_EVENT_MASK_STRUCTURE_NOTIFY, (char *)generated_event);
    xcb_flush(conn);

    free(event);
}