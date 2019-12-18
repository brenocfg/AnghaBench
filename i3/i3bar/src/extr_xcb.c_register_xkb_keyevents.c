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
struct TYPE_3__ {int /*<<< orphan*/  first_event; int /*<<< orphan*/  present; } ;
typedef  TYPE_1__ xcb_query_extension_reply_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 int /*<<< orphan*/  ELOG (char*) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  XCB_XKB_EVENT_TYPE_STATE_NOTIFY ; 
 int /*<<< orphan*/  XCB_XKB_ID_USE_CORE_KBD ; 
 int /*<<< orphan*/  XCB_XKB_MAJOR_VERSION ; 
 int /*<<< orphan*/  XCB_XKB_MINOR_VERSION ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 TYPE_1__* xcb_get_extension_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_xkb_id ; 
 int /*<<< orphan*/  xcb_xkb_select_events (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_xkb_use_extension (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xkb_base ; 

__attribute__((used)) static void register_xkb_keyevents(void) {
    const xcb_query_extension_reply_t *extreply;
    extreply = xcb_get_extension_data(conn, &xcb_xkb_id);
    if (!extreply->present) {
        ELOG("xkb is not present on this server\n");
        exit(EXIT_FAILURE);
    }
    DLOG("initializing xcb-xkb\n");
    xcb_xkb_use_extension(conn, XCB_XKB_MAJOR_VERSION, XCB_XKB_MINOR_VERSION);
    xcb_xkb_select_events(conn,
                          XCB_XKB_ID_USE_CORE_KBD,
                          XCB_XKB_EVENT_TYPE_STATE_NOTIFY,
                          0,
                          XCB_XKB_EVENT_TYPE_STATE_NOTIFY,
                          0xff,
                          0xff,
                          NULL);
    xkb_base = extreply->first_event;
}