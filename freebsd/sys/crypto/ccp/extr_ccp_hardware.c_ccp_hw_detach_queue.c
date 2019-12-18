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
struct ccp_softc {int valid_queues; struct ccp_queue* queues; } ;
struct ccp_queue {int /*<<< orphan*/  ring_desc_tag; int /*<<< orphan*/  ring_desc_map; int /*<<< orphan*/  desc_ring; int /*<<< orphan*/  completions_ring; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_CCP ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ccp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ccp_hw_detach_queue(device_t dev, unsigned queue)
{
	struct ccp_softc *sc;
	struct ccp_queue *qp;

	sc = device_get_softc(dev);
	qp = &sc->queues[queue];

	/*
	 * Don't bother allocating a ring for queues the host isn't allowed to
	 * drive.
	 */
	if ((sc->valid_queues & (1 << queue)) == 0)
		return;

	free(qp->completions_ring, M_CCP);
	bus_dmamap_unload(qp->ring_desc_tag, qp->ring_desc_map);
	bus_dmamem_free(qp->ring_desc_tag, qp->desc_ring, qp->ring_desc_map);
	bus_dma_tag_destroy(qp->ring_desc_tag);
}