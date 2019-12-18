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
struct ffec_softc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FEC_IER_EBERR ; 
 int /*<<< orphan*/  FEC_IER_REG ; 
 int FEC_IER_RXF ; 
 int FEC_IER_TXF ; 
 int /*<<< orphan*/  FFEC_LOCK (struct ffec_softc*) ; 
 int /*<<< orphan*/  FFEC_UNLOCK (struct ffec_softc*) ; 
 int RD4 (struct ffec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (struct ffec_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ffec_init_locked (struct ffec_softc*) ; 
 int /*<<< orphan*/  ffec_rxfinish_locked (struct ffec_softc*) ; 
 int /*<<< orphan*/  ffec_stop_locked (struct ffec_softc*) ; 
 int /*<<< orphan*/  ffec_txfinish_locked (struct ffec_softc*) ; 

__attribute__((used)) static void
ffec_intr(void *arg)
{
	struct ffec_softc *sc;
	uint32_t ier;

	sc = arg;

	FFEC_LOCK(sc);

	ier = RD4(sc, FEC_IER_REG);

	if (ier & FEC_IER_TXF) {
		WR4(sc, FEC_IER_REG, FEC_IER_TXF);
		ffec_txfinish_locked(sc);
	}

	if (ier & FEC_IER_RXF) {
		WR4(sc, FEC_IER_REG, FEC_IER_RXF);
		ffec_rxfinish_locked(sc);
	}

	/*
	 * We actually don't care about most errors, because the hardware copes
	 * with them just fine, discarding the incoming bad frame, or forcing a
	 * bad CRC onto an outgoing bad frame, and counting the errors in the
	 * stats registers.  The one that really matters is EBERR (DMA bus
	 * error) because the hardware automatically clears ECR[ETHEREN] and we
	 * have to restart it here.  It should never happen.
	 */
	if (ier & FEC_IER_EBERR) {
		WR4(sc, FEC_IER_REG, FEC_IER_EBERR);
		device_printf(sc->dev, 
		    "Ethernet DMA error, restarting controller.\n");
		ffec_stop_locked(sc);
		ffec_init_locked(sc);
	}

	FFEC_UNLOCK(sc);

}