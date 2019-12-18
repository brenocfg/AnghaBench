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
struct ixl_vsi {int num_rx_queues; int /*<<< orphan*/  ctx; int /*<<< orphan*/  irq; struct ixl_rx_queue* rx_queues; } ;
struct ixl_rx_queue {int /*<<< orphan*/  que_irq; } ;
struct iavf_sc {int /*<<< orphan*/ * pci_mem; int /*<<< orphan*/  dev; struct ixl_vsi vsi; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iflib_irq_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
iavf_free_pci_resources(struct iavf_sc *sc)
{
	struct ixl_vsi		*vsi = &sc->vsi;
	struct ixl_rx_queue	*rx_que = vsi->rx_queues;
	device_t                dev = sc->dev;

	/* We may get here before stations are set up */
	if (rx_que == NULL)
		goto early;

	/* Release all interrupts */
	iflib_irq_free(vsi->ctx, &vsi->irq);

	for (int i = 0; i < vsi->num_rx_queues; i++, rx_que++)
		iflib_irq_free(vsi->ctx, &rx_que->que_irq);

early:
	if (sc->pci_mem != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY,
		    rman_get_rid(sc->pci_mem), sc->pci_mem);
}