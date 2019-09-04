#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* cursor; struct TYPE_6__* next; } ;
typedef  TYPE_1__ _GLFWwindow ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_2__ _GLFWcursor ;
struct TYPE_8__ {TYPE_2__* cursorListHead; TYPE_1__* windowListHead; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWcursor ;

/* Variables and functions */
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT () ; 
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/  _glfwPlatformDestroyCursor (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  glfwSetCursor (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void glfwDestroyCursor(GLFWcursor* handle)
{
    _GLFWcursor* cursor = (_GLFWcursor*) handle;

    _GLFW_REQUIRE_INIT();

    if (cursor == NULL)
        return;

    // Make sure the cursor is not being used by any window
    {
        _GLFWwindow* window;

        for (window = _glfw.windowListHead;  window;  window = window->next)
        {
            if (window->cursor == cursor)
                glfwSetCursor((GLFWwindow*) window, NULL);
        }
    }

    _glfwPlatformDestroyCursor(cursor);

    // Unlink cursor from global linked list
    {
        _GLFWcursor** prev = &_glfw.cursorListHead;

        while (*prev != cursor)
            prev = &((*prev)->next);

        *prev = cursor->next;
    }

    free(cursor);
}