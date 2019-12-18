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
struct resource {scalar_t__ end; int /*<<< orphan*/  start; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct resource*) ; 
 struct resource* adapter_rom_resources ; 
 unsigned char* isa_bus_to_virt (int /*<<< orphan*/ ) ; 
 scalar_t__ match_id (struct pci_dev*,unsigned short,unsigned short) ; 
 scalar_t__ probe_kernel_address (unsigned char const*,unsigned short) ; 
 scalar_t__ probe_list (struct pci_dev*,unsigned short,unsigned char const*) ; 

__attribute__((used)) static struct resource *find_oprom(struct pci_dev *pdev)
{
	struct resource *oprom = NULL;
	int i;

	for (i = 0; i < ARRAY_SIZE(adapter_rom_resources); i++) {
		struct resource *res = &adapter_rom_resources[i];
		unsigned short offset, vendor, device, list, rev;
		const unsigned char *rom;

		if (res->end == 0)
			break;

		rom = isa_bus_to_virt(res->start);
		if (probe_kernel_address(rom + 0x18, offset) != 0)
			continue;

		if (probe_kernel_address(rom + offset + 0x4, vendor) != 0)
			continue;

		if (probe_kernel_address(rom + offset + 0x6, device) != 0)
			continue;

		if (match_id(pdev, vendor, device)) {
			oprom = res;
			break;
		}

		if (probe_kernel_address(rom + offset + 0x8, list) == 0 &&
		    probe_kernel_address(rom + offset + 0xc, rev) == 0 &&
		    rev >= 3 && list &&
		    probe_list(pdev, vendor, rom + offset + list)) {
			oprom = res;
			break;
		}
	}

	return oprom;
}