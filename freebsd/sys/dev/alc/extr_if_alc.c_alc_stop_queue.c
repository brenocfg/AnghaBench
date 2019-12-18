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
struct alc_softc {int alc_flags; int /*<<< orphan*/  alc_dev; } ;

/* Variables and functions */
 int ALC_FLAG_AR816X_FAMILY ; 
 int /*<<< orphan*/  ALC_IDLE_STATUS ; 
 int /*<<< orphan*/  ALC_RXQ_CFG ; 
 int ALC_TIMEOUT ; 
 int /*<<< orphan*/  ALC_TXQ_CFG ; 
 int CSR_READ_4 (struct alc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct alc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int IDLE_STATUS_RXQ ; 
 int IDLE_STATUS_TXQ ; 
 int RXQ_CFG_ENB ; 
 int RXQ_CFG_QUEUE0_ENB ; 
 int TXQ_CFG_ENB ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
alc_stop_queue(struct alc_softc *sc)
{
	uint32_t reg;
	int i;

	/* Disable RxQ. */
	reg = CSR_READ_4(sc, ALC_RXQ_CFG);
	if ((sc->alc_flags & ALC_FLAG_AR816X_FAMILY) == 0) {
		if ((reg & RXQ_CFG_ENB) != 0) {
			reg &= ~RXQ_CFG_ENB;
			CSR_WRITE_4(sc, ALC_RXQ_CFG, reg);
		}
	} else {
		if ((reg & RXQ_CFG_QUEUE0_ENB) != 0) {
			reg &= ~RXQ_CFG_QUEUE0_ENB;
			CSR_WRITE_4(sc, ALC_RXQ_CFG, reg);
		}
	}
	/* Disable TxQ. */
	reg = CSR_READ_4(sc, ALC_TXQ_CFG);
	if ((reg & TXQ_CFG_ENB) != 0) {
		reg &= ~TXQ_CFG_ENB;
		CSR_WRITE_4(sc, ALC_TXQ_CFG, reg);
	}
	DELAY(40);
	for (i = ALC_TIMEOUT; i > 0; i--) {
		reg = CSR_READ_4(sc, ALC_IDLE_STATUS);
		if ((reg & (IDLE_STATUS_RXQ | IDLE_STATUS_TXQ)) == 0)
			break;
		DELAY(10);
	}
	if (i == 0)
		device_printf(sc->alc_dev,
		    "could not disable RxQ/TxQ (0x%08x)!\n", reg);
}