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
typedef  int u_int8_t ;
struct cs4231_softc {int sc_flags; int /*<<< orphan*/  sc_dev; } ;
struct cs4231_channel {scalar_t__ locked; scalar_t__ dir; struct cs4231_softc* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  APC_CSR ; 
 int APC_CSR_CAPTURE_PAUSE ; 
 int APC_CSR_EI ; 
 int APC_CSR_EIE ; 
 int APC_CSR_GIE ; 
 int APC_CSR_PDMA_GO ; 
 int APC_CSR_PIE ; 
 int APC_CSR_PMIE ; 
 int APC_READ (struct cs4231_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APC_WRITE (struct cs4231_softc*,int /*<<< orphan*/ ,int) ; 
 int CAPTURE_ENABLE ; 
 int CAPTURE_OVERRUN ; 
 int /*<<< orphan*/  CS4231_LOCK (struct cs4231_softc*) ; 
 int CS4231_SBUS ; 
 int /*<<< orphan*/  CS4231_UNLOCK (struct cs4231_softc*) ; 
 int /*<<< orphan*/  CS_INTERFACE_CONFIG ; 
 int /*<<< orphan*/  CS_TEST_AND_INIT ; 
 int CS_TIMEOUT ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EBDCSR_DMAEN ; 
 int EBDMA_C_READ (struct cs4231_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EBDMA_C_WRITE (struct cs4231_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EBDMA_DCSR ; 
 int EBDMA_P_READ (struct cs4231_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EBDMA_P_WRITE (struct cs4231_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ PCMDIR_PLAY ; 
 int PLAYBACK_ENABLE ; 
 int PLAYBACK_UNDERRUN ; 
 int cs4231_read (struct cs4231_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4231_write (struct cs4231_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
cs4231_halt(struct cs4231_channel *ch)
{
	struct cs4231_softc *sc;
	u_int8_t status;
	int i;

	sc = ch->parent;
	CS4231_LOCK(sc);
	if (ch->locked == 0) {
		CS4231_UNLOCK(sc);
		return;
	}

	if (ch->dir == PCMDIR_PLAY ) {
		if ((sc->sc_flags & CS4231_SBUS) != 0) {
			/* XXX Kills some capture bits */
			APC_WRITE(sc, APC_CSR, APC_READ(sc, APC_CSR) &
			    ~(APC_CSR_EI | APC_CSR_GIE | APC_CSR_PIE |
			    APC_CSR_EIE | APC_CSR_PDMA_GO | APC_CSR_PMIE));
		} else {
			EBDMA_P_WRITE(sc, EBDMA_DCSR,
			    EBDMA_P_READ(sc, EBDMA_DCSR) & ~EBDCSR_DMAEN);
		}
		/* Waiting for playback FIFO to empty */
		status = cs4231_read(sc, CS_TEST_AND_INIT);
		for (i = CS_TIMEOUT;
		    i && (status & PLAYBACK_UNDERRUN) == 0; i--) {
			DELAY(5);
			status = cs4231_read(sc, CS_TEST_AND_INIT);
		}
		if (i == 0)
			device_printf(sc->sc_dev, "timeout waiting for "
			    "playback FIFO drain\n");
		cs4231_write(sc, CS_INTERFACE_CONFIG,
		    cs4231_read(sc, CS_INTERFACE_CONFIG) & (~PLAYBACK_ENABLE));
	} else {
		if ((sc->sc_flags & CS4231_SBUS) != 0) {
			/* XXX Kills some playback bits */
			APC_WRITE(sc, APC_CSR, APC_CSR_CAPTURE_PAUSE);
		} else {
			EBDMA_C_WRITE(sc, EBDMA_DCSR,
			    EBDMA_C_READ(sc, EBDMA_DCSR) & ~EBDCSR_DMAEN);
		}
		/* Waiting for capture FIFO to empty */
		status = cs4231_read(sc, CS_TEST_AND_INIT);
		for (i = CS_TIMEOUT;
		    i && (status & CAPTURE_OVERRUN) == 0; i--) {
			DELAY(5);
			status = cs4231_read(sc, CS_TEST_AND_INIT);
		}
		if (i == 0)
			device_printf(sc->sc_dev, "timeout waiting for "
			    "capture FIFO drain\n");
		cs4231_write(sc, CS_INTERFACE_CONFIG,
		    cs4231_read(sc, CS_INTERFACE_CONFIG) & (~CAPTURE_ENABLE));
	}
	ch->locked = 0;
	CS4231_UNLOCK(sc);
}