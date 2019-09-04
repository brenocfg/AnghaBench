#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ _GLFWcursor ;
struct TYPE_6__ {TYPE_1__* cursorListHead; } ;
typedef  int /*<<< orphan*/  GLFWcursor ;
typedef  int /*<<< orphan*/  GLFWCursorShape ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_INVALID_CURSOR ; 
 int /*<<< orphan*/  GLFW_INVALID_ENUM ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT_OR_RETURN (int /*<<< orphan*/ *) ; 
 TYPE_4__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwPlatformCreateStandardCursor (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  glfwDestroyCursor (int /*<<< orphan*/ *) ; 

GLFWcursor* glfwCreateStandardCursor(GLFWCursorShape shape)
{
    _GLFWcursor* cursor;

    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);

    if (shape >= GLFW_INVALID_CURSOR)
    {
        _glfwInputError(GLFW_INVALID_ENUM, "Invalid standard cursor: %d", shape);
        return NULL;
    }

    cursor = calloc(1, sizeof(_GLFWcursor));
    cursor->next = _glfw.cursorListHead;
    _glfw.cursorListHead = cursor;

    if (!_glfwPlatformCreateStandardCursor(cursor, shape))
    {
        glfwDestroyCursor((GLFWcursor*) cursor);
        return NULL;
    }

    return (GLFWcursor*) cursor;
}