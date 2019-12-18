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
struct mrsas_softc {int /*<<< orphan*/  mrsas_dev; int /*<<< orphan*/ * intr_handle; TYPE_1__* irq_context; int /*<<< orphan*/ ** mrsas_irq; scalar_t__* irq_id; scalar_t__ msix_enable; } ;
struct TYPE_2__ {scalar_t__ MSIxIndex; struct mrsas_softc* sc; } ;

/* Variables and functions */
 int FAIL ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_CAM ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrsas_isr ; 
 scalar_t__ mrsas_setup_msix (struct mrsas_softc*) ; 

__attribute__((used)) static int
mrsas_setup_irq(struct mrsas_softc *sc)
{
	if (sc->msix_enable && (mrsas_setup_msix(sc) == SUCCESS))
		device_printf(sc->mrsas_dev, "MSI-x interrupts setup success\n");

	else {
		device_printf(sc->mrsas_dev, "Fall back to legacy interrupt\n");
		sc->irq_context[0].sc = sc;
		sc->irq_context[0].MSIxIndex = 0;
		sc->irq_id[0] = 0;
		sc->mrsas_irq[0] = bus_alloc_resource_any(sc->mrsas_dev,
		    SYS_RES_IRQ, &sc->irq_id[0], RF_SHAREABLE | RF_ACTIVE);
		if (sc->mrsas_irq[0] == NULL) {
			device_printf(sc->mrsas_dev, "Cannot allocate legcay"
			    "interrupt\n");
			return (FAIL);
		}
		if (bus_setup_intr(sc->mrsas_dev, sc->mrsas_irq[0],
		    INTR_MPSAFE | INTR_TYPE_CAM, NULL, mrsas_isr,
		    &sc->irq_context[0], &sc->intr_handle[0])) {
			device_printf(sc->mrsas_dev, "Cannot set up legacy"
			    "interrupt\n");
			return (FAIL);
		}
	}
	return (0);
}