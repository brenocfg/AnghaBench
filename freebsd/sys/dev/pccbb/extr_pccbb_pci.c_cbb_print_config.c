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
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
cbb_print_config(device_t dev)
{
	int i;

	device_printf(dev, "PCI Configuration space:");
	for (i = 0; i < 256; i += 4) {
		if (i % 16 == 0)
			printf("\n  0x%02x: ", i);
		printf("0x%08x ", pci_read_config(dev, i, 4));
	}
	printf("\n");
}