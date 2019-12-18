#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wl_surface {int dummy; } ;
struct wl_output {int dummy; } ;
struct TYPE_4__ {int monitorsCount; int /*<<< orphan*/ ** monitors; } ;
struct TYPE_5__ {TYPE_1__ wl; } ;
typedef  TYPE_2__ _GLFWwindow ;
typedef  int /*<<< orphan*/  _GLFWmonitor ;
typedef  scalar_t__ GLFWbool ;

/* Variables and functions */
 scalar_t__ GLFW_FALSE ; 
 scalar_t__ GLFW_TRUE ; 
 int /*<<< orphan*/  checkScaleChange (TYPE_2__*) ; 
 int /*<<< orphan*/ * wl_output_get_user_data (struct wl_output*) ; 

__attribute__((used)) static void surfaceHandleLeave(void *data,
                               struct wl_surface *surface,
                               struct wl_output *output)
{
    _GLFWwindow* window = data;
    _GLFWmonitor* monitor = wl_output_get_user_data(output);
    GLFWbool found;
    int i;

    for (i = 0, found = GLFW_FALSE; i < window->wl.monitorsCount - 1; ++i)
    {
        if (monitor == window->wl.monitors[i])
            found = GLFW_TRUE;
        if (found)
            window->wl.monitors[i] = window->wl.monitors[i + 1];
    }
    window->wl.monitors[--window->wl.monitorsCount] = NULL;

    checkScaleChange(window);
}