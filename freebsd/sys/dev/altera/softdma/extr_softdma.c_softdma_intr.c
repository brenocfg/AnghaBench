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
struct softdma_softc {struct softdma_channel* channels; } ;
struct softdma_channel {int run; } ;

/* Variables and functions */
 int A_ONCHIP_FIFO_MEM_CORE_ERROR_MASK ; 
 int A_ONCHIP_FIFO_MEM_CORE_ERROR_SHIFT ; 
 int A_ONCHIP_FIFO_MEM_CORE_EVENT_OVERFLOW ; 
 int A_ONCHIP_FIFO_MEM_CORE_EVENT_UNDERFLOW ; 
 int /*<<< orphan*/  A_ONCHIP_FIFO_MEM_CORE_STATUS_REG_EVENT ; 
 int softdma_memc_read (struct softdma_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  softdma_memc_write (struct softdma_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wakeup (struct softdma_channel*) ; 

__attribute__((used)) static void
softdma_intr(void *arg)
{
	struct softdma_channel *chan;
	struct softdma_softc *sc;
	int reg;
	int err;

	sc = arg;

	chan = &sc->channels[0];

	reg = softdma_memc_read(sc, A_ONCHIP_FIFO_MEM_CORE_STATUS_REG_EVENT);

	if (reg & (A_ONCHIP_FIFO_MEM_CORE_EVENT_OVERFLOW | 
	    A_ONCHIP_FIFO_MEM_CORE_EVENT_UNDERFLOW)) {
		/* Errors */
		err = (((reg & A_ONCHIP_FIFO_MEM_CORE_ERROR_MASK) >> \
		    A_ONCHIP_FIFO_MEM_CORE_ERROR_SHIFT) & 0xff);
	}

	if (reg != 0) {
		softdma_memc_write(sc,
		    A_ONCHIP_FIFO_MEM_CORE_STATUS_REG_EVENT, reg);
		chan->run = 1;
		wakeup(chan);
	}
}