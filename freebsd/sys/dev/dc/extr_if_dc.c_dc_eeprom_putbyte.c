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
struct dc_softc {int dc_romwidth; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_CLRBIT (struct dc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DC_EECMD_READ ; 
 int /*<<< orphan*/  DC_SETBIT (struct dc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_SIO ; 
 int /*<<< orphan*/  DC_SIO_EE_CLK ; 
 int /*<<< orphan*/  DC_SIO_EE_DATAIN ; 
 int /*<<< orphan*/  SIO_CLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIO_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_delay (struct dc_softc*) ; 

__attribute__((used)) static void
dc_eeprom_putbyte(struct dc_softc *sc, int addr)
{
	int d, i;

	d = DC_EECMD_READ >> 6;
	for (i = 3; i--; ) {
		if (d & (1 << i))
			DC_SETBIT(sc, DC_SIO, DC_SIO_EE_DATAIN);
		else
			DC_CLRBIT(sc, DC_SIO, DC_SIO_EE_DATAIN);
		dc_delay(sc);
		DC_SETBIT(sc, DC_SIO, DC_SIO_EE_CLK);
		dc_delay(sc);
		DC_CLRBIT(sc, DC_SIO, DC_SIO_EE_CLK);
		dc_delay(sc);
	}

	/*
	 * Feed in each bit and strobe the clock.
	 */
	for (i = sc->dc_romwidth; i--;) {
		if (addr & (1 << i)) {
			SIO_SET(DC_SIO_EE_DATAIN);
		} else {
			SIO_CLR(DC_SIO_EE_DATAIN);
		}
		dc_delay(sc);
		SIO_SET(DC_SIO_EE_CLK);
		dc_delay(sc);
		SIO_CLR(DC_SIO_EE_CLK);
		dc_delay(sc);
	}
}