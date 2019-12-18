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
typedef  scalar_t__ u16 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ OCXL_DVSEC_ID_OFFSET ; 
 scalar_t__ OCXL_DVSEC_VENDOR_OFFSET ; 
 int /*<<< orphan*/  OCXL_EXT_CAP_ID_DVSEC ; 
 scalar_t__ PCI_VENDOR_ID_IBM ; 
 int pci_find_next_ext_capability (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int find_dvsec_from_pos(struct pci_dev *dev, int dvsec_id, int pos)
{
	int vsec = pos;
	u16 vendor, id;

	while ((vsec = pci_find_next_ext_capability(dev, vsec,
						    OCXL_EXT_CAP_ID_DVSEC))) {
		pci_read_config_word(dev, vsec + OCXL_DVSEC_VENDOR_OFFSET,
				&vendor);
		pci_read_config_word(dev, vsec + OCXL_DVSEC_ID_OFFSET, &id);
		if (vendor == PCI_VENDOR_ID_IBM && id == dvsec_id)
			return vsec;
	}
	return 0;
}