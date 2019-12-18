#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int lastCursorPosX; int lastCursorPosY; } ;
struct TYPE_9__ {TYPE_1__ x11; } ;
typedef  TYPE_3__ _GLFWwindow ;
typedef  int /*<<< orphan*/  XEvent ;
struct TYPE_8__ {int /*<<< orphan*/  display; TYPE_3__* disabledCursorWindow; } ;
struct TYPE_10__ {TYPE_2__ x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XNextEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XPending (int /*<<< orphan*/ ) ; 
 scalar_t__ XQLength (int /*<<< orphan*/ ) ; 
 TYPE_6__ _glfw ; 
 int /*<<< orphan*/  _glfwDetectJoystickConnectionLinux () ; 
 int /*<<< orphan*/  _glfwPlatformGetWindowSize (TYPE_3__*,int*,int*) ; 
 int /*<<< orphan*/  _glfwPlatformSetCursorPos (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  processEvent (int /*<<< orphan*/ *) ; 

void _glfwPlatformPollEvents(void)
{
    _GLFWwindow* window;

#if defined(__linux__)
    _glfwDetectJoystickConnectionLinux();
#endif
    XPending(_glfw.x11.display);

    while (XQLength(_glfw.x11.display))
    {
        XEvent event;
        XNextEvent(_glfw.x11.display, &event);
        processEvent(&event);
    }

    window = _glfw.x11.disabledCursorWindow;
    if (window)
    {
        int width, height;
        _glfwPlatformGetWindowSize(window, &width, &height);

        // NOTE: Re-center the cursor only if it has moved since the last call,
        //       to avoid breaking glfwWaitEvents with MotionNotify
        if (window->x11.lastCursorPosX != width / 2 ||
            window->x11.lastCursorPosY != height / 2)
        {
            _glfwPlatformSetCursorPos(window, width / 2, height / 2);
        }
    }

    XFlush(_glfw.x11.display);
}