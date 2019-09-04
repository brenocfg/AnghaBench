#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_shell_surface {int dummy; } ;
typedef  int int32_t ;
struct TYPE_6__ {scalar_t__ numer; scalar_t__ denom; scalar_t__ minwidth; scalar_t__ maxwidth; scalar_t__ minheight; scalar_t__ maxheight; scalar_t__ decorated; int /*<<< orphan*/  monitor; } ;
typedef  TYPE_2__ _GLFWwindow ;
struct TYPE_5__ {scalar_t__ viewporter; } ;
struct TYPE_7__ {TYPE_1__ wl; } ;

/* Variables and functions */
 scalar_t__ GLFW_DONT_CARE ; 
 scalar_t__ _GLFW_DECORATION_HORIZONTAL ; 
 scalar_t__ _GLFW_DECORATION_VERTICAL ; 
 TYPE_4__ _glfw ; 
 int /*<<< orphan*/  dispatchChangesAfterConfigure (TYPE_2__*,int,int) ; 

__attribute__((used)) static void handleConfigure(void* data,
                            struct wl_shell_surface* shellSurface,
                            uint32_t edges,
                            int32_t width,
                            int32_t height)
{
    _GLFWwindow* window = data;
    float aspectRatio;
    float targetRatio;

    if (!window->monitor)
    {
        if (_glfw.wl.viewporter && window->decorated)
        {
            width -= _GLFW_DECORATION_HORIZONTAL;
            height -= _GLFW_DECORATION_VERTICAL;
        }
        if (width < 1)
            width = 1;
        if (height < 1)
            height = 1;

        if (window->numer != GLFW_DONT_CARE && window->denom != GLFW_DONT_CARE)
        {
            aspectRatio = (float)width / (float)height;
            targetRatio = (float)window->numer / (float)window->denom;
            if (aspectRatio < targetRatio)
                height = width / targetRatio;
            else if (aspectRatio > targetRatio)
                width = height * targetRatio;
        }

        if (window->minwidth != GLFW_DONT_CARE && width < window->minwidth)
            width = window->minwidth;
        else if (window->maxwidth != GLFW_DONT_CARE && width > window->maxwidth)
            width = window->maxwidth;

        if (window->minheight != GLFW_DONT_CARE && height < window->minheight)
            height = window->minheight;
        else if (window->maxheight != GLFW_DONT_CARE && height > window->maxheight)
            height = window->maxheight;
    }

    dispatchChangesAfterConfigure(window, width, height);
}