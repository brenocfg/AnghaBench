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
struct cs4231_softc {int sc_burst; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int CS_TIMEOUT ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EBDCSR_DRAIN ; 
 int EBDCSR_INTEN ; 
 int EBDCSR_NEXTEN ; 
 int EBDCSR_RESET ; 
 int EBDMA_C_READ (struct cs4231_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EBDMA_C_WRITE (struct cs4231_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EBDMA_DCSR ; 
 int EBDMA_P_READ (struct cs4231_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EBDMA_P_WRITE (struct cs4231_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
cs4231_ebdma_reset(struct cs4231_softc *sc)
{
	int i;

	/* playback */
	EBDMA_P_WRITE(sc, EBDMA_DCSR,
	    EBDMA_P_READ(sc, EBDMA_DCSR) & ~(EBDCSR_INTEN | EBDCSR_NEXTEN));
	EBDMA_P_WRITE(sc, EBDMA_DCSR, EBDCSR_RESET);
	for (i = CS_TIMEOUT;
	    i && EBDMA_P_READ(sc, EBDMA_DCSR) & EBDCSR_DRAIN; i--)
		DELAY(1);
	if (i == 0)
		device_printf(sc->sc_dev,
		    "timeout waiting for playback DMA reset\n");
	EBDMA_P_WRITE(sc, EBDMA_DCSR, sc->sc_burst);
	/* capture */
	EBDMA_C_WRITE(sc, EBDMA_DCSR,
	    EBDMA_C_READ(sc, EBDMA_DCSR) & ~(EBDCSR_INTEN | EBDCSR_NEXTEN));
	EBDMA_C_WRITE(sc, EBDMA_DCSR, EBDCSR_RESET);
	for (i = CS_TIMEOUT;
	    i && EBDMA_C_READ(sc, EBDMA_DCSR) & EBDCSR_DRAIN; i--)
		DELAY(1);
	if (i == 0)
		device_printf(sc->sc_dev,
		    "timeout waiting for capture DMA reset\n");
	EBDMA_C_WRITE(sc, EBDMA_DCSR, sc->sc_burst);
}