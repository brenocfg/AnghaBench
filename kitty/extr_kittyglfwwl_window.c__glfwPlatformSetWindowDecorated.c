#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  monitor; } ;
typedef  TYPE_1__ _GLFWwindow ;
typedef  scalar_t__ GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  createDecorations (TYPE_1__*) ; 
 int /*<<< orphan*/  destroyDecorations (TYPE_1__*) ; 

void _glfwPlatformSetWindowDecorated(_GLFWwindow* window, GLFWbool enabled)
{
    if (!window->monitor)
    {
        if (enabled)
            createDecorations(window);
        else
            destroyDecorations(window);
    }
}