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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFORCE2_BOOTFSB ; 
 int /*<<< orphan*/  NFORCE2_PLLENABLE ; 
 int /*<<< orphan*/  NFORCE2_PLLREG ; 
 int /*<<< orphan*/  PCI_ANY_ID ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_NVIDIA ; 
 int nforce2_calc_fsb (int) ; 
 struct pci_dev* nforce2_dev ; 
 struct pci_dev* pci_get_subsys (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static unsigned int nforce2_fsb_read(int bootfsb)
{
	struct pci_dev *nforce2_sub5;
	u32 fsb, temp = 0;

	/* Get chipset boot FSB from subdevice 5 (FSB at boot-time) */
	nforce2_sub5 = pci_get_subsys(PCI_VENDOR_ID_NVIDIA, 0x01EF,
				PCI_ANY_ID, PCI_ANY_ID, NULL);
	if (!nforce2_sub5)
		return 0;

	pci_read_config_dword(nforce2_sub5, NFORCE2_BOOTFSB, &fsb);
	fsb /= 1000000;

	/* Check if PLL register is already set */
	pci_read_config_byte(nforce2_dev, NFORCE2_PLLENABLE, (u8 *)&temp);

	if (bootfsb || !temp)
		return fsb;

	/* Use PLL register FSB value */
	pci_read_config_dword(nforce2_dev, NFORCE2_PLLREG, &temp);
	fsb = nforce2_calc_fsb(temp);

	return fsb;
}