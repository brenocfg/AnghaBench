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
typedef  size_t uint32_t ;
struct ocs_softc {TYPE_1__* reg; int /*<<< orphan*/  dev; int /*<<< orphan*/  dmat; int /*<<< orphan*/ * irq; scalar_t__ n_vec; } ;
struct TYPE_2__ {int /*<<< orphan*/ * res; int /*<<< orphan*/  rid; } ;

/* Variables and functions */
 size_t PCI_MAX_BAR ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_intr_teardown (struct ocs_softc*) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ocs_release_bus(struct ocs_softc *ocs)
{

	if (NULL != ocs) {
		uint32_t	i;

		ocs_intr_teardown(ocs);

		if (ocs->irq) {
			bus_release_resource(ocs->dev, SYS_RES_IRQ,
					rman_get_rid(ocs->irq), ocs->irq);

			if (ocs->n_vec) {
				pci_release_msi(ocs->dev);
				ocs->n_vec = 0;
			}

			ocs->irq = NULL;
		}

		bus_dma_tag_destroy(ocs->dmat);

		for (i = 0; i < PCI_MAX_BAR; i++) {
			if (ocs->reg[i].res) {
				bus_release_resource(ocs->dev, SYS_RES_MEMORY,
						ocs->reg[i].rid,
						ocs->reg[i].res);
			}
		}
	}
}