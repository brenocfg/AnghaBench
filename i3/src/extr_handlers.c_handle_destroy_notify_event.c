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
struct TYPE_5__ {int /*<<< orphan*/  window; int /*<<< orphan*/  event; int /*<<< orphan*/  sequence; } ;
typedef  TYPE_1__ xcb_unmap_notify_event_t ;
struct TYPE_6__ {int /*<<< orphan*/  window; int /*<<< orphan*/  event; int /*<<< orphan*/  sequence; } ;
typedef  TYPE_2__ xcb_destroy_notify_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_unmap_notify_event (TYPE_1__*) ; 

__attribute__((used)) static void handle_destroy_notify_event(xcb_destroy_notify_event_t *event) {
    DLOG("destroy notify for 0x%08x, 0x%08x\n", event->event, event->window);

    xcb_unmap_notify_event_t unmap;
    unmap.sequence = event->sequence;
    unmap.event = event->event;
    unmap.window = event->window;

    handle_unmap_notify_event(&unmap);
}