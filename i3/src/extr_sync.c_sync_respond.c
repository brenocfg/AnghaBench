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
typedef  void* xcb_window_t ;
struct TYPE_3__ {void** data32; } ;
struct TYPE_4__ {int format; TYPE_1__ data; int /*<<< orphan*/  type; void* window; int /*<<< orphan*/  response_type; } ;
typedef  TYPE_2__ xcb_client_message_event_t ;
typedef  void* uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_I3_SYNC ; 
 int /*<<< orphan*/  DLOG (char*,void*,void*) ; 
 int /*<<< orphan*/  XCB_CLIENT_MESSAGE ; 
 int /*<<< orphan*/  XCB_EVENT_MASK_NO_EVENT ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  free (void*) ; 
 void* scalloc (int,int) ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_send_event (int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ,char*) ; 

void sync_respond(xcb_window_t window, uint32_t rnd) {
    DLOG("[i3 sync protocol] Sending random value %d back to X11 window 0x%08x\n", rnd, window);

    void *reply = scalloc(32, 1);
    xcb_client_message_event_t *ev = reply;

    ev->response_type = XCB_CLIENT_MESSAGE;
    ev->window = window;
    ev->type = A_I3_SYNC;
    ev->format = 32;
    ev->data.data32[0] = window;
    ev->data.data32[1] = rnd;

    xcb_send_event(conn, false, window, XCB_EVENT_MASK_NO_EVENT, (char *)ev);
    xcb_flush(conn);
    free(reply);
}