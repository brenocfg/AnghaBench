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
 int bus_generic_suspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_suspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isavga_suspend(device_t dev)
{
	int error;

	error = bus_generic_suspend(dev);
	if (error != 0)
		return (error);
	vga_suspend(dev);

	return (error);
}