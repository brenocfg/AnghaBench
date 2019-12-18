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
struct TYPE_2__ {scalar_t__ target; int /*<<< orphan*/  irq_base; } ;
struct fsl_msi_softc {scalar_t__ sc_base; TYPE_1__ sc_map; struct fsl_msi_irq* sc_msi_irq; } ;
struct fsl_msi_irq {int irq; scalar_t__ reg; int /*<<< orphan*/  cookie; int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ FSL_MSI_TARGET ; 
 int FSL_NUM_IRQS ; 
 int /*<<< orphan*/  FSL_NUM_MSIS ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int M_BESTFIT ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 void* bus_get_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct fsl_msi_irq*,int /*<<< orphan*/ *) ; 
 struct fsl_msi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_msi_intr_filter ; 
 int /*<<< orphan*/  fsl_msis ; 
 int /*<<< orphan*/ * msi_vmem ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powerpc_register_pic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slist ; 
 int /*<<< orphan*/  vmem_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * vmem_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
fsl_msi_attach(device_t dev)
{
	struct fsl_msi_softc *sc;
	struct fsl_msi_irq *irq;
	int i;

	sc = device_get_softc(dev);

	if (msi_vmem == NULL)
		msi_vmem = vmem_create("MPIC MSI", 0, 0, 1, 1, M_BESTFIT | M_WAITOK);

	/* Manually play with resource entries. */
	sc->sc_base = bus_get_resource_start(dev, SYS_RES_MEMORY, 0);
	sc->sc_map.target = bus_get_resource_start(dev, SYS_RES_MEMORY, 1);

	if (sc->sc_map.target == 0)
		sc->sc_map.target = sc->sc_base + FSL_MSI_TARGET;

	for (i = 0; i < FSL_NUM_IRQS; i++) {
		irq = &sc->sc_msi_irq[i];
		irq->irq = i;
		irq->reg = sc->sc_base + 16 * i;
		irq->res = bus_alloc_resource_any(dev, SYS_RES_IRQ,
		    &irq->irq, RF_ACTIVE);
		bus_setup_intr(dev, irq->res, INTR_TYPE_MISC | INTR_MPSAFE,
		    fsl_msi_intr_filter, NULL, irq, &irq->cookie);
	}
	sc->sc_map.irq_base = powerpc_register_pic(dev, ofw_bus_get_node(dev),
	    FSL_NUM_MSIS, 0, 0);

	/* Let vmem and the IRQ subsystem work their magic for allocations. */
	vmem_add(msi_vmem, sc->sc_map.irq_base, FSL_NUM_MSIS, M_WAITOK);

	SLIST_INSERT_HEAD(&fsl_msis, &sc->sc_map, slist);

	return (0);
}