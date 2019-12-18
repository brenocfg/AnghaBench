#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  _GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  _glfwPlatformGetWindowSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  updateNormalHints (int /*<<< orphan*/ *,int,int) ; 

void _glfwPlatformSetWindowResizable(_GLFWwindow* window, GLFWbool enabled)
{
    int width, height;
    _glfwPlatformGetWindowSize(window, &width, &height);
    updateNormalHints(window, width, height);
}