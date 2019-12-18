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
struct ix_rx_queue {int /*<<< orphan*/  que_irq; } ;
struct adapter {scalar_t__ intr_type; int num_rx_queues; int /*<<< orphan*/ * pci_mem; int /*<<< orphan*/  irq; struct ix_rx_queue* rx_queues; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ IFLIB_INTR_MSIX ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_irq_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ixgbe_free_pci_resources(if_ctx_t ctx)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	struct         ix_rx_queue *que = adapter->rx_queues;
	device_t       dev = iflib_get_dev(ctx);

	/* Release all MSI-X queue resources */
	if (adapter->intr_type == IFLIB_INTR_MSIX)
		iflib_irq_free(ctx, &adapter->irq);

	if (que != NULL) {
		for (int i = 0; i < adapter->num_rx_queues; i++, que++) {
			iflib_irq_free(ctx, &que->que_irq);
		}
	}

	if (adapter->pci_mem != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY,
		    rman_get_rid(adapter->pci_mem), adapter->pci_mem);
}