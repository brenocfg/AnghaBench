#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ cursorMode; } ;
typedef  TYPE_2__ _GLFWwindow ;
typedef  int /*<<< orphan*/  _GLFWcursor ;
struct TYPE_6__ {int /*<<< orphan*/  display; } ;
struct TYPE_8__ {TYPE_1__ x11; } ;

/* Variables and functions */
 scalar_t__ GLFW_CURSOR_NORMAL ; 
 int /*<<< orphan*/  XFlush (int /*<<< orphan*/ ) ; 
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/  updateCursorImage (TYPE_2__*) ; 

void _glfwPlatformSetCursor(_GLFWwindow* window, _GLFWcursor* cursor)
{
    if (window->cursorMode == GLFW_CURSOR_NORMAL)
    {
        updateCursorImage(window);
        XFlush(_glfw.x11.display);
    }
}