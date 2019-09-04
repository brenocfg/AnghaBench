#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  callbacks; } ;
typedef  TYPE_1__ _GLFWwindow ;
struct TYPE_7__ {TYPE_1__* windowListHead; int /*<<< orphan*/  contextSlot; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT () ; 
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/  _glfwPlatformDestroyWindow (TYPE_1__*) ; 
 TYPE_1__* _glfwPlatformGetTls (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void glfwDestroyWindow(GLFWwindow* handle)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;

    _GLFW_REQUIRE_INIT();

    // Allow closing of NULL (to match the behavior of free)
    if (window == NULL)
        return;

    // Clear all callbacks to avoid exposing a half torn-down window object
    memset(&window->callbacks, 0, sizeof(window->callbacks));

    // The window's context must not be current on another thread when the
    // window is destroyed
    if (window == _glfwPlatformGetTls(&_glfw.contextSlot))
        glfwMakeContextCurrent(NULL);

    _glfwPlatformDestroyWindow(window);

    // Unlink window from global linked list
    {
        _GLFWwindow** prev = &_glfw.windowListHead;

        while (*prev != window)
            prev = &((*prev)->next);

        *prev = window->next;
    }

    free(window);
}