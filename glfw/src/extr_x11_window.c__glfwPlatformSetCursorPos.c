#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int warpCursorPosX; int warpCursorPosY; int /*<<< orphan*/  handle; } ;
struct TYPE_8__ {TYPE_2__ x11; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_6__ {int /*<<< orphan*/  display; } ;
struct TYPE_9__ {TYPE_1__ x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  None ; 
 int /*<<< orphan*/  XFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XWarpPointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 TYPE_5__ _glfw ; 

void _glfwPlatformSetCursorPos(_GLFWwindow* window, double x, double y)
{
    // Store the new position so it can be recognized later
    window->x11.warpCursorPosX = (int) x;
    window->x11.warpCursorPosY = (int) y;

    XWarpPointer(_glfw.x11.display, None, window->x11.handle,
                 0,0,0,0, (int) x, (int) y);
    XFlush(_glfw.x11.display);
}