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
typedef  int uint32_t ;
struct ti_sdma_softc {int sc_active_channels; struct ti_sdma_channel* sc_channel; } ;
struct ti_sdma_channel {int reg_csdp; int reg_ccr; scalar_t__ need_reg_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA4_CCR (unsigned int) ; 
 int /*<<< orphan*/  DMA4_CDE (unsigned int) ; 
 int /*<<< orphan*/  DMA4_CDF (unsigned int) ; 
 int /*<<< orphan*/  DMA4_CDSA (unsigned int) ; 
 int /*<<< orphan*/  DMA4_CEN (unsigned int) ; 
 int /*<<< orphan*/  DMA4_CFN (unsigned int) ; 
 int /*<<< orphan*/  DMA4_CSDP (unsigned int) ; 
 int DMA4_CSDP_WRITE_MODE (int) ; 
 int /*<<< orphan*/  DMA4_CSE (unsigned int) ; 
 int /*<<< orphan*/  DMA4_CSF (unsigned int) ; 
 int /*<<< orphan*/  DMA4_CSR (unsigned int) ; 
 int /*<<< orphan*/  DMA4_CSSA (unsigned int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TI_SDMA_LOCK (struct ti_sdma_softc*) ; 
 int /*<<< orphan*/  TI_SDMA_UNLOCK (struct ti_sdma_softc*) ; 
 int ti_sdma_read_4 (struct ti_sdma_softc*,int /*<<< orphan*/ ) ; 
 struct ti_sdma_softc* ti_sdma_sc ; 
 int /*<<< orphan*/  ti_sdma_write_4 (struct ti_sdma_softc*,int /*<<< orphan*/ ,int) ; 

int
ti_sdma_start_xfer(unsigned int ch, unsigned int src_paddr,
                    unsigned long dst_paddr,
                    unsigned int frmcnt, unsigned int elmcnt)
{
	struct ti_sdma_softc *sc = ti_sdma_sc;
	struct ti_sdma_channel *channel;
	uint32_t ccr;

	/* Sanity check */
	if (sc == NULL)
		return (ENOMEM);

	TI_SDMA_LOCK(sc);

	if ((sc->sc_active_channels & (1 << ch)) == 0) {
		TI_SDMA_UNLOCK(sc);
		return (EINVAL);
	}

	channel = &sc->sc_channel[ch];

	/* a) Write the CSDP register */
	ti_sdma_write_4(sc, DMA4_CSDP(ch),
	    channel->reg_csdp | DMA4_CSDP_WRITE_MODE(1));

	/* b) Set the number of element per frame CEN[23:0] */
	ti_sdma_write_4(sc, DMA4_CEN(ch), elmcnt);

	/* c) Set the number of frame per block CFN[15:0] */
	ti_sdma_write_4(sc, DMA4_CFN(ch), frmcnt);

	/* d) Set the Source/dest start address index CSSA[31:0]/CDSA[31:0] */
	ti_sdma_write_4(sc, DMA4_CSSA(ch), src_paddr);
	ti_sdma_write_4(sc, DMA4_CDSA(ch), dst_paddr);

	/* e) Write the CCR register */
	ti_sdma_write_4(sc, DMA4_CCR(ch), channel->reg_ccr);

	/* f)  - Set the source element index increment CSEI[15:0] */
	ti_sdma_write_4(sc, DMA4_CSE(ch), 0x0001);

	/*     - Set the source frame index increment CSFI[15:0] */
	ti_sdma_write_4(sc, DMA4_CSF(ch), 0x0001);

	/*     - Set the destination element index increment CDEI[15:0]*/
	ti_sdma_write_4(sc, DMA4_CDE(ch), 0x0001);

	/* - Set the destination frame index increment CDFI[31:0] */
	ti_sdma_write_4(sc, DMA4_CDF(ch), 0x0001);

	/* Clear the status register */
	ti_sdma_write_4(sc, DMA4_CSR(ch), 0x1FFE);

	/* Write the start-bit and away we go */
	ccr = ti_sdma_read_4(sc, DMA4_CCR(ch));
	ccr |= (1 << 7);
	ti_sdma_write_4(sc, DMA4_CCR(ch), ccr);

	/* Clear the reg write flag */
	channel->need_reg_write = 0;

	TI_SDMA_UNLOCK(sc);

	return (0);
}