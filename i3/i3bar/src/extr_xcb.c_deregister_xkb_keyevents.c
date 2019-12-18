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
 int /*<<< orphan*/  XCB_XKB_ID_USE_CORE_KBD ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  xcb_xkb_select_events (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void deregister_xkb_keyevents(void) {
    xcb_xkb_select_events(conn,
                          XCB_XKB_ID_USE_CORE_KBD,
                          0,
                          0,
                          0,
                          0xff,
                          0xff,
                          NULL);
}