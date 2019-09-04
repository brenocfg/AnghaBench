#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ visible; int /*<<< orphan*/  shellSurface; } ;
struct TYPE_10__ {TYPE_2__ wl; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_8__ {scalar_t__ wmBase; } ;
struct TYPE_11__ {TYPE_1__ wl; } ;

/* Variables and functions */
 scalar_t__ GLFW_TRUE ; 
 TYPE_7__ _glfw ; 
 int /*<<< orphan*/  createShellSurface (TYPE_3__*) ; 
 int /*<<< orphan*/  createXdgSurface (TYPE_3__*) ; 

void _glfwPlatformShowWindow(_GLFWwindow* window)
{
    if (!window->wl.visible)
    {
        if (_glfw.wl.wmBase)
            createXdgSurface(window);
        else if (!window->wl.shellSurface)
            createShellSurface(window);
        window->wl.visible = GLFW_TRUE;
    }
}