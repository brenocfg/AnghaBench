#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ id; } ;
struct TYPE_6__ {TYPE_1__ bar; } ;
typedef  TYPE_2__ i3_output ;

/* Variables and functions */
 scalar_t__ XCB_NONE ; 
 int /*<<< orphan*/  kick_tray_clients (TYPE_2__*) ; 
 int /*<<< orphan*/  xcb_connection ; 
 int /*<<< orphan*/  xcb_destroy_window (int /*<<< orphan*/ ,scalar_t__) ; 

void destroy_window(i3_output *output) {
    if (output == NULL) {
        return;
    }
    if (output->bar.id == XCB_NONE) {
        return;
    }

    kick_tray_clients(output);
    xcb_destroy_window(xcb_connection, output->bar.id);
    output->bar.id = XCB_NONE;
}