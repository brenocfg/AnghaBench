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
typedef  scalar_t__ uint32_t ;
struct ti_sdma_softc {int sc_active_channels; struct ti_sdma_channel* sc_channel; } ;
struct ti_sdma_channel {void (* callback ) (unsigned int,uint32_t,void*) ;int need_reg_write; int reg_csdp; int reg_ccr; int reg_cicr; void* callback_data; } ;

/* Variables and functions */
 scalar_t__ DMA4_CCR (unsigned int) ; 
 int DMA4_CCR_BLOCK_SYNC (int /*<<< orphan*/ ) ; 
 int DMA4_CCR_DST_ADDRESS_MODE (int) ; 
 int DMA4_CCR_FRAME_SYNC (int /*<<< orphan*/ ) ; 
 int DMA4_CCR_READ_PRIORITY (int /*<<< orphan*/ ) ; 
 int DMA4_CCR_SRC_ADDRESS_MODE (int) ; 
 int DMA4_CCR_SYNC_TRIGGER (int /*<<< orphan*/ ) ; 
 int DMA4_CCR_WRITE_PRIORITY (int /*<<< orphan*/ ) ; 
 int DMA4_CICR_MISALIGNED_ADRS_ERR_IE ; 
 int DMA4_CICR_SECURE_ERR_IE ; 
 int DMA4_CICR_SUPERVISOR_ERR_IE ; 
 int DMA4_CICR_TRANS_ERR_IE ; 
 scalar_t__ DMA4_COLOR (unsigned int) ; 
 int DMA4_CSDP_DATA_TYPE (int) ; 
 int DMA4_CSDP_DST_BURST_MODE (int /*<<< orphan*/ ) ; 
 int DMA4_CSDP_DST_ENDIANISM (int /*<<< orphan*/ ) ; 
 int DMA4_CSDP_DST_PACKED (int /*<<< orphan*/ ) ; 
 int DMA4_CSDP_SRC_BURST_MODE (int /*<<< orphan*/ ) ; 
 int DMA4_CSDP_SRC_ENDIANISM (int /*<<< orphan*/ ) ; 
 int DMA4_CSDP_SRC_PACKED (int /*<<< orphan*/ ) ; 
 int DMA4_CSDP_WRITE_MODE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 unsigned int NUM_DMA_CHANNELS ; 
 int /*<<< orphan*/  TI_SDMA_LOCK (struct ti_sdma_softc*) ; 
 int /*<<< orphan*/  TI_SDMA_UNLOCK (struct ti_sdma_softc*) ; 
 struct ti_sdma_softc* ti_sdma_sc ; 
 int /*<<< orphan*/  ti_sdma_write_4 (struct ti_sdma_softc*,scalar_t__,int) ; 

int
ti_sdma_activate_channel(unsigned int *ch,
                          void (*callback)(unsigned int ch, uint32_t status, void *data),
                          void *data)
{
	struct ti_sdma_softc *sc = ti_sdma_sc;
	struct ti_sdma_channel *channel = NULL;
	uint32_t addr;
	unsigned int i;

	/* Sanity check */
	if (sc == NULL)
		return (ENOMEM);

	if (ch == NULL)
		return (EINVAL);

	TI_SDMA_LOCK(sc);

	/* Check to see if all channels are in use */
	if (sc->sc_active_channels == 0xffffffff) {
		TI_SDMA_UNLOCK(sc);
		return (ENOMEM);
	}

	/* Find the first non-active channel */
	for (i = 0; i < NUM_DMA_CHANNELS; i++) {
		if (!(sc->sc_active_channels & (0x1 << i))) {
			sc->sc_active_channels |= (0x1 << i);
			*ch = i;
			break;
		}
	}

	/* Get the channel struct and populate the fields */
	channel = &sc->sc_channel[*ch];

	channel->callback = callback;
	channel->callback_data = data;

	channel->need_reg_write = 1;

	/* Set the default configuration for the DMA channel */
	channel->reg_csdp = DMA4_CSDP_DATA_TYPE(0x2)
		| DMA4_CSDP_SRC_BURST_MODE(0)
		| DMA4_CSDP_DST_BURST_MODE(0)
		| DMA4_CSDP_SRC_ENDIANISM(0)
		| DMA4_CSDP_DST_ENDIANISM(0)
		| DMA4_CSDP_WRITE_MODE(0)
		| DMA4_CSDP_SRC_PACKED(0)
		| DMA4_CSDP_DST_PACKED(0);

	channel->reg_ccr = DMA4_CCR_DST_ADDRESS_MODE(1)
		| DMA4_CCR_SRC_ADDRESS_MODE(1)
		| DMA4_CCR_READ_PRIORITY(0)
		| DMA4_CCR_WRITE_PRIORITY(0)
		| DMA4_CCR_SYNC_TRIGGER(0)
		| DMA4_CCR_FRAME_SYNC(0)
		| DMA4_CCR_BLOCK_SYNC(0);

	channel->reg_cicr = DMA4_CICR_TRANS_ERR_IE
		| DMA4_CICR_SECURE_ERR_IE
		| DMA4_CICR_SUPERVISOR_ERR_IE
		| DMA4_CICR_MISALIGNED_ADRS_ERR_IE;

	/* Clear all the channel registers, this should abort any transaction */
	for (addr = DMA4_CCR(*ch); addr <= DMA4_COLOR(*ch); addr += 4)
		ti_sdma_write_4(sc, addr, 0x00000000);

	TI_SDMA_UNLOCK(sc);

	return 0;
}