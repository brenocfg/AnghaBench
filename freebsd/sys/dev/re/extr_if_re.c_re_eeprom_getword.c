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
typedef  int u_int16_t ;
struct rl_softc {int dummy; } ;

/* Variables and functions */
 int CSR_READ_1 (struct rl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  EE_CLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EE_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RL_EECMD ; 
 int /*<<< orphan*/  RL_EE_CLK ; 
 int RL_EE_DATAOUT ; 
 int /*<<< orphan*/  re_eeprom_putbyte (struct rl_softc*,int) ; 

__attribute__((used)) static void
re_eeprom_getword(struct rl_softc *sc, int addr, u_int16_t *dest)
{
	int			i;
	u_int16_t		word = 0;

	/*
	 * Send address of word we want to read.
	 */
	re_eeprom_putbyte(sc, addr);

	/*
	 * Start reading bits from EEPROM.
	 */
	for (i = 0x8000; i; i >>= 1) {
		EE_SET(RL_EE_CLK);
		DELAY(100);
		if (CSR_READ_1(sc, RL_EECMD) & RL_EE_DATAOUT)
			word |= i;
		EE_CLR(RL_EE_CLK);
		DELAY(100);
	}

	*dest = word;
}