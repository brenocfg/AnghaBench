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
typedef  int uint32_t ;
struct bcm_dma_softc {TYPE_1__* sc_dma_ch; int /*<<< orphan*/  sc_mem; } ;
struct bcm_dma_cb {int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {struct bcm_dma_cb* cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_DMA_CBADDR (int) ; 
 int /*<<< orphan*/  BCM_DMA_CBNEXT (int) ; 
 int BCM_DMA_CH_MAX ; 
 int /*<<< orphan*/  BCM_DMA_CS (int) ; 
 int CS_ABORT ; 
 int CS_ACTIVE ; 
 int CS_END ; 
 int CS_INT ; 
 int CS_ISPAUSED ; 
 int /*<<< orphan*/  INFO_WAIT_RESP ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (struct bcm_dma_cb*,int) ; 
 struct bcm_dma_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
bcm_dma_reset(device_t dev, int ch)
{
	struct bcm_dma_softc *sc = device_get_softc(dev);
	struct bcm_dma_cb *cb;
	uint32_t cs;
	int count;

	if (ch < 0 || ch >= BCM_DMA_CH_MAX)
		return;

	cs = bus_read_4(sc->sc_mem, BCM_DMA_CS(ch));

	if (cs & CS_ACTIVE) {
		/* pause current task */
		bus_write_4(sc->sc_mem, BCM_DMA_CS(ch), 0);

		count = 1000;
		do {
			cs = bus_read_4(sc->sc_mem, BCM_DMA_CS(ch));
		} while (!(cs & CS_ISPAUSED) && (count-- > 0));

		if (!(cs & CS_ISPAUSED)) {
			device_printf(dev,
			    "Can't abort DMA transfer at channel %d\n", ch);
		}

		bus_write_4(sc->sc_mem, BCM_DMA_CBNEXT(ch), 0);

		/* Complete everything, clear interrupt */
		bus_write_4(sc->sc_mem, BCM_DMA_CS(ch),
		    CS_ABORT | CS_INT | CS_END| CS_ACTIVE);
	}

	/* clear control blocks */
	bus_write_4(sc->sc_mem, BCM_DMA_CBADDR(ch), 0);
	bus_write_4(sc->sc_mem, BCM_DMA_CBNEXT(ch), 0);

	/* Reset control block */
	cb = sc->sc_dma_ch[ch].cb;
	bzero(cb, sizeof(*cb));
	cb->info = INFO_WAIT_RESP;
}