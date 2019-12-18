#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  handle; } ;
struct TYPE_12__ {TYPE_1__ x11; scalar_t__ rawMouseMotion; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_11__ {int /*<<< orphan*/  hiddenCursorHandle; int /*<<< orphan*/  display; int /*<<< orphan*/  restoreCursorPosY; int /*<<< orphan*/  restoreCursorPosX; TYPE_3__* disabledCursorWindow; } ;
struct TYPE_13__ {TYPE_2__ x11; } ;

/* Variables and functions */
 int ButtonPressMask ; 
 int ButtonReleaseMask ; 
 int /*<<< orphan*/  CurrentTime ; 
 int /*<<< orphan*/  GrabModeAsync ; 
 int PointerMotionMask ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  XGrabPointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_9__ _glfw ; 
 int /*<<< orphan*/  _glfwCenterCursorInContentArea (TYPE_3__*) ; 
 int /*<<< orphan*/  _glfwPlatformGetCursorPos (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enableRawMouseMotion (TYPE_3__*) ; 
 int /*<<< orphan*/  updateCursorImage (TYPE_3__*) ; 

__attribute__((used)) static void disableCursor(_GLFWwindow* window)
{
    if (window->rawMouseMotion)
        enableRawMouseMotion(window);

    _glfw.x11.disabledCursorWindow = window;
    _glfwPlatformGetCursorPos(window,
                              &_glfw.x11.restoreCursorPosX,
                              &_glfw.x11.restoreCursorPosY);
    updateCursorImage(window);
    _glfwCenterCursorInContentArea(window);
    XGrabPointer(_glfw.x11.display, window->x11.handle, True,
                 ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
                 GrabModeAsync, GrabModeAsync,
                 window->x11.handle,
                 _glfw.x11.hiddenCursorHandle,
                 CurrentTime);
}