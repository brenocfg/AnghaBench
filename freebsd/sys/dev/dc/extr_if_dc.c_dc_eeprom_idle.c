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
struct dc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_4 (struct dc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DC_CLRBIT (struct dc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_SETBIT (struct dc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_SIO ; 
 int DC_SIO_EESEL ; 
 int /*<<< orphan*/  DC_SIO_EE_CLK ; 
 int /*<<< orphan*/  DC_SIO_EE_CS ; 
 int /*<<< orphan*/  DC_SIO_ROMCTL_READ ; 
 int /*<<< orphan*/  dc_delay (struct dc_softc*) ; 

__attribute__((used)) static void
dc_eeprom_idle(struct dc_softc *sc)
{
	int i;

	CSR_WRITE_4(sc, DC_SIO, DC_SIO_EESEL);
	dc_delay(sc);
	DC_SETBIT(sc, DC_SIO, DC_SIO_ROMCTL_READ);
	dc_delay(sc);
	DC_CLRBIT(sc, DC_SIO, DC_SIO_EE_CLK);
	dc_delay(sc);
	DC_SETBIT(sc, DC_SIO, DC_SIO_EE_CS);
	dc_delay(sc);

	for (i = 0; i < 25; i++) {
		DC_CLRBIT(sc, DC_SIO, DC_SIO_EE_CLK);
		dc_delay(sc);
		DC_SETBIT(sc, DC_SIO, DC_SIO_EE_CLK);
		dc_delay(sc);
	}

	DC_CLRBIT(sc, DC_SIO, DC_SIO_EE_CLK);
	dc_delay(sc);
	DC_CLRBIT(sc, DC_SIO, DC_SIO_EE_CS);
	dc_delay(sc);
	CSR_WRITE_4(sc, DC_SIO, 0x00000000);
}