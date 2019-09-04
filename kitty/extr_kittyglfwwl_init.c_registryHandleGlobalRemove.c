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
typedef  scalar_t__ uint32_t ;
struct wl_registry {int dummy; } ;
struct TYPE_5__ {scalar_t__ name; } ;
struct TYPE_6__ {TYPE_1__ wl; } ;
typedef  TYPE_2__ _GLFWmonitor ;
struct TYPE_7__ {int monitorCount; TYPE_2__** monitors; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_DISCONNECTED ; 
 TYPE_4__ _glfw ; 
 int /*<<< orphan*/  _glfwInputMonitor (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void registryHandleGlobalRemove(void *data,
                                       struct wl_registry *registry,
                                       uint32_t name)
{
    int i;
    _GLFWmonitor* monitor;

    for (i = 0; i < _glfw.monitorCount; ++i)
    {
        monitor = _glfw.monitors[i];
        if (monitor->wl.name == name)
        {
            _glfwInputMonitor(monitor, GLFW_DISCONNECTED, 0);
            return;
        }
    }
}