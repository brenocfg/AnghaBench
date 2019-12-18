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
struct TYPE_3__ {int /*<<< orphan*/  window; } ;
typedef  TYPE_1__ xcb_resize_request_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_configuration_change (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_resize_request(xcb_resize_request_event_t *event) {
    DLOG("ResizeRequest for window = %08x\n", event->window);
    handle_configuration_change(event->window);
}