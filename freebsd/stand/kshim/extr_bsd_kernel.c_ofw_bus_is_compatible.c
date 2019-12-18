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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ofw_bus_is_compatible_cb (int /*<<< orphan*/ ,char*) ; 
 int stub1 (int /*<<< orphan*/ ,char*) ; 

int
ofw_bus_is_compatible(device_t dev, char *name)
{
	if (ofw_bus_is_compatible_cb == NULL)
		return (0);

	return ((*ofw_bus_is_compatible_cb)(dev, name));
}