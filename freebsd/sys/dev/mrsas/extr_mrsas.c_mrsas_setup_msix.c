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
struct mrsas_softc {int msix_vectors; int* irq_id; int /*<<< orphan*/  mrsas_dev; int /*<<< orphan*/ * intr_handle; TYPE_1__* irq_context; int /*<<< orphan*/ ** mrsas_irq; } ;
struct TYPE_2__ {int MSIxIndex; struct mrsas_softc* sc; } ;

/* Variables and functions */
 int FAIL ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_CAM ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrsas_isr ; 
 int /*<<< orphan*/  mrsas_teardown_intr (struct mrsas_softc*) ; 

__attribute__((used)) static int
mrsas_setup_msix(struct mrsas_softc *sc)
{
	int i;

	for (i = 0; i < sc->msix_vectors; i++) {
		sc->irq_context[i].sc = sc;
		sc->irq_context[i].MSIxIndex = i;
		sc->irq_id[i] = i + 1;
		sc->mrsas_irq[i] = bus_alloc_resource_any
		    (sc->mrsas_dev, SYS_RES_IRQ, &sc->irq_id[i]
		    ,RF_ACTIVE);
		if (sc->mrsas_irq[i] == NULL) {
			device_printf(sc->mrsas_dev, "Can't allocate MSI-x\n");
			goto irq_alloc_failed;
		}
		if (bus_setup_intr(sc->mrsas_dev,
		    sc->mrsas_irq[i],
		    INTR_MPSAFE | INTR_TYPE_CAM,
		    NULL, mrsas_isr, &sc->irq_context[i],
		    &sc->intr_handle[i])) {
			device_printf(sc->mrsas_dev,
			    "Cannot set up MSI-x interrupt handler\n");
			goto irq_alloc_failed;
		}
	}
	return SUCCESS;

irq_alloc_failed:
	mrsas_teardown_intr(sc);
	return (FAIL);
}