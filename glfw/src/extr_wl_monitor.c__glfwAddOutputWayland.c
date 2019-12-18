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
typedef  int uint32_t ;
struct wl_output {int dummy; } ;
struct TYPE_8__ {int scale; int name; struct wl_output* output; } ;
struct TYPE_10__ {TYPE_1__ wl; } ;
typedef  TYPE_3__ _GLFWmonitor ;
struct TYPE_9__ {int /*<<< orphan*/  registry; } ;
struct TYPE_11__ {TYPE_2__ wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 TYPE_7__ _glfw ; 
 TYPE_3__* _glfwAllocMonitor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwFreeMonitor (TYPE_3__*) ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  outputListener ; 
 int /*<<< orphan*/  wl_output_add_listener (struct wl_output*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  wl_output_interface ; 
 struct wl_output* wl_registry_bind (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

void _glfwAddOutputWayland(uint32_t name, uint32_t version)
{
    _GLFWmonitor *monitor;
    struct wl_output *output;

    if (version < 2)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Wayland: Unsupported output interface version");
        return;
    }

    // The actual name of this output will be set in the geometry handler.
    monitor = _glfwAllocMonitor(NULL, 0, 0);

    output = wl_registry_bind(_glfw.wl.registry,
                              name,
                              &wl_output_interface,
                              2);
    if (!output)
    {
        _glfwFreeMonitor(monitor);
        return;
    }

    monitor->wl.scale = 1;
    monitor->wl.output = output;
    monitor->wl.name = name;

    wl_output_add_listener(output, &outputListener, monitor);
}