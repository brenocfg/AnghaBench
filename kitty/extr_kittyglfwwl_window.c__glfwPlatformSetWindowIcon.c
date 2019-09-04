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
typedef  int /*<<< orphan*/  _GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWimage ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 

void _glfwPlatformSetWindowIcon(_GLFWwindow* window,
                                int count, const GLFWimage* images)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "Wayland: Setting window icon not supported");
}