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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  BCOM_DEVICEID_BCM5717 148 
#define  BCOM_DEVICEID_BCM5717C 147 
#define  BCOM_DEVICEID_BCM5718 146 
#define  BCOM_DEVICEID_BCM5719 145 
#define  BCOM_DEVICEID_BCM5720 144 
#define  BCOM_DEVICEID_BCM5725 143 
#define  BCOM_DEVICEID_BCM5727 142 
#define  BCOM_DEVICEID_BCM5762 141 
#define  BCOM_DEVICEID_BCM57761 140 
#define  BCOM_DEVICEID_BCM57762 139 
#define  BCOM_DEVICEID_BCM57764 138 
#define  BCOM_DEVICEID_BCM57765 137 
#define  BCOM_DEVICEID_BCM57766 136 
#define  BCOM_DEVICEID_BCM57767 135 
#define  BCOM_DEVICEID_BCM57781 134 
#define  BCOM_DEVICEID_BCM57782 133 
#define  BCOM_DEVICEID_BCM57785 132 
#define  BCOM_DEVICEID_BCM57786 131 
#define  BCOM_DEVICEID_BCM57787 130 
#define  BCOM_DEVICEID_BCM57791 129 
#define  BCOM_DEVICEID_BCM57795 128 
 scalar_t__ BGE_ASICREV (int) ; 
 scalar_t__ BGE_ASICREV_USE_PRODID_REG ; 
 int BGE_CHIPID_BCM5720_A0 ; 
 int BGE_PCIMISCCTL_ASICREV_SHIFT ; 
 int /*<<< orphan*/  BGE_PCI_GEN15_PRODID_ASICREV ; 
 int /*<<< orphan*/  BGE_PCI_GEN2_PRODID_ASICREV ; 
 int /*<<< orphan*/  BGE_PCI_MISC_CTL ; 
 int /*<<< orphan*/  BGE_PCI_PRODID_ASICREV ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32_t
bge_chipid(device_t dev)
{
	uint32_t id;

	id = pci_read_config(dev, BGE_PCI_MISC_CTL, 4) >>
	    BGE_PCIMISCCTL_ASICREV_SHIFT;
	if (BGE_ASICREV(id) == BGE_ASICREV_USE_PRODID_REG) {
		/*
		 * Find the ASCI revision.  Different chips use different
		 * registers.
		 */
		switch (pci_get_device(dev)) {
		case BCOM_DEVICEID_BCM5717C:
			/* 5717 C0 seems to belong to 5720 line. */
			id = BGE_CHIPID_BCM5720_A0;
			break;
		case BCOM_DEVICEID_BCM5717:
		case BCOM_DEVICEID_BCM5718:
		case BCOM_DEVICEID_BCM5719:
		case BCOM_DEVICEID_BCM5720:
		case BCOM_DEVICEID_BCM5725:
		case BCOM_DEVICEID_BCM5727:
		case BCOM_DEVICEID_BCM5762:
		case BCOM_DEVICEID_BCM57764:
		case BCOM_DEVICEID_BCM57767:
		case BCOM_DEVICEID_BCM57787:
			id = pci_read_config(dev,
			    BGE_PCI_GEN2_PRODID_ASICREV, 4);
			break;
		case BCOM_DEVICEID_BCM57761:
		case BCOM_DEVICEID_BCM57762:
		case BCOM_DEVICEID_BCM57765:
		case BCOM_DEVICEID_BCM57766:
		case BCOM_DEVICEID_BCM57781:
		case BCOM_DEVICEID_BCM57782:
		case BCOM_DEVICEID_BCM57785:
		case BCOM_DEVICEID_BCM57786:
		case BCOM_DEVICEID_BCM57791:
		case BCOM_DEVICEID_BCM57795:
			id = pci_read_config(dev,
			    BGE_PCI_GEN15_PRODID_ASICREV, 4);
			break;
		default:
			id = pci_read_config(dev, BGE_PCI_PRODID_ASICREV, 4);
		}
	}
	return (id);
}