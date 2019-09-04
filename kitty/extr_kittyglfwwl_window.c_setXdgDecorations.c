#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  serverSide; } ;
struct TYPE_13__ {int /*<<< orphan*/  decoration; int /*<<< orphan*/  toplevel; } ;
struct TYPE_12__ {TYPE_1__ decorations; TYPE_4__ xdg; } ;
struct TYPE_14__ {TYPE_3__ wl; } ;
typedef  TYPE_5__ _GLFWwindow ;
struct TYPE_11__ {scalar_t__ decorationManager; } ;
struct TYPE_15__ {TYPE_2__ wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE ; 
 TYPE_9__ _glfw ; 
 int /*<<< orphan*/  createDecorations (TYPE_5__*) ; 
 int /*<<< orphan*/  xdgDecorationListener ; 
 int /*<<< orphan*/  zxdg_decoration_manager_v1_get_toplevel_decoration (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zxdg_toplevel_decoration_v1_add_listener (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  zxdg_toplevel_decoration_v1_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setXdgDecorations(_GLFWwindow* window)
{
    if (_glfw.wl.decorationManager)
    {
        window->wl.xdg.decoration =
            zxdg_decoration_manager_v1_get_toplevel_decoration(
                _glfw.wl.decorationManager, window->wl.xdg.toplevel);
        zxdg_toplevel_decoration_v1_add_listener(window->wl.xdg.decoration,
                                                 &xdgDecorationListener,
                                                 window);
        zxdg_toplevel_decoration_v1_set_mode(
            window->wl.xdg.decoration,
            ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE);
    }
    else
    {
        window->wl.decorations.serverSide = GLFW_FALSE;
        createDecorations(window);
    }
}