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
struct stge_softc {scalar_t__ sc_nerr; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int CSR_READ_4 (struct stge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct stge_softc*,int /*<<< orphan*/ ,int) ; 
 int MC_MASK ; 
 int MC_TxEnable ; 
 int /*<<< orphan*/  STGE_MACCtrl ; 
 scalar_t__ STGE_MAXERR ; 
 int /*<<< orphan*/  STGE_TxStatus ; 
 int TS_LateCollision ; 
 int TS_MaxCollisions ; 
 int TS_TxComplete ; 
 int TS_TxUnderrun ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static __inline int
stge_tx_error(struct stge_softc *sc)
{
	uint32_t txstat;
	int error;

	for (error = 0;;) {
		txstat = CSR_READ_4(sc, STGE_TxStatus);
		if ((txstat & TS_TxComplete) == 0)
			break;
		/* Tx underrun */
		if ((txstat & TS_TxUnderrun) != 0) {
			/*
			 * XXX
			 * There should be a more better way to recover
			 * from Tx underrun instead of a full reset.
			 */
			if (sc->sc_nerr++ < STGE_MAXERR)
				device_printf(sc->sc_dev, "Tx underrun, "
				    "resetting...\n");
			if (sc->sc_nerr == STGE_MAXERR)
				device_printf(sc->sc_dev, "too many errors; "
				    "not reporting any more\n");
			error = -1;
			break;
		}
		/* Maximum/Late collisions, Re-enable Tx MAC. */
		if ((txstat & (TS_MaxCollisions|TS_LateCollision)) != 0)
			CSR_WRITE_4(sc, STGE_MACCtrl,
			    (CSR_READ_4(sc, STGE_MACCtrl) & MC_MASK) |
			    MC_TxEnable);
	}

	return (error);
}