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
struct ubsec_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
#define  PCI_PRODUCT_BLUESTEEL_5601 141 
#define  PCI_PRODUCT_BROADCOM_5801 140 
#define  PCI_PRODUCT_BROADCOM_5802 139 
#define  PCI_PRODUCT_BROADCOM_5805 138 
#define  PCI_PRODUCT_BROADCOM_5820 137 
#define  PCI_PRODUCT_BROADCOM_5821 136 
#define  PCI_PRODUCT_BROADCOM_5822 135 
#define  PCI_PRODUCT_BROADCOM_5823 134 
#define  PCI_PRODUCT_BROADCOM_5825 133 
#define  PCI_PRODUCT_SUN_5821 132 
#define  PCI_PRODUCT_SUN_SCA1K 131 
#define  PCI_VENDOR_BLUESTEEL 130 
#define  PCI_VENDOR_BROADCOM 129 
#define  PCI_VENDOR_SUN 128 
 int /*<<< orphan*/  pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char*
ubsec_partname(struct ubsec_softc *sc)
{
	/* XXX sprintf numbers when not decoded */
	switch (pci_get_vendor(sc->sc_dev)) {
	case PCI_VENDOR_BROADCOM:
		switch (pci_get_device(sc->sc_dev)) {
		case PCI_PRODUCT_BROADCOM_5801:	return "Broadcom 5801";
		case PCI_PRODUCT_BROADCOM_5802:	return "Broadcom 5802";
		case PCI_PRODUCT_BROADCOM_5805:	return "Broadcom 5805";
		case PCI_PRODUCT_BROADCOM_5820:	return "Broadcom 5820";
		case PCI_PRODUCT_BROADCOM_5821:	return "Broadcom 5821";
		case PCI_PRODUCT_BROADCOM_5822:	return "Broadcom 5822";
		case PCI_PRODUCT_BROADCOM_5823:	return "Broadcom 5823";
		case PCI_PRODUCT_BROADCOM_5825:	return "Broadcom 5825";
		}
		return "Broadcom unknown-part";
	case PCI_VENDOR_BLUESTEEL:
		switch (pci_get_device(sc->sc_dev)) {
		case PCI_PRODUCT_BLUESTEEL_5601: return "Bluesteel 5601";
		}
		return "Bluesteel unknown-part";
	case PCI_VENDOR_SUN:
		switch (pci_get_device(sc->sc_dev)) {
		case PCI_PRODUCT_SUN_5821: return "Sun Crypto 5821";
		case PCI_PRODUCT_SUN_SCA1K: return "Sun Crypto 1K";
		}
		return "Sun unknown-part";
	}
	return "Unknown-vendor unknown-part";
}