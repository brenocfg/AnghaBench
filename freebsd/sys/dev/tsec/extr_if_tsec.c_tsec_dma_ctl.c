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
struct tsec_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 int DMACTRL_WOP ; 
 int DMACTRL_WWR ; 
 int TSEC_DMACTRL_GRS ; 
 int TSEC_DMACTRL_GTS ; 
 int TSEC_DMACTRL_TBDSEN ; 
 int TSEC_DMACTRL_TDSEN ; 
 int TSEC_IEVENT_GRSC ; 
 int TSEC_IEVENT_GTSC ; 
 int TSEC_READ (struct tsec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSEC_READ_DELAY ; 
 int TSEC_READ_RETRY ; 
 int /*<<< orphan*/  TSEC_REG_DMACTRL ; 
 int /*<<< orphan*/  TSEC_REG_IEVENT ; 
 int /*<<< orphan*/  TSEC_REG_TSTAT ; 
 int TSEC_TSTAT_THLT ; 
 int /*<<< orphan*/  TSEC_WRITE (struct tsec_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
tsec_dma_ctl(struct tsec_softc *sc, int state)
{
	device_t dev;
	uint32_t dma_flags, timeout;

	dev = sc->dev;

	dma_flags = TSEC_READ(sc, TSEC_REG_DMACTRL);

	switch (state) {
	case 0:
		/* Temporarily clear stop graceful stop bits. */
		tsec_dma_ctl(sc, 1000);

		/* Set it again */
		dma_flags |= (TSEC_DMACTRL_GRS | TSEC_DMACTRL_GTS);
		break;
	case 1000:
	case 1:
		/* Set write with response (WWR), wait (WOP) and snoop bits */
		dma_flags |= (TSEC_DMACTRL_TDSEN | TSEC_DMACTRL_TBDSEN |
		    DMACTRL_WWR | DMACTRL_WOP);

		/* Clear graceful stop bits */
		dma_flags &= ~(TSEC_DMACTRL_GRS | TSEC_DMACTRL_GTS);
		break;
	default:
		device_printf(dev, "tsec_dma_ctl(): unknown state value: %d\n",
		    state);
	}

	TSEC_WRITE(sc, TSEC_REG_DMACTRL, dma_flags);

	switch (state) {
	case 0:
		/* Wait for DMA stop */
		timeout = TSEC_READ_RETRY;
		while (--timeout && (!(TSEC_READ(sc, TSEC_REG_IEVENT) &
		    (TSEC_IEVENT_GRSC | TSEC_IEVENT_GTSC))))
			DELAY(TSEC_READ_DELAY);

		if (timeout == 0)
			device_printf(dev, "tsec_dma_ctl(): timeout!\n");
		break;
	case 1:
		/* Restart transmission function */
		TSEC_WRITE(sc, TSEC_REG_TSTAT, TSEC_TSTAT_THLT);
	}
}