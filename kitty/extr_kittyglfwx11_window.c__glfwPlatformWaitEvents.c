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

/* Variables and functions */
 scalar_t__ _glfwDispatchX11Events () ; 
 int /*<<< orphan*/  handleEvents (double) ; 

void _glfwPlatformWaitEvents(void)
{
    double timeout = _glfwDispatchX11Events() ? 0 : -1;
    handleEvents(timeout);
}