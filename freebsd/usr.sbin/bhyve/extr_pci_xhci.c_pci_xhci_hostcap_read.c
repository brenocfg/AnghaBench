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
typedef  int uint64_t ;
struct pci_xhci_softc {int caplength; int hcsparams1; int hcsparams2; int hcsparams3; int hccparams1; int dboff; int rtsoff; int hccparams2; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
#define  XHCI_CAPLENGTH 135 
#define  XHCI_DBOFF 134 
#define  XHCI_HCCPRAMS2 133 
#define  XHCI_HCSPARAMS0 132 
#define  XHCI_HCSPARAMS1 131 
#define  XHCI_HCSPARAMS2 130 
#define  XHCI_HCSPARAMS3 129 
#define  XHCI_RTSOFF 128 

__attribute__((used)) static uint64_t
pci_xhci_hostcap_read(struct pci_xhci_softc *sc, uint64_t offset)
{
	uint64_t	value;

	switch (offset) {
	case XHCI_CAPLENGTH:	/* 0x00 */
		value = sc->caplength;
		break;

	case XHCI_HCSPARAMS1:	/* 0x04 */
		value = sc->hcsparams1;
		break;

	case XHCI_HCSPARAMS2:	/* 0x08 */
		value = sc->hcsparams2;
		break;

	case XHCI_HCSPARAMS3:	/* 0x0C */
		value = sc->hcsparams3;
		break;

	case XHCI_HCSPARAMS0:	/* 0x10 */
		value = sc->hccparams1;
		break;

	case XHCI_DBOFF:	/* 0x14 */
		value = sc->dboff;
		break;

	case XHCI_RTSOFF:	/* 0x18 */
		value = sc->rtsoff;
		break;

	case XHCI_HCCPRAMS2:	/* 0x1C */
		value = sc->hccparams2;
		break;

	default:
		value = 0;
		break;
	}

	DPRINTF(("pci_xhci: hostcap read offset 0x%lx -> 0x%lx\r\n",
	        offset, value));

	return (value);
}