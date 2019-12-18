#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  handle; } ;
struct TYPE_16__ {scalar_t__ minwidth; scalar_t__ minheight; scalar_t__ maxwidth; scalar_t__ maxheight; scalar_t__ numer; scalar_t__ denom; TYPE_4__ x11; scalar_t__ resizable; int /*<<< orphan*/  monitor; } ;
typedef  TYPE_5__ _GLFWwindow ;
struct TYPE_13__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_12__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_17__ {int flags; int min_width; int min_height; int max_width; int max_height; int /*<<< orphan*/  win_gravity; TYPE_2__ max_aspect; TYPE_1__ min_aspect; } ;
typedef  TYPE_6__ XSizeHints ;
struct TYPE_14__ {int /*<<< orphan*/  display; } ;
struct TYPE_18__ {TYPE_3__ x11; } ;

/* Variables and functions */
 scalar_t__ GLFW_DONT_CARE ; 
 int PAspect ; 
 int PMaxSize ; 
 int PMinSize ; 
 int PWinGravity ; 
 int /*<<< orphan*/  StaticGravity ; 
 TYPE_6__* XAllocSizeHints () ; 
 int /*<<< orphan*/  XFree (TYPE_6__*) ; 
 int /*<<< orphan*/  XSetWMNormalHints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 TYPE_8__ _glfw ; 

__attribute__((used)) static void updateNormalHints(_GLFWwindow* window, int width, int height)
{
    XSizeHints* hints = XAllocSizeHints();

    if (!window->monitor)
    {
        if (window->resizable)
        {
            if (window->minwidth != GLFW_DONT_CARE &&
                window->minheight != GLFW_DONT_CARE)
            {
                hints->flags |= PMinSize;
                hints->min_width = window->minwidth;
                hints->min_height = window->minheight;
            }

            if (window->maxwidth != GLFW_DONT_CARE &&
                window->maxheight != GLFW_DONT_CARE)
            {
                hints->flags |= PMaxSize;
                hints->max_width = window->maxwidth;
                hints->max_height = window->maxheight;
            }

            if (window->numer != GLFW_DONT_CARE &&
                window->denom != GLFW_DONT_CARE)
            {
                hints->flags |= PAspect;
                hints->min_aspect.x = hints->max_aspect.x = window->numer;
                hints->min_aspect.y = hints->max_aspect.y = window->denom;
            }
        }
        else
        {
            hints->flags |= (PMinSize | PMaxSize);
            hints->min_width  = hints->max_width  = width;
            hints->min_height = hints->max_height = height;
        }
    }

    hints->flags |= PWinGravity;
    hints->win_gravity = StaticGravity;

    XSetWMNormalHints(_glfw.x11.display, window->x11.handle, hints);
    XFree(hints);
}