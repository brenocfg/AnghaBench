#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XEvent ;
struct TYPE_3__ {int /*<<< orphan*/  display; } ;
struct TYPE_4__ {TYPE_1__ x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  XNextEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ XQLength (int /*<<< orphan*/ ) ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  processEvent (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned
dispatch_x11_queued_events(void) {
    unsigned dispatched = 0;
    while (XQLength(_glfw.x11.display) > 0)
    {
        XEvent event;
        XNextEvent(_glfw.x11.display, &event);
        processEvent(&event);
        dispatched += 1;
    }
    return dispatched;
}