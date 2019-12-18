#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  handle; } ;
struct TYPE_10__ {TYPE_2__ x11; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_8__ {int /*<<< orphan*/  display; } ;
struct TYPE_11__ {TYPE_1__ x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  XMapWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__ _glfw ; 
 scalar_t__ _glfwPlatformWindowVisible (TYPE_3__*) ; 
 int /*<<< orphan*/  waitForVisibilityNotify (TYPE_3__*) ; 

void _glfwPlatformShowWindow(_GLFWwindow* window)
{
    if (_glfwPlatformWindowVisible(window))
        return;

    XMapWindow(_glfw.x11.display, window->x11.handle);
    waitForVisibilityNotify(window);
}