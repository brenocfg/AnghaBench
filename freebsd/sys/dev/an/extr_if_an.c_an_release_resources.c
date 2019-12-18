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
struct TYPE_2__ {scalar_t__ an_dma_paddr; } ;
struct an_softc {scalar_t__ an_dtag; TYPE_1__* an_tx_buffer; TYPE_1__* an_rx_buffer; TYPE_1__ an_rid_buffer; scalar_t__ irq_res; int /*<<< orphan*/  irq_rid; scalar_t__ mem_aux_res; int /*<<< orphan*/  mem_aux_rid; scalar_t__ mem_res; int /*<<< orphan*/  mem_rid; scalar_t__ port_res; int /*<<< orphan*/  port_rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AN_MAX_RX_DESC ; 
 int AN_MAX_TX_DESC ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  an_dma_free (struct an_softc*,TYPE_1__*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct an_softc* device_get_softc (int /*<<< orphan*/ ) ; 

void
an_release_resources(device_t dev)
{
	struct an_softc *sc = device_get_softc(dev);
	int i;

	if (sc->port_res) {
		bus_release_resource(dev, SYS_RES_IOPORT,
				     sc->port_rid, sc->port_res);
		sc->port_res = 0;
	}
	if (sc->mem_res) {
		bus_release_resource(dev, SYS_RES_MEMORY,
				     sc->mem_rid, sc->mem_res);
		sc->mem_res = 0;
	}
	if (sc->mem_aux_res) {
		bus_release_resource(dev, SYS_RES_MEMORY,
				     sc->mem_aux_rid, sc->mem_aux_res);
		sc->mem_aux_res = 0;
	}
	if (sc->irq_res) {
		bus_release_resource(dev, SYS_RES_IRQ,
				     sc->irq_rid, sc->irq_res);
		sc->irq_res = 0;
	}
	if (sc->an_rid_buffer.an_dma_paddr) {
		an_dma_free(sc, &sc->an_rid_buffer);
	}
	for (i = 0; i < AN_MAX_RX_DESC; i++)
		if (sc->an_rx_buffer[i].an_dma_paddr) {
			an_dma_free(sc, &sc->an_rx_buffer[i]);
		}
	for (i = 0; i < AN_MAX_TX_DESC; i++)
		if (sc->an_tx_buffer[i].an_dma_paddr) {
			an_dma_free(sc, &sc->an_tx_buffer[i]);
		}
	if (sc->an_dtag) {
		bus_dma_tag_destroy(sc->an_dtag);
	}

}