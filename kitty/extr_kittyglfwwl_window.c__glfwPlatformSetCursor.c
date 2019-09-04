#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
struct wl_cursor {int dummy; } ;
struct TYPE_15__ {scalar_t__ focus; } ;
struct TYPE_16__ {TYPE_1__ decorations; TYPE_6__* currentCursor; } ;
struct TYPE_18__ {scalar_t__ cursorMode; TYPE_2__ wl; } ;
typedef  TYPE_4__ _GLFWwindow ;
struct TYPE_19__ {int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; struct wl_cursor* member_0; } ;
typedef  TYPE_5__ _GLFWcursorWayland ;
struct TYPE_20__ {TYPE_5__ wl; } ;
typedef  TYPE_6__ _GLFWcursor ;
struct TYPE_17__ {int /*<<< orphan*/  pointerSerial; int /*<<< orphan*/  pointer; TYPE_4__* pointerFocus; } ;
struct TYPE_14__ {TYPE_3__ wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_ARROW_CURSOR ; 
 scalar_t__ GLFW_CURSOR_DISABLED ; 
 scalar_t__ GLFW_CURSOR_HIDDEN ; 
 scalar_t__ GLFW_CURSOR_NORMAL ; 
 TYPE_13__ _glfw ; 
 struct wl_cursor* _glfwLoadCursor (int /*<<< orphan*/ ) ; 
 scalar_t__ isPointerLocked (TYPE_4__*) ; 
 int /*<<< orphan*/  lockPointer (TYPE_4__*) ; 
 scalar_t__ mainWindow ; 
 int /*<<< orphan*/  setCursorImage (TYPE_5__*) ; 
 int /*<<< orphan*/  unlockPointer (TYPE_4__*) ; 
 int /*<<< orphan*/  wl_pointer_set_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void _glfwPlatformSetCursor(_GLFWwindow* window, _GLFWcursor* cursor)
{
    struct wl_cursor* defaultCursor;

    if (!_glfw.wl.pointer)
        return;

    window->wl.currentCursor = cursor;

    // If we're not in the correct window just save the cursor
    // the next time the pointer enters the window the cursor will change
    if (window != _glfw.wl.pointerFocus || window->wl.decorations.focus != mainWindow)
        return;

    // Unlock possible pointer lock if no longer disabled.
    if (window->cursorMode != GLFW_CURSOR_DISABLED && isPointerLocked(window))
        unlockPointer(window);

    if (window->cursorMode == GLFW_CURSOR_NORMAL)
    {
        if (cursor)
            setCursorImage(&cursor->wl);
        else
        {
            defaultCursor = _glfwLoadCursor(GLFW_ARROW_CURSOR);
            if (!defaultCursor) return;
            _GLFWcursorWayland cursorWayland = {
                defaultCursor,
                NULL,
                0, 0,
                0, 0,
                0
            };
            setCursorImage(&cursorWayland);
        }
    }
    else if (window->cursorMode == GLFW_CURSOR_DISABLED)
    {
        if (!isPointerLocked(window))
            lockPointer(window);
    }
    else if (window->cursorMode == GLFW_CURSOR_HIDDEN)
    {
        wl_pointer_set_cursor(_glfw.wl.pointer, _glfw.wl.pointerSerial,
                              NULL, 0, 0);
    }
}