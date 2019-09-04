#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_2__ _GLFWwindow ;
struct TYPE_5__ {float contentScaleX; float contentScaleY; } ;
struct TYPE_7__ {TYPE_1__ x11; TYPE_2__* windowListHead; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_TRUE ; 
 TYPE_4__ _glfw ; 
 int /*<<< orphan*/  _glfwGetSystemContentScaleX11 (float*,float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwInputWindowContentScale (TYPE_2__*,float,float) ; 

__attribute__((used)) static void onConfigChange()
{
    float xscale, yscale;
    _glfwGetSystemContentScaleX11(&xscale, &yscale, GLFW_TRUE);

    if (xscale != _glfw.x11.contentScaleX || yscale != _glfw.x11.contentScaleY)
    {
        _GLFWwindow* window = _glfw.windowListHead;
        _glfw.x11.contentScaleX = xscale;
        _glfw.x11.contentScaleY = yscale;
        while (window)
        {
            _glfwInputWindowContentScale(window, xscale, yscale);
            window = window->next;
        }
    }
}