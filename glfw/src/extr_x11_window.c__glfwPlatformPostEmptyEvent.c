#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int format; int /*<<< orphan*/  message_type; int /*<<< orphan*/  window; } ;
struct TYPE_8__ {TYPE_1__ xclient; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ XEvent ;
struct TYPE_7__ {int /*<<< orphan*/  display; int /*<<< orphan*/  helperWindowHandle; int /*<<< orphan*/  NULL_; } ;
struct TYPE_9__ {TYPE_2__ x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClientMessage ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  XFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSendEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_4__ _glfw ; 

void _glfwPlatformPostEmptyEvent(void)
{
    XEvent event = { ClientMessage };
    event.xclient.window = _glfw.x11.helperWindowHandle;
    event.xclient.format = 32; // Data is 32-bit longs
    event.xclient.message_type = _glfw.x11.NULL_;

    XSendEvent(_glfw.x11.display, _glfw.x11.helperWindowHandle, False, 0, &event);
    XFlush(_glfw.x11.display);
}