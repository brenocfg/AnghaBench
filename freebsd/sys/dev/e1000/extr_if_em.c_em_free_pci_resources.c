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
struct em_rx_queue {int /*<<< orphan*/  que_irq; } ;
struct adapter {scalar_t__ intr_type; int rx_num_queues; int /*<<< orphan*/ * ioport; int /*<<< orphan*/ * flash; int /*<<< orphan*/ * memory; int /*<<< orphan*/  irq; struct em_rx_queue* rx_queues; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ IFLIB_INTR_MSIX ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_irq_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
em_free_pci_resources(if_ctx_t ctx)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	struct em_rx_queue *que = adapter->rx_queues;
	device_t dev = iflib_get_dev(ctx);

	/* Release all MSI-X queue resources */
	if (adapter->intr_type == IFLIB_INTR_MSIX)
		iflib_irq_free(ctx, &adapter->irq);

	for (int i = 0; i < adapter->rx_num_queues; i++, que++) {
		iflib_irq_free(ctx, &que->que_irq);
	}

	if (adapter->memory != NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY,
		    rman_get_rid(adapter->memory), adapter->memory);
		adapter->memory = NULL;
	}

	if (adapter->flash != NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY,
		    rman_get_rid(adapter->flash), adapter->flash);
		adapter->flash = NULL;
	}

	if (adapter->ioport != NULL) {
		bus_release_resource(dev, SYS_RES_IOPORT,
		    rman_get_rid(adapter->ioport), adapter->ioport);
		adapter->ioport = NULL;
	}
}