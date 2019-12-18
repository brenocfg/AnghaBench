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
struct sis_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIO_CLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIO_SET (int /*<<< orphan*/ ) ; 
 int SIS_EECMD_READ ; 
 int /*<<< orphan*/  SIS_EECTL_CLK ; 
 int /*<<< orphan*/  SIS_EECTL_DIN ; 
 int /*<<< orphan*/  sis_delay (struct sis_softc*) ; 

__attribute__((used)) static void
sis_eeprom_putbyte(struct sis_softc *sc, int addr)
{
	int		d, i;

	d = addr | SIS_EECMD_READ;

	/*
	 * Feed in each bit and stobe the clock.
	 */
	for (i = 0x400; i; i >>= 1) {
		if (d & i) {
			SIO_SET(SIS_EECTL_DIN);
		} else {
			SIO_CLR(SIS_EECTL_DIN);
		}
		sis_delay(sc);
		SIO_SET(SIS_EECTL_CLK);
		sis_delay(sc);
		SIO_CLR(SIS_EECTL_CLK);
		sis_delay(sc);
	}
}