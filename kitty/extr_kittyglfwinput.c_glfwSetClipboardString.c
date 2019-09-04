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
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT () ; 
 int /*<<< orphan*/  _glfwPlatformSetClipboardString (char const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void glfwSetClipboardString(GLFWwindow* handle, const char* string)
{
    assert(string != NULL);

    _GLFW_REQUIRE_INIT();
    _glfwPlatformSetClipboardString(string);
}