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
struct rl_softc {int rl_eecmd_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  EE_CLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EE_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RL_EE_CLK ; 
 int /*<<< orphan*/  RL_EE_DATAIN ; 

__attribute__((used)) static void
rl_eeprom_putbyte(struct rl_softc *sc, int addr)
{
	int			d, i;

	d = addr | sc->rl_eecmd_read;

	/*
	 * Feed in each bit and strobe the clock.
	 */
	for (i = 0x400; i; i >>= 1) {
		if (d & i) {
			EE_SET(RL_EE_DATAIN);
		} else {
			EE_CLR(RL_EE_DATAIN);
		}
		DELAY(100);
		EE_SET(RL_EE_CLK);
		DELAY(150);
		EE_CLR(RL_EE_CLK);
		DELAY(100);
	}
}