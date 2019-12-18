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
struct sym_pci_chip {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sym_find_firmware (struct sym_pci_chip const*) ; 
 struct sym_pci_chip* sym_find_pci_chip (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sym_pci_probe(device_t dev)
{
	const struct	sym_pci_chip *chip;

	chip = sym_find_pci_chip(dev);
	if (chip && sym_find_firmware(chip)) {
		device_set_desc(dev, chip->name);
		return BUS_PROBE_DEFAULT;
	}
	return ENXIO;
}