#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ rawMouseMotion; } ;
typedef  TYPE_2__ _GLFWwindow ;
struct TYPE_10__ {int /*<<< orphan*/  restoreCursorPosY; int /*<<< orphan*/  restoreCursorPosX; TYPE_2__* disabledCursorWindow; } ;
struct TYPE_12__ {TYPE_1__ win32; } ;

/* Variables and functions */
 TYPE_9__ _glfw ; 
 int /*<<< orphan*/  _glfwCenterCursorInContentArea (TYPE_2__*) ; 
 int /*<<< orphan*/  _glfwPlatformGetCursorPos (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enableRawMouseMotion (TYPE_2__*) ; 
 int /*<<< orphan*/  updateClipRect (TYPE_2__*) ; 
 int /*<<< orphan*/  updateCursorImage (TYPE_2__*) ; 

__attribute__((used)) static void disableCursor(_GLFWwindow* window)
{
    _glfw.win32.disabledCursorWindow = window;
    _glfwPlatformGetCursorPos(window,
                              &_glfw.win32.restoreCursorPosX,
                              &_glfw.win32.restoreCursorPosY);
    updateCursorImage(window);
    _glfwCenterCursorInContentArea(window);
    updateClipRect(window);

    if (window->rawMouseMotion)
        enableRawMouseMotion(window);
}