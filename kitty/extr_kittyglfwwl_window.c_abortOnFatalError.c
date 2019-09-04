#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ _GLFWwindow ;
struct TYPE_5__ {TYPE_1__* windowListHead; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 TYPE_3__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwInputWindowCloseRequest (TYPE_1__*) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static void
abortOnFatalError(int last_error) {
    _glfwInputError(GLFW_PLATFORM_ERROR, "Wayland: fatal display error: %s", strerror(last_error));
    _GLFWwindow* window = _glfw.windowListHead;
    while (window)
    {
        _glfwInputWindowCloseRequest(window);
        window = window->next;
    }
}