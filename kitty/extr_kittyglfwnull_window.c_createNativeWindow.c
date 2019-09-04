#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_2__ _GLFWwndconfig ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_8__ {TYPE_1__ null; } ;
typedef  TYPE_3__ _GLFWwindow ;

/* Variables and functions */
 int GLFW_TRUE ; 

__attribute__((used)) static int createNativeWindow(_GLFWwindow* window,
                              const _GLFWwndconfig* wndconfig)
{
    window->null.width = wndconfig->width;
    window->null.height = wndconfig->height;

    return GLFW_TRUE;
}