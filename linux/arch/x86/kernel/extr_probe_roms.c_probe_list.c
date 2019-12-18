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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ match_id (struct pci_dev*,unsigned short,unsigned short) ; 
 scalar_t__ probe_kernel_address (unsigned char const*,unsigned short) ; 

__attribute__((used)) static bool probe_list(struct pci_dev *pdev, unsigned short vendor,
		       const unsigned char *rom_list)
{
	unsigned short device;

	do {
		if (probe_kernel_address(rom_list, device) != 0)
			device = 0;

		if (device && match_id(pdev, vendor, device))
			break;

		rom_list += 2;
	} while (device);

	return !!device;
}