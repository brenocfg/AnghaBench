#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct mmc_command {TYPE_2__* data; } ;
struct jz4780_mmc_softc {int sc_dma_map_err; int sc_dma_inuse; int sc_dma_ctl; int /*<<< orphan*/  sc_dma_map; int /*<<< orphan*/  sc_dma_tag; int /*<<< orphan*/  sc_dma_buf_map; int /*<<< orphan*/  sc_dma_buf_tag; TYPE_1__* sc_req; } ;
typedef  int /*<<< orphan*/  bus_dmasync_op_t ;
struct TYPE_4__ {int len; int flags; scalar_t__ data; } ;
struct TYPE_3__ {struct mmc_command* cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int EFBIG ; 
 int JZ_ALIGNEN ; 
 int JZ_AOFST_S ; 
 int JZ_DMAEN ; 
 int JZ_INCR_64 ; 
 int JZ_MODE_SEL ; 
 int JZ_MSC_DMA_MAX_SIZE ; 
 int JZ_MSC_DMA_SEGS ; 
 int MMC_DATA_WRITE ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,struct jz4780_mmc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4780_mmc_dma_cb ; 

__attribute__((used)) static int
jz4780_mmc_prepare_dma(struct jz4780_mmc_softc *sc)
{
	bus_dmasync_op_t sync_op;
	int error;
	struct mmc_command *cmd;
	uint32_t off;

	cmd = sc->sc_req->cmd;
	if (cmd->data->len > JZ_MSC_DMA_MAX_SIZE * JZ_MSC_DMA_SEGS)
		return (EFBIG);
	error = bus_dmamap_load(sc->sc_dma_buf_tag, sc->sc_dma_buf_map,
	    cmd->data->data, cmd->data->len, jz4780_mmc_dma_cb, sc,
	    BUS_DMA_NOWAIT);
	if (error)
		return (error);
	if (sc->sc_dma_map_err)
		return (sc->sc_dma_map_err);

	sc->sc_dma_inuse = 1;
	if (cmd->data->flags & MMC_DATA_WRITE)
		sync_op = BUS_DMASYNC_PREWRITE;
	else
		sync_op = BUS_DMASYNC_PREREAD;
	bus_dmamap_sync(sc->sc_dma_buf_tag, sc->sc_dma_buf_map, sync_op);
	bus_dmamap_sync(sc->sc_dma_tag, sc->sc_dma_map, BUS_DMASYNC_PREWRITE);

	/* Configure default DMA parameters */
	sc->sc_dma_ctl = JZ_MODE_SEL | JZ_INCR_64 | JZ_DMAEN;

	/* Enable unaligned buffer handling */
	off = (uintptr_t)cmd->data->data & 3;
	if (off != 0)
		sc->sc_dma_ctl |= (off << JZ_AOFST_S) | JZ_ALIGNEN;
	return (0);
}