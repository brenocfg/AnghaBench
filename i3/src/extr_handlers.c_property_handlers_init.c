#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  atom; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_WM_CLIENT_LEADER ; 
 int /*<<< orphan*/  A_WM_WINDOW_ROLE ; 
 int /*<<< orphan*/  A__MOTIF_WM_HINTS ; 
 int /*<<< orphan*/  A__NET_WM_NAME ; 
 int /*<<< orphan*/  A__NET_WM_STRUT_PARTIAL ; 
 int /*<<< orphan*/  A__NET_WM_WINDOW_TYPE ; 
 int /*<<< orphan*/  XCB_ATOM_WM_CLASS ; 
 int /*<<< orphan*/  XCB_ATOM_WM_HINTS ; 
 int /*<<< orphan*/  XCB_ATOM_WM_NAME ; 
 int /*<<< orphan*/  XCB_ATOM_WM_NORMAL_HINTS ; 
 int /*<<< orphan*/  XCB_ATOM_WM_TRANSIENT_FOR ; 
 int /*<<< orphan*/  conn_screen ; 
 TYPE_1__* property_handlers ; 
 int /*<<< orphan*/  sn_monitor_context_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sndisplay ; 
 int /*<<< orphan*/  startup_monitor_event ; 

void property_handlers_init(void) {
    sn_monitor_context_new(sndisplay, conn_screen, startup_monitor_event, NULL, NULL);

    property_handlers[0].atom = A__NET_WM_NAME;
    property_handlers[1].atom = XCB_ATOM_WM_HINTS;
    property_handlers[2].atom = XCB_ATOM_WM_NAME;
    property_handlers[3].atom = XCB_ATOM_WM_NORMAL_HINTS;
    property_handlers[4].atom = A_WM_CLIENT_LEADER;
    property_handlers[5].atom = XCB_ATOM_WM_TRANSIENT_FOR;
    property_handlers[6].atom = A_WM_WINDOW_ROLE;
    property_handlers[7].atom = XCB_ATOM_WM_CLASS;
    property_handlers[8].atom = A__NET_WM_STRUT_PARTIAL;
    property_handlers[9].atom = A__NET_WM_WINDOW_TYPE;
    property_handlers[10].atom = A__MOTIF_WM_HINTS;
}