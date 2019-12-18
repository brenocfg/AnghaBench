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
struct stge_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int CSR_READ_4 (struct stge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct stge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int MC_MASK ; 
 int MC_TxDisable ; 
 int MC_TxEnabled ; 
 int /*<<< orphan*/  STGE_MACCtrl ; 
 int STGE_TIMEOUT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
stge_stop_tx(struct stge_softc *sc)
{
	uint32_t v;
	int i;

	v = CSR_READ_4(sc, STGE_MACCtrl) & MC_MASK;
	if ((v & MC_TxEnabled) == 0)
		return;
	v |= MC_TxDisable;
	CSR_WRITE_4(sc, STGE_MACCtrl, v);
	for (i = STGE_TIMEOUT; i > 0; i--) {
		DELAY(10);
		v = CSR_READ_4(sc, STGE_MACCtrl) & MC_MASK;
		if ((v & MC_TxEnabled) == 0)
			break;
	}
	if (i == 0)
		device_printf(sc->sc_dev, "Stopping Tx MAC timed out\n");
}