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
 int atse_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atse_detach_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

int
atse_detach_dev(device_t dev)
{
	int error;

	error = atse_detach(dev);
	if (error) {
		/* We are basically in undefined state now. */
		device_printf(dev, "atse_detach() failed: %d\n", error);
		return (error);
	}

	atse_detach_resources(dev);

	return (0);
}