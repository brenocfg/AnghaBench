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
struct TYPE_2__ {int usbsts; int dnctrl; int crcr; int dcbaap; int config; void* dcbaa_p; void* cr_p; int /*<<< orphan*/  usbcmd; } ;
struct pci_xhci_softc {TYPE_1__ opregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int MASK_64_HI (int) ; 
 int MASK_64_LO (int) ; 
 scalar_t__ XHCI_CAPLEN ; 
#define  XHCI_CONFIG 136 
#define  XHCI_CRCR_HI 135 
#define  XHCI_CRCR_LO 134 
 int XHCI_CRCR_LO_CA ; 
 int XHCI_CRCR_LO_CRR ; 
 int XHCI_CRCR_LO_CS ; 
 int XHCI_CRCR_LO_RCS ; 
#define  XHCI_DCBAAP_HI 133 
#define  XHCI_DCBAAP_LO 132 
#define  XHCI_DNCTRL 131 
 void* XHCI_GADDR (struct pci_xhci_softc*,int) ; 
#define  XHCI_PAGESIZE 130 
 int XHCI_STS_CNR ; 
 int XHCI_STS_EINT ; 
 int XHCI_STS_HSE ; 
 int XHCI_STS_PCD ; 
 int XHCI_STS_RSS ; 
 int XHCI_STS_SRE ; 
 int XHCI_STS_SSS ; 
#define  XHCI_USBCMD 129 
#define  XHCI_USBSTS 128 
 int /*<<< orphan*/  pci_xhci_portregs_write (struct pci_xhci_softc*,int,int) ; 
 int /*<<< orphan*/  pci_xhci_usbcmd_write (struct pci_xhci_softc*,int) ; 

__attribute__((used)) static void
pci_xhci_hostop_write(struct pci_xhci_softc *sc, uint64_t offset,
    uint64_t value)
{
	offset -= XHCI_CAPLEN;

	if (offset < 0x400)
		DPRINTF(("pci_xhci: hostop write offset 0x%lx: 0x%lx\r\n",
		         offset, value));

	switch (offset) {
	case XHCI_USBCMD:
		sc->opregs.usbcmd = pci_xhci_usbcmd_write(sc, value & 0x3F0F);
		break;

	case XHCI_USBSTS:
		/* clear bits on write */
		sc->opregs.usbsts &= ~(value &
		      (XHCI_STS_HSE|XHCI_STS_EINT|XHCI_STS_PCD|XHCI_STS_SSS|
		       XHCI_STS_RSS|XHCI_STS_SRE|XHCI_STS_CNR));
		break;

	case XHCI_PAGESIZE:
		/* read only */
		break;

	case XHCI_DNCTRL:
		sc->opregs.dnctrl = value & 0xFFFF;
		break;

	case XHCI_CRCR_LO:
		if (sc->opregs.crcr & XHCI_CRCR_LO_CRR) {
			sc->opregs.crcr &= ~(XHCI_CRCR_LO_CS|XHCI_CRCR_LO_CA);
			sc->opregs.crcr |= value &
			                   (XHCI_CRCR_LO_CS|XHCI_CRCR_LO_CA);
		} else {
			sc->opregs.crcr = MASK_64_HI(sc->opregs.crcr) |
			           (value & (0xFFFFFFC0 | XHCI_CRCR_LO_RCS));
		}
		break;

	case XHCI_CRCR_HI:
		if (!(sc->opregs.crcr & XHCI_CRCR_LO_CRR)) {
			sc->opregs.crcr = MASK_64_LO(sc->opregs.crcr) |
			                  (value << 32);

			sc->opregs.cr_p = XHCI_GADDR(sc,
			                  sc->opregs.crcr & ~0xF);
		}

		if (sc->opregs.crcr & XHCI_CRCR_LO_CS) {
			/* Stop operation of Command Ring */
		}

		if (sc->opregs.crcr & XHCI_CRCR_LO_CA) {
			/* Abort command */
		}

		break;

	case XHCI_DCBAAP_LO:
		sc->opregs.dcbaap = MASK_64_HI(sc->opregs.dcbaap) |
		                    (value & 0xFFFFFFC0);
		break;

	case XHCI_DCBAAP_HI:
		sc->opregs.dcbaap =  MASK_64_LO(sc->opregs.dcbaap) |
		                     (value << 32);
		sc->opregs.dcbaa_p = XHCI_GADDR(sc, sc->opregs.dcbaap & ~0x3FUL);

		DPRINTF(("pci_xhci: opregs dcbaap = 0x%lx (vaddr 0x%lx)\r\n",
		    sc->opregs.dcbaap, (uint64_t)sc->opregs.dcbaa_p));
		break;

	case XHCI_CONFIG:
		sc->opregs.config = value & 0x03FF;
		break;

	default:
		if (offset >= 0x400)
			pci_xhci_portregs_write(sc, offset, value);

		break;
	}
}