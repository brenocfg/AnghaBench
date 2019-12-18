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
struct TYPE_5__ {int /*<<< orphan*/  window; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ xcb_unmap_notify_event_t ;
struct TYPE_6__ {int mapped; } ;
typedef  TYPE_2__ trayclient ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,...) ; 
 int /*<<< orphan*/  configure_trayclients () ; 
 int /*<<< orphan*/  draw_bars (int) ; 
 TYPE_2__* trayclient_from_window (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_unmap_notify(xcb_unmap_notify_event_t *event) {
    DLOG("UnmapNotify for window = %08x, event = %08x\n", event->window, event->event);

    trayclient *client = trayclient_from_window(event->window);
    if (!client) {
        DLOG("WARNING: Could not find corresponding tray window.\n");
        return;
    }

    DLOG("Tray client unmapped (window ID %08x). Adjusting tray.\n", event->window);
    client->mapped = false;

    /* Trigger an update, we now have more space for the statusline */
    configure_trayclients();
    draw_bars(false);
}