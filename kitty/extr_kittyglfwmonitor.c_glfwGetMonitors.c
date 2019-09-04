#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int monitorCount; scalar_t__ monitors; } ;
typedef  int /*<<< orphan*/  GLFWmonitor ;

/* Variables and functions */
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT_OR_RETURN (int /*<<< orphan*/ *) ; 
 TYPE_1__ _glfw ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

GLFWmonitor** glfwGetMonitors(int* count)
{
    assert(count != NULL);

    *count = 0;

    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);

    *count = _glfw.monitorCount;
    return (GLFWmonitor**) _glfw.monitors;
}