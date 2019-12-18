#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct zxdg_toplevel_decoration_v1 {int dummy; } ;
struct TYPE_5__ {int serverSide; } ;
struct TYPE_6__ {TYPE_1__ decorations; } ;
struct TYPE_7__ {TYPE_2__ wl; } ;
typedef  TYPE_3__ _GLFWwindow ;

/* Variables and functions */
 scalar_t__ ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE ; 
 int /*<<< orphan*/  createDecorations (TYPE_3__*) ; 

__attribute__((used)) static void xdgDecorationHandleConfigure(void* data,
                                         struct zxdg_toplevel_decoration_v1* decoration,
                                         uint32_t mode)
{
    _GLFWwindow* window = data;

    window->wl.decorations.serverSide = (mode == ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE);

    if (!window->wl.decorations.serverSide)
        createDecorations(window);
}