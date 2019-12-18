#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int interval; } ;
struct TYPE_8__ {TYPE_1__ wgl; } ;
struct TYPE_10__ {int /*<<< orphan*/  monitor; TYPE_2__ context; } ;
typedef  TYPE_4__ _GLFWwindow ;
struct TYPE_9__ {scalar_t__ EXT_swap_control; } ;
struct TYPE_11__ {TYPE_3__ wgl; int /*<<< orphan*/  contextSlot; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DwmIsCompositionEnabled (scalar_t__*) ; 
 scalar_t__ IsWindows8OrGreater () ; 
 scalar_t__ IsWindowsVistaOrGreater () ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 TYPE_6__ _glfw ; 
 TYPE_4__* _glfwPlatformGetTls (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wglSwapIntervalEXT (int) ; 

__attribute__((used)) static void swapIntervalWGL(int interval)
{
    _GLFWwindow* window = _glfwPlatformGetTls(&_glfw.contextSlot);

    window->context.wgl.interval = interval;

    if (!window->monitor)
    {
        if (IsWindowsVistaOrGreater())
        {
            // DWM Composition is always enabled on Win8+
            BOOL enabled = IsWindows8OrGreater();

            // HACK: Disable WGL swap interval when desktop composition is enabled to
            //       avoid interfering with DWM vsync
            if (enabled ||
                (SUCCEEDED(DwmIsCompositionEnabled(&enabled)) && enabled))
                interval = 0;
        }
    }

    if (_glfw.wgl.EXT_swap_control)
        wglSwapIntervalEXT(interval);
}