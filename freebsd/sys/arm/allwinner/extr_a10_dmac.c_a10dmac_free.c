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
typedef  int /*<<< orphan*/  uint32_t ;
struct a10dmac_softc {int /*<<< orphan*/  sc_mtx; } ;
struct a10dmac_channel {scalar_t__ ch_type; int /*<<< orphan*/ * ch_callbackarg; int /*<<< orphan*/ * ch_callback; int /*<<< orphan*/  ch_index; struct a10dmac_softc* ch_sc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AWIN_DDMA_CTL_DMA_LOADING ; 
 int /*<<< orphan*/  AWIN_DMA_IRQ_DDMA_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AWIN_DMA_IRQ_EN_REG ; 
 int /*<<< orphan*/  AWIN_DMA_IRQ_NDMA_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AWIN_DMA_IRQ_PEND_STA_REG ; 
 int /*<<< orphan*/  AWIN_NDMA_CTL_DMA_LOADING ; 
 scalar_t__ CH_NDMA ; 
 int /*<<< orphan*/  DMA_READ (struct a10dmac_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_WRITE (struct a10dmac_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a10dmac_read_ctl (struct a10dmac_channel*) ; 
 int /*<<< orphan*/  a10dmac_write_ctl (struct a10dmac_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
a10dmac_free(device_t dev, void *priv)
{
	struct a10dmac_channel *ch = priv;
	struct a10dmac_softc *sc = ch->ch_sc;
	uint32_t irqen, sta, cfg;

	mtx_lock_spin(&sc->sc_mtx);

	irqen = DMA_READ(sc, AWIN_DMA_IRQ_EN_REG);
	cfg = a10dmac_read_ctl(ch);
	if (ch->ch_type == CH_NDMA) {
		sta = AWIN_DMA_IRQ_NDMA_END(ch->ch_index);
		cfg &= ~AWIN_NDMA_CTL_DMA_LOADING;
	} else {
		sta = AWIN_DMA_IRQ_DDMA_END(ch->ch_index);
		cfg &= ~AWIN_DDMA_CTL_DMA_LOADING;
	}
	irqen &= ~sta;
	a10dmac_write_ctl(ch, cfg);
	DMA_WRITE(sc, AWIN_DMA_IRQ_EN_REG, irqen);
	DMA_WRITE(sc, AWIN_DMA_IRQ_PEND_STA_REG, sta);

	ch->ch_callback = NULL;
	ch->ch_callbackarg = NULL;

	mtx_unlock_spin(&sc->sc_mtx);
}