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
struct rtwn_softc {int /*<<< orphan*/  sc_mtx; } ;
struct rtwn_pci_softc {int /*<<< orphan*/ * mem; int /*<<< orphan*/ * irq; int /*<<< orphan*/  pc_ih; struct rtwn_softc pc_sc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int RTWN_PCI_NTXQUEUES ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rtwn_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtwn_detach (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_detach_private (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_pci_free_rx_list (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_pci_free_tx_list (struct rtwn_softc*,int) ; 

__attribute__((used)) static int
rtwn_pci_detach(device_t dev)
{
	struct rtwn_pci_softc *pc = device_get_softc(dev);
	struct rtwn_softc *sc = &pc->pc_sc;
	int i;

	/* Generic detach. */
	rtwn_detach(sc);

	/* Uninstall interrupt handler. */
	if (pc->irq != NULL) {
		bus_teardown_intr(dev, pc->irq, pc->pc_ih);
		bus_release_resource(dev, SYS_RES_IRQ, rman_get_rid(pc->irq),
		    pc->irq);
		pci_release_msi(dev);
	}

	/* Free Tx/Rx buffers. */
	for (i = 0; i < RTWN_PCI_NTXQUEUES; i++)
		rtwn_pci_free_tx_list(sc, i);
	rtwn_pci_free_rx_list(sc);

	if (pc->mem != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY,
		    rman_get_rid(pc->mem), pc->mem);

	rtwn_detach_private(sc);
	mtx_destroy(&sc->sc_mtx);

	return (0);
}