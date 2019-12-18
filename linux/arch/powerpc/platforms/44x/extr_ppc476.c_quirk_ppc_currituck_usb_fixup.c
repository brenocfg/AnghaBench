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
 scalar_t__ of_machine_is_compatible (char*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 

__attribute__((used)) static void quirk_ppc_currituck_usb_fixup(struct pci_dev *dev)
{
	if (of_machine_is_compatible("ibm,currituck")) {
		pci_write_config_dword(dev, 0xe0, 0x0114231f);
		pci_write_config_dword(dev, 0xe4, 0x00006c40);
	}
}