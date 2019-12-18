#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int R_AL; int R_DL; int /*<<< orphan*/  R_AH; } ;
typedef  TYPE_1__ x86regs_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUP ; 
 scalar_t__ VGA_PCI_BIOS_SHADOW_ADDR ; 
 int /*<<< orphan*/  X86BIOS_PHYSTOOFF (scalar_t__) ; 
 int /*<<< orphan*/  X86BIOS_PHYSTOSEG (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ ) ; 
 int pci_get_function (int /*<<< orphan*/ ) ; 
 int pci_get_slot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_pci_is_boot_display (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x86bios_call (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x86bios_get_intr (int) ; 
 int /*<<< orphan*/ * x86bios_get_orm (scalar_t__) ; 
 int /*<<< orphan*/  x86bios_init_regs (TYPE_1__*) ; 

int
vga_pci_repost(device_t dev)
{
#if defined(__amd64__) || defined(__i386__)
	x86regs_t regs;

	if (!vga_pci_is_boot_display(dev))
		return (EINVAL);

	if (x86bios_get_orm(VGA_PCI_BIOS_SHADOW_ADDR) == NULL)
		return (ENOTSUP);

	x86bios_init_regs(&regs);

	regs.R_AH = pci_get_bus(dev);
	regs.R_AL = (pci_get_slot(dev) << 3) | (pci_get_function(dev) & 0x07);
	regs.R_DL = 0x80;

	device_printf(dev, "REPOSTing\n");
	x86bios_call(&regs, X86BIOS_PHYSTOSEG(VGA_PCI_BIOS_SHADOW_ADDR + 3),
	    X86BIOS_PHYSTOOFF(VGA_PCI_BIOS_SHADOW_ADDR + 3));

	x86bios_get_intr(0x10);

	return (0);
#else
	return (ENOTSUP);
#endif
}