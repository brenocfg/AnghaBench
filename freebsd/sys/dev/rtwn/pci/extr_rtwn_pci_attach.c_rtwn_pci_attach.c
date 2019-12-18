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
typedef  int /*<<< orphan*/  uint32_t ;
struct ieee80211com {int /*<<< orphan*/  ic_name; } ;
struct rtwn_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_dev; struct ieee80211com sc_ic; } ;
struct rtwn_pci_softc {int /*<<< orphan*/  pc_ih; int /*<<< orphan*/ * irq; int /*<<< orphan*/ * mem; int /*<<< orphan*/  pc_sh; int /*<<< orphan*/  pc_st; struct rtwn_softc pc_sc; } ;
struct rtwn_pci_ident {int /*<<< orphan*/  chip; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  PCIEM_LINK_CTL_ASPMC ; 
 scalar_t__ PCIER_LINK_CTL ; 
 int PCIR_BAR (int) ; 
 int /*<<< orphan*/  PCIY_EXPRESS ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int RTWN_PCI_NTXQUEUES ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rtwn_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct rtwn_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int rtwn_attach (struct rtwn_softc*) ; 
 int rtwn_pci_alloc_rx_list (struct rtwn_softc*) ; 
 int rtwn_pci_alloc_tx_list (struct rtwn_softc*,int) ; 
 int /*<<< orphan*/  rtwn_pci_attach_methods (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_pci_attach_private (struct rtwn_pci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_pci_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_pci_intr ; 
 struct rtwn_pci_ident* rtwn_pci_probe_sub (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_sysctlattach (struct rtwn_softc*) ; 

__attribute__((used)) static int
rtwn_pci_attach(device_t dev)
{
	const struct rtwn_pci_ident *ident;
	struct rtwn_pci_softc *pc = device_get_softc(dev);
	struct rtwn_softc *sc = &pc->pc_sc;
	struct ieee80211com *ic = &sc->sc_ic;
	uint32_t lcsr;
	int cap_off, i, error, rid;

	ident = rtwn_pci_probe_sub(dev);
	if (ident == NULL)
		return (ENXIO);

	/*
	 * Get the offset of the PCI Express Capability Structure in PCI
	 * Configuration Space.
	 */
	error = pci_find_cap(dev, PCIY_EXPRESS, &cap_off);
	if (error != 0) {
		device_printf(dev, "PCIe capability structure not found!\n");
		return (error);
	}

	/* Enable bus-mastering. */
	pci_enable_busmaster(dev);

	rid = PCIR_BAR(2);
	pc->mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (pc->mem == NULL) {
		device_printf(dev, "can't map mem space\n");
		return (ENOMEM);
	}
	pc->pc_st = rman_get_bustag(pc->mem);
	pc->pc_sh = rman_get_bushandle(pc->mem);

	/* Install interrupt handler. */
	rid = 1;
	if (pci_alloc_msi(dev, &rid) == 0)
		rid = 1;
	else
		rid = 0;
	pc->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid, RF_ACTIVE |
	    (rid != 0 ? 0 : RF_SHAREABLE));
	if (pc->irq == NULL) {
		device_printf(dev, "can't map interrupt\n");
		goto detach;
	}

	/* Disable PCIe Active State Power Management (ASPM). */
	lcsr = pci_read_config(dev, cap_off + PCIER_LINK_CTL, 4);
	lcsr &= ~PCIEM_LINK_CTL_ASPMC;
	pci_write_config(dev, cap_off + PCIER_LINK_CTL, lcsr, 4);

	sc->sc_dev = dev;
	ic->ic_name = device_get_nameunit(dev);

	/* Need to be initialized early. */
	rtwn_sysctlattach(sc);
	mtx_init(&sc->sc_mtx, ic->ic_name, MTX_NETWORK_LOCK, MTX_DEF);

	rtwn_pci_attach_methods(sc);
	rtwn_pci_attach_private(pc, ident->chip);

	/* Allocate Tx/Rx buffers. */
	error = rtwn_pci_alloc_rx_list(sc);
	if (error != 0) {
		device_printf(dev,
		    "could not allocate Rx buffers, error %d\n",
		    error);
		goto detach;
	}
	for (i = 0; i < RTWN_PCI_NTXQUEUES; i++) {
		error = rtwn_pci_alloc_tx_list(sc, i);
		if (error != 0) {
			device_printf(dev,
			    "could not allocate Tx buffers, error %d\n",
			    error);
			goto detach;
		}
	}

	/* Generic attach. */
	error = rtwn_attach(sc);
	if (error != 0)
		goto detach;

	/*
	 * Hook our interrupt after all initialization is complete.
	 */
	error = bus_setup_intr(dev, pc->irq, INTR_TYPE_NET | INTR_MPSAFE,
	    NULL, rtwn_pci_intr, sc, &pc->pc_ih);
	if (error != 0) {
		device_printf(dev, "can't establish interrupt, error %d\n",
		    error);
		goto detach;
	}

	return (0);

detach:
	rtwn_pci_detach(dev);		/* failure */
	return (ENXIO);
}