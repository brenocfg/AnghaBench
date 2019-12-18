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
struct TYPE_3__ {scalar_t__ event; } ;
typedef  TYPE_1__ xcb_configure_notify_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,scalar_t__) ; 
 scalar_t__ force_xinerama ; 
 int /*<<< orphan*/  randr_query_outputs () ; 
 scalar_t__ root ; 

__attribute__((used)) static void handle_configure_notify(xcb_configure_notify_event_t *event) {
    if (event->event != root) {
        DLOG("ConfigureNotify for non-root window 0x%08x, ignoring\n", event->event);
        return;
    }
    DLOG("ConfigureNotify for root window 0x%08x\n", event->event);

    if (force_xinerama) {
        return;
    }
    randr_query_outputs();
}