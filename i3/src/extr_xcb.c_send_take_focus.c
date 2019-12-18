#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_window_t ;
typedef  int /*<<< orphan*/  xcb_timestamp_t ;
struct TYPE_3__ {int /*<<< orphan*/ * data32; } ;
struct TYPE_4__ {int format; TYPE_1__ data; int /*<<< orphan*/  type; int /*<<< orphan*/  window; int /*<<< orphan*/  response_type; } ;
typedef  TYPE_2__ xcb_client_message_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_WM_PROTOCOLS ; 
 int /*<<< orphan*/  A_WM_TAKE_FOCUS ; 
 int /*<<< orphan*/  DLOG (char*) ; 
 int /*<<< orphan*/  XCB_CLIENT_MESSAGE ; 
 int /*<<< orphan*/  XCB_EVENT_MASK_NO_EVENT ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  free (void*) ; 
 void* scalloc (int,int) ; 
 int /*<<< orphan*/  xcb_send_event (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void send_take_focus(xcb_window_t window, xcb_timestamp_t timestamp) {
    /* Every X11 event is 32 bytes long. Therefore, XCB will copy 32 bytes.
     * In order to properly initialize these bytes, we allocate 32 bytes even
     * though we only need less for an xcb_configure_notify_event_t */
    void *event = scalloc(32, 1);
    xcb_client_message_event_t *ev = event;

    ev->response_type = XCB_CLIENT_MESSAGE;
    ev->window = window;
    ev->type = A_WM_PROTOCOLS;
    ev->format = 32;
    ev->data.data32[0] = A_WM_TAKE_FOCUS;
    ev->data.data32[1] = timestamp;

    DLOG("Sending WM_TAKE_FOCUS to the client\n");
    xcb_send_event(conn, false, window, XCB_EVENT_MASK_NO_EVENT, (char *)ev);
    free(event);
}