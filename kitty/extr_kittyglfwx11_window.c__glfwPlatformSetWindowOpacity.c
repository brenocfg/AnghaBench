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
struct TYPE_7__ {int /*<<< orphan*/  NET_WM_WINDOW_OPACITY; int /*<<< orphan*/  display; } ;
struct TYPE_9__ {TYPE_2__ x11; } ;
typedef  int /*<<< orphan*/  CARD32 ;

/* Variables and functions */
 int /*<<< orphan*/  PropModeReplace ; 
 int /*<<< orphan*/  XA_CARDINAL ; 
 int /*<<< orphan*/  XChangeProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned char*,int) ; 
 TYPE_5__ _glfw ; 

void _glfwPlatformSetWindowOpacity(_GLFWwindow* window, float opacity)
{
    const CARD32 value = (CARD32) (0xffffffffu * (double) opacity);
    XChangeProperty(_glfw.x11.display, window->x11.handle,
                    _glfw.x11.NET_WM_WINDOW_OPACITY, XA_CARDINAL, 32,
                    PropModeReplace, (unsigned char*) &value, 1);
}