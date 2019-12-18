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
struct xhci_trb {int qwTrb0; int /*<<< orphan*/  dwTrb3; } ;
struct pci_xhci_softc {int dummy; } ;

/* Variables and functions */
 struct xhci_trb* XHCI_GADDR (struct pci_xhci_softc*,int) ; 
 scalar_t__ XHCI_TRB_3_TYPE_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ XHCI_TRB_TYPE_LINK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

struct xhci_trb *
pci_xhci_trb_next(struct pci_xhci_softc *sc, struct xhci_trb *curtrb,
    uint64_t *guestaddr)
{
	struct xhci_trb *next;

	assert(curtrb != NULL);

	if (XHCI_TRB_3_TYPE_GET(curtrb->dwTrb3) == XHCI_TRB_TYPE_LINK) {
		if (guestaddr)
			*guestaddr = curtrb->qwTrb0 & ~0xFUL;
		
		next = XHCI_GADDR(sc, curtrb->qwTrb0 & ~0xFUL);
	} else {
		if (guestaddr)
			*guestaddr += sizeof(struct xhci_trb) & ~0xFUL;

		next = curtrb + 1;
	}

	return (next);
}