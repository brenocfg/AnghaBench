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
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/ * devclass_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 char* VGA_DRIVER_NAME ; 
 int /*<<< orphan*/  X86BIOS_PHYSTOOFF (scalar_t__) ; 
 int /*<<< orphan*/  X86BIOS_PHYSTOSEG (scalar_t__) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/ * devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ devclass_get_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ***,int*) ; 
 scalar_t__ device_get_flags (int /*<<< orphan*/ *) ; 
 char* device_get_nameunit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ *) ; 
 int pci_get_function (int /*<<< orphan*/ *) ; 
 int pci_get_slot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ vesa_bios_offs ; 
 int /*<<< orphan*/  x86bios_call (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ x86bios_get_intr (int) ; 
 int /*<<< orphan*/ * x86bios_get_orm (scalar_t__) ; 
 int /*<<< orphan*/  x86bios_init_regs (TYPE_1__*) ; 
 scalar_t__ x86bios_match_device (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vesa_bios_post(void)
{
	x86regs_t regs;
	devclass_t dc;
	device_t *devs;
	device_t dev;
	int count, i, is_pci;

	if (x86bios_get_orm(vesa_bios_offs) == NULL)
		return (1);

	dev = NULL;
	is_pci = 0;

	/* Find the matching PCI video controller. */
	dc = devclass_find("vgapci");
	if (dc != NULL && devclass_get_devices(dc, &devs, &count) == 0) {
		for (i = 0; i < count; i++)
			if (device_get_flags(devs[i]) != 0 &&
			    x86bios_match_device(vesa_bios_offs, devs[i])) {
				dev = devs[i];
				is_pci = 1;
				break;
			}
		free(devs, M_TEMP);
	}

	/* Try VGA if a PCI device is not found. */
	if (dev == NULL) {
		dc = devclass_find(VGA_DRIVER_NAME);
		if (dc != NULL)
			dev = devclass_get_device(dc, 0);
	}

	if (bootverbose)
		printf("%s: calling BIOS POST\n",
		    dev == NULL ? "VESA" : device_get_nameunit(dev));

	x86bios_init_regs(&regs);
	if (is_pci) {
		regs.R_AH = pci_get_bus(dev);
		regs.R_AL = (pci_get_slot(dev) << 3) |
		    (pci_get_function(dev) & 0x07);
	}
	regs.R_DL = 0x80;
	x86bios_call(&regs, X86BIOS_PHYSTOSEG(vesa_bios_offs + 3),
	    X86BIOS_PHYSTOOFF(vesa_bios_offs + 3));

	if (x86bios_get_intr(0x10) == 0)
		return (1);

	return (0);
}