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
struct TYPE_6__ {int /*<<< orphan*/  handle; } ;
struct TYPE_8__ {TYPE_1__ x11; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_7__ {int /*<<< orphan*/  NET_WM_WINDOW_OPACITY; int /*<<< orphan*/  NET_WM_CM_Sx; int /*<<< orphan*/  display; } ;
struct TYPE_9__ {TYPE_2__ x11; } ;
typedef  double CARD32 ;

/* Variables and functions */
 int /*<<< orphan*/  XA_CARDINAL ; 
 int /*<<< orphan*/  XFree (double*) ; 
 scalar_t__ XGetSelectionOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ _glfw ; 
 scalar_t__ _glfwGetWindowPropertyX11 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char**) ; 

float _glfwPlatformGetWindowOpacity(_GLFWwindow* window)
{
    float opacity = 1.f;

    if (XGetSelectionOwner(_glfw.x11.display, _glfw.x11.NET_WM_CM_Sx))
    {
        CARD32* value = NULL;

        if (_glfwGetWindowPropertyX11(window->x11.handle,
                                      _glfw.x11.NET_WM_WINDOW_OPACITY,
                                      XA_CARDINAL,
                                      (unsigned char**) &value))
        {
            opacity = (float) (*value / (double) 0xffffffffu);
        }

        if (value)
            XFree(value);
    }

    return opacity;
}