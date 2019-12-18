#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rt2560_softc {int sc_invalid; int /*<<< orphan*/  sc_sh; int /*<<< orphan*/  sc_st; } ;
struct TYPE_5__ {struct rt2560_softc sc_rt2560; } ;
struct ral_pci_softc {int /*<<< orphan*/  sc_ih; TYPE_2__* sc_opns; int /*<<< orphan*/ * irq; int /*<<< orphan*/ * mem; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {int (* attach ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  intr; } ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ral_pci_softc*,int /*<<< orphan*/ *) ; 
 struct ral_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 scalar_t__ ral_msi_disable ; 
 int /*<<< orphan*/  ral_pci_detach (int /*<<< orphan*/ ) ; 
 TYPE_2__ ral_rt2560_opns ; 
 TYPE_2__ ral_rt2661_opns ; 
 TYPE_2__ ral_rt2860_opns ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ral_pci_attach(device_t dev)
{
	struct ral_pci_softc *psc = device_get_softc(dev);
	struct rt2560_softc *sc = &psc->u.sc_rt2560;
	int count, error, rid;

	pci_enable_busmaster(dev);

	switch (pci_get_device(dev)) {
	case 0x0201:
		psc->sc_opns = &ral_rt2560_opns;
		break;
	case 0x0301:
	case 0x0302:
	case 0x0401:
		psc->sc_opns = &ral_rt2661_opns;
		break;
	default:
		psc->sc_opns = &ral_rt2860_opns;
		break;
	}

	rid = PCIR_BAR(0);
	psc->mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (psc->mem == NULL) {
		device_printf(dev, "could not allocate memory resource\n");
		return ENXIO;
	}

	sc->sc_st = rman_get_bustag(psc->mem);
	sc->sc_sh = rman_get_bushandle(psc->mem);
	sc->sc_invalid = 1;
	
	rid = 0;
	if (ral_msi_disable == 0) {
		count = 1;
		if (pci_alloc_msi(dev, &count) == 0)
			rid = 1;
	}
	psc->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid, RF_ACTIVE |
	    (rid != 0 ? 0 : RF_SHAREABLE));
	if (psc->irq == NULL) {
		device_printf(dev, "could not allocate interrupt resource\n");
		pci_release_msi(dev);
		bus_release_resource(dev, SYS_RES_MEMORY,
		    rman_get_rid(psc->mem), psc->mem);
		return ENXIO;
	}

	error = (*psc->sc_opns->attach)(dev, pci_get_device(dev));
	if (error != 0) {
		(void)ral_pci_detach(dev);
		return error;
	}

	/*
	 * Hook our interrupt after all initialization is complete.
	 */
	error = bus_setup_intr(dev, psc->irq, INTR_TYPE_NET | INTR_MPSAFE,
	    NULL, psc->sc_opns->intr, psc, &psc->sc_ih);
	if (error != 0) {
		device_printf(dev, "could not set up interrupt\n");
		(void)ral_pci_detach(dev);
		return error;
	}
	sc->sc_invalid = 0;
	
	return 0;
}