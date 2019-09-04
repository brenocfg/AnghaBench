#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* maximize ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ callbacks; } ;
typedef  TYPE_2__ _GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void _glfwInputWindowMaximize(_GLFWwindow* window, GLFWbool maximized)
{
    if (window->callbacks.maximize)
        window->callbacks.maximize((GLFWwindow*) window, maximized);
}