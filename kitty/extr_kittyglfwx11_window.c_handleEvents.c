#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ibus; } ;
struct TYPE_5__ {TYPE_1__ xkb; int /*<<< orphan*/  eventLoopData; } ;
struct TYPE_6__ {TYPE_2__ x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVDBG (char*,...) ; 
 TYPE_3__ _glfw ; 
 unsigned int _glfwDispatchX11Events () ; 
 int /*<<< orphan*/  glfw_dbus_session_bus_dispatch () ; 
 int /*<<< orphan*/  glfw_ibus_dispatch (int /*<<< orphan*/ *) ; 
 int pollForEvents (int /*<<< orphan*/ *,double) ; 

__attribute__((used)) static void
handleEvents(double timeout) {
    EVDBG("starting handleEvents(%.2f)", timeout);
    int display_read_ok = pollForEvents(&_glfw.x11.eventLoopData, timeout);
    EVDBG("display_read_ok: %d", display_read_ok);
    if (display_read_ok) {
        unsigned dispatched = _glfwDispatchX11Events();
        (void)dispatched;
        EVDBG("dispatched %u X11 events", dispatched);
    }
    glfw_ibus_dispatch(&_glfw.x11.xkb.ibus);
    glfw_dbus_session_bus_dispatch();
    EVDBG("other dispatch done");
}