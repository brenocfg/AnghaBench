#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int num_slices; int /*<<< orphan*/  dev; int /*<<< orphan*/ * msix_table_res; int /*<<< orphan*/ ** msix_irq_res; int /*<<< orphan*/ ** msix_ih; } ;
typedef  TYPE_1__ mxge_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int PCIR_BAR (int) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mxge_rem_msix_irqs(mxge_softc_t *sc)
{
	int i, rid;

	for (i = 0; i < sc->num_slices; i++) {
		if (sc->msix_ih[i] != NULL) {
			bus_teardown_intr(sc->dev, sc->msix_irq_res[i],
					  sc->msix_ih[i]);
			sc->msix_ih[i] = NULL;
		}
	}
	free(sc->msix_ih, M_DEVBUF);

	for (i = 0; i < sc->num_slices; i++) {
		rid = i + 1;
		if (sc->msix_irq_res[i] != NULL)
			bus_release_resource(sc->dev, SYS_RES_IRQ, rid,
					     sc->msix_irq_res[i]);
		sc->msix_irq_res[i] = NULL;
	}
	free(sc->msix_irq_res, M_DEVBUF);

	bus_release_resource(sc->dev, SYS_RES_MEMORY, PCIR_BAR(2),
			     sc->msix_table_res);

	pci_release_msi(sc->dev);
	return;
}