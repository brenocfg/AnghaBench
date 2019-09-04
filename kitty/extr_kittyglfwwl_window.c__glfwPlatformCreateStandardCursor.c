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
struct wl_cursor {int dummy; } ;
struct TYPE_4__ {scalar_t__ currentImage; struct wl_cursor* cursor; } ;
struct TYPE_5__ {TYPE_1__ wl; } ;
typedef  TYPE_2__ _GLFWcursor ;
typedef  int /*<<< orphan*/  GLFWCursorShape ;

/* Variables and functions */
 int GLFW_FALSE ; 
 int GLFW_TRUE ; 
 struct wl_cursor* _glfwLoadCursor (int /*<<< orphan*/ ) ; 

int _glfwPlatformCreateStandardCursor(_GLFWcursor* cursor, GLFWCursorShape shape)
{
    struct wl_cursor* standardCursor;

    standardCursor = _glfwLoadCursor(shape);
    if (!standardCursor) return GLFW_FALSE;
    cursor->wl.cursor = standardCursor;
    cursor->wl.currentImage = 0;
    return GLFW_TRUE;
}