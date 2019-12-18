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
struct nge_softc {int dummy; } ;

/* Variables and functions */
 int NGE_EECMD_READ ; 
 int /*<<< orphan*/  NGE_MEAR_EE_CLK ; 
 int /*<<< orphan*/  NGE_MEAR_EE_DIN ; 
 int /*<<< orphan*/  SIO_CLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIO_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nge_delay (struct nge_softc*) ; 

__attribute__((used)) static void
nge_eeprom_putbyte(struct nge_softc *sc, int addr)
{
	int d, i;

	d = addr | NGE_EECMD_READ;

	/*
	 * Feed in each bit and stobe the clock.
	 */
	for (i = 0x400; i; i >>= 1) {
		if (d & i) {
			SIO_SET(NGE_MEAR_EE_DIN);
		} else {
			SIO_CLR(NGE_MEAR_EE_DIN);
		}
		nge_delay(sc);
		SIO_SET(NGE_MEAR_EE_CLK);
		nge_delay(sc);
		SIO_CLR(NGE_MEAR_EE_CLK);
		nge_delay(sc);
	}
}