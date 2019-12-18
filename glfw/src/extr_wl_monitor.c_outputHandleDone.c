#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wl_output {int dummy; } ;
struct _GLFWmonitor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_CONNECTED ; 
 int /*<<< orphan*/  _GLFW_INSERT_LAST ; 
 int /*<<< orphan*/  _glfwInputMonitor (struct _GLFWmonitor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void outputHandleDone(void* data, struct wl_output* output)
{
    struct _GLFWmonitor *monitor = data;

    _glfwInputMonitor(monitor, GLFW_CONNECTED, _GLFW_INSERT_LAST);
}