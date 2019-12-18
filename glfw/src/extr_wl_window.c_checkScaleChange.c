#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int monitorsCount; int scale; int /*<<< orphan*/  surface; TYPE_2__** monitors; } ;
struct TYPE_13__ {TYPE_4__ wl; } ;
typedef  TYPE_5__ _GLFWwindow ;
struct TYPE_11__ {int compositorVersion; } ;
struct TYPE_14__ {TYPE_3__ wl; } ;
struct TYPE_9__ {int scale; } ;
struct TYPE_10__ {TYPE_1__ wl; } ;

/* Variables and functions */
 TYPE_8__ _glfw ; 
 int /*<<< orphan*/  resizeWindow (TYPE_5__*) ; 
 int /*<<< orphan*/  wl_surface_set_buffer_scale (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void checkScaleChange(_GLFWwindow* window)
{
    int scale = 1;
    int i;
    int monitorScale;

    // Check if we will be able to set the buffer scale or not.
    if (_glfw.wl.compositorVersion < 3)
        return;

    // Get the scale factor from the highest scale monitor.
    for (i = 0; i < window->wl.monitorsCount; ++i)
    {
        monitorScale = window->wl.monitors[i]->wl.scale;
        if (scale < monitorScale)
            scale = monitorScale;
    }

    // Only change the framebuffer size if the scale changed.
    if (scale != window->wl.scale)
    {
        window->wl.scale = scale;
        wl_surface_set_buffer_scale(window->wl.surface, scale);
        resizeWindow(window);
    }
}