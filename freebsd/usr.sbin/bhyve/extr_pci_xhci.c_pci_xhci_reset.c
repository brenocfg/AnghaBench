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
struct TYPE_2__ {int event_pcs; scalar_t__ er_events_cnt; scalar_t__ er_enq_idx; } ;
struct pci_xhci_softc {TYPE_1__ rtsregs; } ;

/* Variables and functions */
 int XHCI_MAX_SLOTS ; 
 int /*<<< orphan*/  pci_xhci_reset_slot (struct pci_xhci_softc*,int) ; 

__attribute__((used)) static void
pci_xhci_reset(struct pci_xhci_softc *sc)
{
	int i;

	sc->rtsregs.er_enq_idx = 0;
	sc->rtsregs.er_events_cnt = 0;
	sc->rtsregs.event_pcs = 1;

	for (i = 1; i <= XHCI_MAX_SLOTS; i++) {
		pci_xhci_reset_slot(sc, i);
	}
}