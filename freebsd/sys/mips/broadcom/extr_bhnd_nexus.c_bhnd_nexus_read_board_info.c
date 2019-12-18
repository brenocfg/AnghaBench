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
struct bhnd_board_info {scalar_t__ board_vendor; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ PCI_VENDOR_BROADCOM ; 
 int bhnd_bus_generic_read_board_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bhnd_board_info*) ; 

__attribute__((used)) static int
bhnd_nexus_read_board_info(device_t dev, device_t child,
    struct bhnd_board_info *info)
{
	int error;

	/* Initialize with NVRAM-derived values */
	if ((error = bhnd_bus_generic_read_board_info(dev, child, info)))
		return (error);

	/* The board vendor should default to PCI_VENDOR_BROADCOM if not
	 * otherwise specified */
	if (info->board_vendor == 0)
		info->board_vendor = PCI_VENDOR_BROADCOM;

	return (0);
}