#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  visible; } ;
struct TYPE_6__ {TYPE_1__ wl; } ;
typedef  TYPE_2__ _GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_TRUE ; 
 int /*<<< orphan*/  createXdgSurface (TYPE_2__*) ; 

void _glfwPlatformShowWindow(_GLFWwindow* window)
{
    if (!window->wl.visible)
    {
        createXdgSurface(window);
        window->wl.visible = GLFW_TRUE;
    }
}