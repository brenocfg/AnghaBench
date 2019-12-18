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
struct aic_softc {scalar_t__ internal_codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AICFR ; 
 int AICFR_AUSEL ; 
 int AICFR_BCKD ; 
 int AICFR_ENB ; 
 int AICFR_ICDC ; 
 int AICFR_RFTH (int) ; 
 int AICFR_RST ; 
 int AICFR_SYNCD ; 
 int AICFR_TFTH (int) ; 
 int READ4 (struct aic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct aic_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
aic_configure(struct aic_softc *sc)
{
	int reg;

	WRITE4(sc, AICFR, AICFR_RST);

	/* Configure AIC */
	reg = 0;
	if (sc->internal_codec) {
		reg |= (AICFR_ICDC);
	} else {
		reg |= (AICFR_SYNCD | AICFR_BCKD);
	}
	reg |= (AICFR_AUSEL);	/* I2S/MSB-justified format. */
	reg |= (AICFR_TFTH(8));	/* Transmit FIFO threshold */
	reg |= (AICFR_RFTH(7));	/* Receive FIFO threshold */
	WRITE4(sc, AICFR, reg);

	reg = READ4(sc, AICFR);
	reg |= (AICFR_ENB);	/* Enable the controller. */
	WRITE4(sc, AICFR, reg);

	return (0);
}