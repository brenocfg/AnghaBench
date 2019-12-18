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
struct TYPE_4__ {scalar_t__ request; } ;
typedef  TYPE_1__ xcb_mapping_notify_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 scalar_t__ XCB_MAPPING_KEYBOARD ; 
 scalar_t__ XCB_MAPPING_MODIFIER ; 
 int /*<<< orphan*/  XCB_NUM_LOCK ; 
 int /*<<< orphan*/  aio_get_mod_mask_for (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  grab_all_keys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keysyms ; 
 int /*<<< orphan*/  translate_keysyms () ; 
 int /*<<< orphan*/  ungrab_all_keys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_numlock_mask ; 
 int /*<<< orphan*/  xcb_refresh_keyboard_mapping (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void handle_mapping_notify(xcb_mapping_notify_event_t *event) {
    if (event->request != XCB_MAPPING_KEYBOARD &&
        event->request != XCB_MAPPING_MODIFIER)
        return;

    DLOG("Received mapping_notify for keyboard or modifier mapping, re-grabbing keys\n");
    xcb_refresh_keyboard_mapping(keysyms, event);

    xcb_numlock_mask = aio_get_mod_mask_for(XCB_NUM_LOCK, keysyms);

    ungrab_all_keys(conn);
    translate_keysyms();
    grab_all_keys(conn);
}