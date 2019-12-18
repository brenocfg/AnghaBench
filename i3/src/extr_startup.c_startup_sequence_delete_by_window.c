#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_get_property_reply_t ;
typedef  int /*<<< orphan*/  xcb_get_property_cookie_t ;
struct Startup_Sequence {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ i3Window ;

/* Variables and functions */
 int /*<<< orphan*/  A__NET_STARTUP_ID ; 
 int /*<<< orphan*/  XCB_GET_PROPERTY_TYPE_ANY ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  startup_sequence_delete (struct Startup_Sequence*) ; 
 struct Startup_Sequence* startup_sequence_get (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xcb_get_property (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * xcb_get_property_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void startup_sequence_delete_by_window(i3Window *win) {
    struct Startup_Sequence *sequence;
    xcb_get_property_cookie_t cookie;
    xcb_get_property_reply_t *startup_id_reply;

    cookie = xcb_get_property(conn, false, win->id, A__NET_STARTUP_ID,
                              XCB_GET_PROPERTY_TYPE_ANY, 0, 512);
    startup_id_reply = xcb_get_property_reply(conn, cookie, NULL);

    sequence = startup_sequence_get(win, startup_id_reply, true);
    if (sequence != NULL) {
        startup_sequence_delete(sequence);
    }
}