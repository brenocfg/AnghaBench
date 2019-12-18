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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_VENDOR_ID_INTEL ; 
 int /*<<< orphan*/  SKX_CAPID6 ; 
 int /*<<< orphan*/  SKX_CHA_BIT_MASK ; 
 int hweight32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int skx_count_chabox(void)
{
	struct pci_dev *dev = NULL;
	u32 val = 0;

	dev = pci_get_device(PCI_VENDOR_ID_INTEL, 0x2083, dev);
	if (!dev)
		goto out;

	pci_read_config_dword(dev, SKX_CAPID6, &val);
	val &= SKX_CHA_BIT_MASK;
out:
	pci_dev_put(dev);
	return hweight32(val);
}