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
struct TYPE_5__ {struct TYPE_5__* name; struct TYPE_5__* modes; int /*<<< orphan*/  currentRamp; int /*<<< orphan*/  originalRamp; } ;
typedef  TYPE_1__ _GLFWmonitor ;

/* Variables and functions */
 int /*<<< orphan*/  _glfwFreeGammaArrays (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _glfwPlatformFreeMonitor (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void _glfwFreeMonitor(_GLFWmonitor* monitor)
{
    if (monitor == NULL)
        return;

    _glfwPlatformFreeMonitor(monitor);

    _glfwFreeGammaArrays(&monitor->originalRamp);
    _glfwFreeGammaArrays(&monitor->currentRamp);

    free(monitor->modes);
    free(monitor->name);
    free(monitor);
}