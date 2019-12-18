#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_2__ {int usbcmd; int usbsts; int pgsz; int dnctrl; int crcr; int dcbaap; int config; } ;
struct pci_xhci_softc {TYPE_1__ opregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int XHCI_CAPLEN ; 
#define  XHCI_CONFIG 136 
#define  XHCI_CRCR_HI 135 
#define  XHCI_CRCR_LO 134 
 int XHCI_CRCR_LO_CRR ; 
#define  XHCI_DCBAAP_HI 133 
#define  XHCI_DCBAAP_LO 132 
#define  XHCI_DNCTRL 131 
#define  XHCI_PAGESIZE 130 
#define  XHCI_USBCMD 129 
#define  XHCI_USBSTS 128 
 int pci_xhci_portregs_read (struct pci_xhci_softc*,int) ; 

__attribute__((used)) static uint64_t
pci_xhci_hostop_read(struct pci_xhci_softc *sc, uint64_t offset)
{
	uint64_t value;

	offset = (offset - XHCI_CAPLEN);

	switch (offset) {
	case XHCI_USBCMD:	/* 0x00 */
		value = sc->opregs.usbcmd;
		break;

	case XHCI_USBSTS:	/* 0x04 */
		value = sc->opregs.usbsts;
		break;

	case XHCI_PAGESIZE:	/* 0x08 */
		value = sc->opregs.pgsz;
		break;

	case XHCI_DNCTRL:	/* 0x14 */
		value = sc->opregs.dnctrl;
		break;

	case XHCI_CRCR_LO:	/* 0x18 */
		value = sc->opregs.crcr & XHCI_CRCR_LO_CRR;
		break;

	case XHCI_CRCR_HI:	/* 0x1C */
		value = 0;
		break;

	case XHCI_DCBAAP_LO:	/* 0x30 */
		value = sc->opregs.dcbaap & 0xFFFFFFFF;
		break;

	case XHCI_DCBAAP_HI:	/* 0x34 */
		value = (sc->opregs.dcbaap >> 32) & 0xFFFFFFFF;
		break;

	case XHCI_CONFIG:	/* 0x38 */
		value = sc->opregs.config;
		break;

	default:
		if (offset >= 0x400)
			value = pci_xhci_portregs_read(sc, offset);
		else
			value = 0;

		break;
	}

	if (offset < 0x400)
		DPRINTF(("pci_xhci: hostop read offset 0x%lx -> 0x%lx\r\n",
		        offset, value));

	return (value);
}