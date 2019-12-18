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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct a10dmac_softc {TYPE_2__* sc_ddma_channels; TYPE_1__* sc_ndma_channels; } ;
struct TYPE_4__ {int /*<<< orphan*/  ch_callbackarg; int /*<<< orphan*/  (* ch_callback ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  ch_callbackarg; int /*<<< orphan*/  (* ch_callback ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int AWIN_DMA_IRQ_END_MASK ; 
 int AWIN_DMA_IRQ_NDMA ; 
 int /*<<< orphan*/  AWIN_DMA_IRQ_PEND_STA_REG ; 
 int DMA_READ (struct a10dmac_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_WRITE (struct a10dmac_softc*,int /*<<< orphan*/ ,int) ; 
 int ffs (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
a10dmac_intr(void *priv)
{
	struct a10dmac_softc *sc = priv;
	uint32_t sta, bit, mask;
	uint8_t index;

	sta = DMA_READ(sc, AWIN_DMA_IRQ_PEND_STA_REG);
	DMA_WRITE(sc, AWIN_DMA_IRQ_PEND_STA_REG, sta);

	while ((bit = ffs(sta & AWIN_DMA_IRQ_END_MASK)) != 0) {
		mask = (1U << (bit - 1));
		sta &= ~mask;
		/*
		 * Map status bit to channel number. The status register is
		 * encoded with two bits of status per channel (lowest bit
		 * is half transfer pending, highest bit is end transfer
		 * pending). The 8 normal DMA channel status are in the lower
		 * 16 bits and the 8 dedicated DMA channel status are in
		 * the upper 16 bits. The output is a channel number from 0-7.
		 */
		index = ((bit - 1) / 2) & 7;
		if (mask & AWIN_DMA_IRQ_NDMA) {
			if (sc->sc_ndma_channels[index].ch_callback == NULL)
				continue;
			sc->sc_ndma_channels[index].ch_callback(
			    sc->sc_ndma_channels[index].ch_callbackarg);
		} else {
			if (sc->sc_ddma_channels[index].ch_callback == NULL)
				continue;
			sc->sc_ddma_channels[index].ch_callback(
			    sc->sc_ddma_channels[index].ch_callbackarg);
		}
	}
}