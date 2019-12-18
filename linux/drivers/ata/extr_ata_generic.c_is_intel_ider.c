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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,scalar_t__*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,scalar_t__*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int,int) ; 

__attribute__((used)) static int is_intel_ider(struct pci_dev *dev)
{
	/* For Intel IDE the value at 0xF8 is only zero on IDE-R
	   interfaces */
	u32 r;
	u16 t;

	/* Check the manufacturing ID, it will be zero for IDE-R */
	pci_read_config_dword(dev, 0xF8, &r);
	/* Not IDE-R: punt so that ata_(old)piix gets it */
	if (r != 0)
		return 0;
	/* 0xF8 will also be zero on some early Intel IDE devices
	   but they will have a sane timing register */
	pci_read_config_word(dev, 0x40, &t);
	if (t != 0)
		return 0;
	/* Finally check if the timing register is writable so that
	   we eliminate any early devices hot-docked in a docking
	   station */
	pci_write_config_word(dev, 0x40, 1);
	pci_read_config_word(dev, 0x40, &t);
	if (t) {
		pci_write_config_word(dev, 0x40, 0);
		return 0;
	}
	return 1;
}