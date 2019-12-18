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
 int atse_ethernet_option_bits_read_fdt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
atse_ethernet_option_bits_read(device_t dev)
{
	int error;

	error = atse_ethernet_option_bits_read_fdt(dev);
	if (error == 0)
		return (0);

	device_printf(dev, "Cannot read Ethernet addresses from flash.\n");

	return (error);
}