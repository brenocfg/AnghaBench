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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ xcb_xinerama_is_active_reply_t ;
struct TYPE_6__ {int /*<<< orphan*/  present; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 int /*<<< orphan*/  FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  query_screens (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_root_output (int /*<<< orphan*/ ) ; 
 TYPE_3__* xcb_get_extension_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_xinerama_id ; 
 int /*<<< orphan*/  xcb_xinerama_is_active (int /*<<< orphan*/ ) ; 
 TYPE_1__* xcb_xinerama_is_active_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void xinerama_init(void) {
    if (!xcb_get_extension_data(conn, &xcb_xinerama_id)->present) {
        DLOG("Xinerama extension not found, using root output.\n");
        use_root_output(conn);
    } else {
        xcb_xinerama_is_active_reply_t *reply;
        reply = xcb_xinerama_is_active_reply(conn, xcb_xinerama_is_active(conn), NULL);

        if (reply == NULL || !reply->state) {
            DLOG("Xinerama is not active (in your X-Server), using root output.\n");
            use_root_output(conn);
        } else
            query_screens(conn);

        FREE(reply);
    }
}