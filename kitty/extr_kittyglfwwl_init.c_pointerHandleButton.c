#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct wl_pointer {int dummy; } ;
struct TYPE_11__ {int focus; } ;
struct TYPE_10__ {scalar_t__ toplevel; } ;
struct TYPE_12__ {TYPE_2__ decorations; scalar_t__ cursorPosY; scalar_t__ cursorPosX; TYPE_1__ xdg; int /*<<< orphan*/  shellSurface; scalar_t__ width; } ;
struct TYPE_16__ {TYPE_3__ wl; } ;
typedef  TYPE_7__ _GLFWwindow ;
struct TYPE_13__ {int /*<<< orphan*/  modifiers; } ;
struct TYPE_14__ {TYPE_4__ states; } ;
struct TYPE_15__ {TYPE_5__ xkb; scalar_t__ pointerSerial; int /*<<< orphan*/  seat; TYPE_7__* pointerFocus; } ;
struct TYPE_17__ {TYPE_6__ wl; } ;

/* Variables and functions */
 scalar_t__ BTN_LEFT ; 
 scalar_t__ BTN_RIGHT ; 
 int /*<<< orphan*/  GLFW_PRESS ; 
 int /*<<< orphan*/  GLFW_RELEASE ; 
 scalar_t__ WL_POINTER_BUTTON_STATE_PRESSED ; 
 scalar_t__ WL_SHELL_SURFACE_RESIZE_BOTTOM ; 
 scalar_t__ WL_SHELL_SURFACE_RESIZE_BOTTOM_LEFT ; 
 scalar_t__ WL_SHELL_SURFACE_RESIZE_BOTTOM_RIGHT ; 
 scalar_t__ WL_SHELL_SURFACE_RESIZE_LEFT ; 
 scalar_t__ WL_SHELL_SURFACE_RESIZE_NONE ; 
 scalar_t__ WL_SHELL_SURFACE_RESIZE_RIGHT ; 
 scalar_t__ WL_SHELL_SURFACE_RESIZE_TOP ; 
 scalar_t__ WL_SHELL_SURFACE_RESIZE_TOP_LEFT ; 
 scalar_t__ WL_SHELL_SURFACE_RESIZE_TOP_RIGHT ; 
 scalar_t__ _GLFW_DECORATION_WIDTH ; 
 TYPE_9__ _glfw ; 
 int /*<<< orphan*/  _glfwInputMouseClick (TYPE_7__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
#define  bottomDecoration 132 
#define  leftDecoration 131 
#define  mainWindow 130 
#define  rightDecoration 129 
#define  topDecoration 128 
 int /*<<< orphan*/  wl_shell_surface_move (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wl_shell_surface_resize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  xdg_toplevel_move (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xdg_toplevel_resize (scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  xdg_toplevel_show_window_menu (scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void pointerHandleButton(void* data,
                                struct wl_pointer* pointer,
                                uint32_t serial,
                                uint32_t time,
                                uint32_t button,
                                uint32_t state)
{
    _GLFWwindow* window = _glfw.wl.pointerFocus;
    int glfwButton;

    // Both xdg-shell and wl_shell use the same values.
    uint32_t edges = WL_SHELL_SURFACE_RESIZE_NONE;

    if (!window)
        return;
    if (button == BTN_LEFT)
    {
        switch (window->wl.decorations.focus)
        {
            case mainWindow:
                break;
            case topDecoration:
                if (window->wl.cursorPosY < _GLFW_DECORATION_WIDTH)
                    edges = WL_SHELL_SURFACE_RESIZE_TOP;
                else
                {
                    if (window->wl.xdg.toplevel)
                        xdg_toplevel_move(window->wl.xdg.toplevel, _glfw.wl.seat, serial);
                    else
                        wl_shell_surface_move(window->wl.shellSurface, _glfw.wl.seat, serial);
                }
                break;
            case leftDecoration:
                if (window->wl.cursorPosY < _GLFW_DECORATION_WIDTH)
                    edges = WL_SHELL_SURFACE_RESIZE_TOP_LEFT;
                else
                    edges = WL_SHELL_SURFACE_RESIZE_LEFT;
                break;
            case rightDecoration:
                if (window->wl.cursorPosY < _GLFW_DECORATION_WIDTH)
                    edges = WL_SHELL_SURFACE_RESIZE_TOP_RIGHT;
                else
                    edges = WL_SHELL_SURFACE_RESIZE_RIGHT;
                break;
            case bottomDecoration:
                if (window->wl.cursorPosX < _GLFW_DECORATION_WIDTH)
                    edges = WL_SHELL_SURFACE_RESIZE_BOTTOM_LEFT;
                else if (window->wl.cursorPosX > window->wl.width + _GLFW_DECORATION_WIDTH)
                    edges = WL_SHELL_SURFACE_RESIZE_BOTTOM_RIGHT;
                else
                    edges = WL_SHELL_SURFACE_RESIZE_BOTTOM;
                break;
            default:
                assert(0);
        }
        if (edges != WL_SHELL_SURFACE_RESIZE_NONE)
        {
            if (window->wl.xdg.toplevel)
                xdg_toplevel_resize(window->wl.xdg.toplevel, _glfw.wl.seat,
                                    serial, edges);
            else
                wl_shell_surface_resize(window->wl.shellSurface, _glfw.wl.seat,
                                        serial, edges);
        }
    }
    else if (button == BTN_RIGHT)
    {
        if (window->wl.decorations.focus != mainWindow && window->wl.xdg.toplevel)
        {
            xdg_toplevel_show_window_menu(window->wl.xdg.toplevel,
                                          _glfw.wl.seat, serial,
                                          window->wl.cursorPosX,
                                          window->wl.cursorPosY);
            return;
        }
    }

    // Don’t pass the button to the user if it was related to a decoration.
    if (window->wl.decorations.focus != mainWindow)
        return;

    _glfw.wl.pointerSerial = serial;

    /* Makes left, right and middle 0, 1 and 2. Overall order follows evdev
     * codes. */
    glfwButton = button - BTN_LEFT;

    _glfwInputMouseClick(window,
                         glfwButton,
                         state == WL_POINTER_BUTTON_STATE_PRESSED
                                ? GLFW_PRESS
                                : GLFW_RELEASE,
                         _glfw.wl.xkb.states.modifiers);
}