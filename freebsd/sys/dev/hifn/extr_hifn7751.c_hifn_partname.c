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
struct hifn_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
#define  PCI_PRODUCT_HIFN_6500 138 
#define  PCI_PRODUCT_HIFN_7751 137 
#define  PCI_PRODUCT_HIFN_7811 136 
#define  PCI_PRODUCT_HIFN_7951 135 
#define  PCI_PRODUCT_HIFN_7955 134 
#define  PCI_PRODUCT_HIFN_7956 133 
#define  PCI_PRODUCT_INVERTEX_AEON 132 
#define  PCI_PRODUCT_NETSEC_7751 131 
#define  PCI_VENDOR_HIFN 130 
#define  PCI_VENDOR_INVERTEX 129 
#define  PCI_VENDOR_NETSEC 128 
 int /*<<< orphan*/  pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char*
hifn_partname(struct hifn_softc *sc)
{
	/* XXX sprintf numbers when not decoded */
	switch (pci_get_vendor(sc->sc_dev)) {
	case PCI_VENDOR_HIFN:
		switch (pci_get_device(sc->sc_dev)) {
		case PCI_PRODUCT_HIFN_6500:	return "Hifn 6500";
		case PCI_PRODUCT_HIFN_7751:	return "Hifn 7751";
		case PCI_PRODUCT_HIFN_7811:	return "Hifn 7811";
		case PCI_PRODUCT_HIFN_7951:	return "Hifn 7951";
		case PCI_PRODUCT_HIFN_7955:	return "Hifn 7955";
		case PCI_PRODUCT_HIFN_7956:	return "Hifn 7956";
		}
		return "Hifn unknown-part";
	case PCI_VENDOR_INVERTEX:
		switch (pci_get_device(sc->sc_dev)) {
		case PCI_PRODUCT_INVERTEX_AEON:	return "Invertex AEON";
		}
		return "Invertex unknown-part";
	case PCI_VENDOR_NETSEC:
		switch (pci_get_device(sc->sc_dev)) {
		case PCI_PRODUCT_NETSEC_7751:	return "NetSec 7751";
		}
		return "NetSec unknown-part";
	}
	return "Unknown-vendor unknown-part";
}