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
struct wl_display {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ibus; } ;
struct TYPE_5__ {TYPE_1__ xkb; int /*<<< orphan*/  eventLoopData; struct wl_display* display; } ;
struct TYPE_6__ {TYPE_2__ wl; } ;
typedef  scalar_t__ GLFWbool ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 TYPE_3__ _glfw ; 
 int /*<<< orphan*/  abortOnFatalError (scalar_t__) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  glfw_dbus_session_bus_dispatch () ; 
 int /*<<< orphan*/  glfw_ibus_dispatch (int /*<<< orphan*/ *) ; 
 scalar_t__ pollForEvents (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  wl_display_cancel_read (struct wl_display*) ; 
 int wl_display_dispatch_pending (struct wl_display*) ; 
 scalar_t__ wl_display_flush (struct wl_display*) ; 
 int wl_display_get_error (struct wl_display*) ; 
 scalar_t__ wl_display_prepare_read (struct wl_display*) ; 
 int /*<<< orphan*/  wl_display_read_events (struct wl_display*) ; 

__attribute__((used)) static void
handleEvents(double timeout)
{
    struct wl_display* display = _glfw.wl.display;
    errno = 0;

    while (wl_display_prepare_read(display) != 0) {
        while(1) {
            errno = 0;
            int num_dispatched = wl_display_dispatch_pending(display);
            if (num_dispatched == 0) return;
            if (num_dispatched < 0) {
                if (errno == EAGAIN) continue;
                int last_error = wl_display_get_error(display);
                if (last_error) abortOnFatalError(last_error);
                return;
            }
            break;
        }
    }

    // If an error different from EAGAIN happens, we have likely been
    // disconnected from the Wayland session, try to handle that the best we
    // can.
    errno = 0;
    if (wl_display_flush(display) < 0 && errno != EAGAIN)
    {
        abortOnFatalError(errno);
        wl_display_cancel_read(display);
        return;
    }

    GLFWbool display_read_ok = pollForEvents(&_glfw.wl.eventLoopData, timeout);
    if (display_read_ok) {
        wl_display_read_events(display);
        wl_display_dispatch_pending(display);
    }
    else
    {
        wl_display_cancel_read(display);
    }
    glfw_ibus_dispatch(&_glfw.wl.xkb.ibus);
    glfw_dbus_session_bus_dispatch();
}