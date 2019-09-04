#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  serverSide; } ;
struct TYPE_6__ {TYPE_1__ decorations; } ;
struct TYPE_7__ {TYPE_2__ wl; int /*<<< orphan*/  monitor; scalar_t__ decorated; } ;
typedef  TYPE_3__ _GLFWwindow ;

/* Variables and functions */
 int _GLFW_DECORATION_TOP ; 
 int _GLFW_DECORATION_WIDTH ; 

void _glfwPlatformGetWindowFrameSize(_GLFWwindow* window,
                                     int* left, int* top,
                                     int* right, int* bottom)
{
    if (window->decorated && !window->monitor && !window->wl.decorations.serverSide)
    {
        if (top)
            *top = _GLFW_DECORATION_TOP;
        if (left)
            *left = _GLFW_DECORATION_WIDTH;
        if (right)
            *right = _GLFW_DECORATION_WIDTH;
        if (bottom)
            *bottom = _GLFW_DECORATION_WIDTH;
    }
}