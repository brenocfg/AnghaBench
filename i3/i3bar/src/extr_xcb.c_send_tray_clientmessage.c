#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * data32; } ;
struct TYPE_5__ {int format; TYPE_1__ data; int /*<<< orphan*/  type; int /*<<< orphan*/  window; int /*<<< orphan*/  response_type; } ;
typedef  TYPE_2__ xcb_client_message_event_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  atom; } ;

/* Variables and functions */
 size_t MANAGER ; 
 int /*<<< orphan*/  XCB_CLIENT_MESSAGE ; 
 int /*<<< orphan*/  XCB_CURRENT_TIME ; 
 int /*<<< orphan*/ * atoms ; 
 int /*<<< orphan*/  selwin ; 
 TYPE_3__* tray_reply ; 
 int /*<<< orphan*/  xcb_connection ; 
 int /*<<< orphan*/  xcb_root ; 
 int /*<<< orphan*/  xcb_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static void send_tray_clientmessage(void) {
    uint8_t buffer[32] = {0};
    xcb_client_message_event_t *ev = (xcb_client_message_event_t *)buffer;

    ev->response_type = XCB_CLIENT_MESSAGE;
    ev->window = xcb_root;
    ev->type = atoms[MANAGER];
    ev->format = 32;
    ev->data.data32[0] = XCB_CURRENT_TIME;
    ev->data.data32[1] = tray_reply->atom;
    ev->data.data32[2] = selwin;

    xcb_send_event(xcb_connection,
                   0,
                   xcb_root,
                   0xFFFFFF,
                   (char *)buffer);
}