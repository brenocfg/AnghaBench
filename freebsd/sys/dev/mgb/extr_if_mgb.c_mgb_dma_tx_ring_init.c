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
struct mgb_ring_data {scalar_t__ ring_bus_addr; scalar_t__ head_wb_bus_addr; int last_tail; void* last_head; } ;
struct mgb_softc {int /*<<< orphan*/  dev; struct mgb_ring_data tx_ring_data; } ;

/* Variables and functions */
 void* CSR_READ_REG (struct mgb_softc*,int /*<<< orphan*/ ) ; 
 int CSR_TRANSLATE_ADDR_HIGH32 (scalar_t__) ; 
 int CSR_TRANSLATE_ADDR_LOW32 (scalar_t__) ; 
 int /*<<< orphan*/  CSR_WRITE_REG (struct mgb_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DMAC_RESET ; 
 int /*<<< orphan*/  DMAC_START ; 
 int /*<<< orphan*/  FCT_ENABLE ; 
 int /*<<< orphan*/  FCT_RESET ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MGB_DMAC_STATE_IS_INITIAL (struct mgb_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MGB_DMAC_TX_START ; 
 int MGB_DMA_HEAD_WB_ENBL ; 
 int MGB_DMA_HEAD_WB_LS_ENBL ; 
 int MGB_DMA_RING_LEN_MASK ; 
 int MGB_DMA_RING_SIZE ; 
 int /*<<< orphan*/  MGB_DMA_TX_BASE_H (int) ; 
 int /*<<< orphan*/  MGB_DMA_TX_BASE_L (int) ; 
 int /*<<< orphan*/  MGB_DMA_TX_CONFIG0 (int) ; 
 int /*<<< orphan*/  MGB_DMA_TX_CONFIG1 (int) ; 
 int /*<<< orphan*/  MGB_DMA_TX_HEAD (int) ; 
 int /*<<< orphan*/  MGB_DMA_TX_HEAD_WB_H (int) ; 
 int /*<<< orphan*/  MGB_DMA_TX_HEAD_WB_L (int) ; 
 int /*<<< orphan*/  MGB_DMA_TX_TAIL (int) ; 
 int /*<<< orphan*/  MGB_FCT_TX_CTL ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int mgb_dmac_control (struct mgb_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mgb_fct_control (struct mgb_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mgb_dma_tx_ring_init(struct mgb_softc *sc, int channel)
{
	struct mgb_ring_data *rdata;
	int ring_config, error = 0;

	rdata = &sc->tx_ring_data;
	if ((error = mgb_fct_control(sc, MGB_FCT_TX_CTL, channel, FCT_RESET))) {
		device_printf(sc->dev, "Failed to reset TX FCT.\n");
		goto fail;
	}
	if ((error = mgb_fct_control(sc, MGB_FCT_TX_CTL, channel,
	    FCT_ENABLE))) {
		device_printf(sc->dev, "Failed to enable TX FCT.\n");
		goto fail;
	}
	if ((error = mgb_dmac_control(sc, MGB_DMAC_TX_START, channel,
	    DMAC_RESET))) {
		device_printf(sc->dev, "Failed to reset TX DMAC.\n");
		goto fail;
	}
	KASSERT(MGB_DMAC_STATE_IS_INITIAL(sc, MGB_DMAC_TX_START, channel),
	    ("Trying to init channels in not init state\n"));

	/* write ring address */
	if (rdata->ring_bus_addr == 0) {
		device_printf(sc->dev, "Invalid ring bus addr.\n");
		goto fail;
	}
	CSR_WRITE_REG(sc, MGB_DMA_TX_BASE_H(channel),
	    CSR_TRANSLATE_ADDR_HIGH32(rdata->ring_bus_addr));
	CSR_WRITE_REG(sc, MGB_DMA_TX_BASE_L(channel),
	    CSR_TRANSLATE_ADDR_LOW32(rdata->ring_bus_addr));

	/* write ring size */
	ring_config = CSR_READ_REG(sc, MGB_DMA_TX_CONFIG1(channel));
	ring_config &= ~MGB_DMA_RING_LEN_MASK;
	ring_config |= (MGB_DMA_RING_SIZE & MGB_DMA_RING_LEN_MASK);
	CSR_WRITE_REG(sc, MGB_DMA_TX_CONFIG1(channel), ring_config);

	/* Enable interrupt on completion and head pointer writeback */
	ring_config = (MGB_DMA_HEAD_WB_LS_ENBL | MGB_DMA_HEAD_WB_ENBL);
	CSR_WRITE_REG(sc, MGB_DMA_TX_CONFIG0(channel), ring_config);

	/* write head pointer writeback address */
	if (rdata->head_wb_bus_addr == 0) {
		device_printf(sc->dev, "Invalid head wb bus addr.\n");
		goto fail;
	}
	CSR_WRITE_REG(sc, MGB_DMA_TX_HEAD_WB_H(channel),
	    CSR_TRANSLATE_ADDR_HIGH32(rdata->head_wb_bus_addr));
	CSR_WRITE_REG(sc, MGB_DMA_TX_HEAD_WB_L(channel),
	    CSR_TRANSLATE_ADDR_LOW32(rdata->head_wb_bus_addr));

	rdata->last_head = CSR_READ_REG(sc, MGB_DMA_TX_HEAD(channel));
	KASSERT(rdata->last_head == 0, ("MGB_DMA_TX_HEAD was not reset.\n"));
	rdata->last_tail = 0;
	CSR_WRITE_REG(sc, MGB_DMA_TX_TAIL(channel), rdata->last_tail);

	if ((error = mgb_dmac_control(sc, MGB_DMAC_TX_START, channel,
	    DMAC_START)))
		device_printf(sc->dev, "Failed to start TX DMAC.\n");
fail:
	return error;
}