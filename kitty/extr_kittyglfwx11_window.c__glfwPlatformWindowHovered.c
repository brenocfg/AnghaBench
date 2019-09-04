#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ handle; } ;
struct TYPE_8__ {TYPE_2__ x11; } ;
typedef  TYPE_3__ _GLFWwindow ;
typedef  scalar_t__ Window ;
struct TYPE_6__ {int /*<<< orphan*/  display; scalar_t__ root; } ;
struct TYPE_9__ {TYPE_1__ x11; } ;

/* Variables and functions */
 int GLFW_FALSE ; 
 int GLFW_TRUE ; 
 int /*<<< orphan*/  XQueryPointer (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__*,int*,int*,int*,int*,unsigned int*) ; 
 TYPE_5__ _glfw ; 

int _glfwPlatformWindowHovered(_GLFWwindow* window)
{
    Window w = _glfw.x11.root;
    while (w)
    {
        Window root;
        int rootX, rootY, childX, childY;
        unsigned int mask;

        if (!XQueryPointer(_glfw.x11.display, w,
                           &root, &w, &rootX, &rootY, &childX, &childY, &mask))
        {
            return GLFW_FALSE;
        }

        if (w == window->x11.handle)
            return GLFW_TRUE;
    }

    return GLFW_FALSE;
}