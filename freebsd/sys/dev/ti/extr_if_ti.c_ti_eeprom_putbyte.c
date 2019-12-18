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
struct ti_softc {int dummy; } ;

/* Variables and functions */
 int CSR_READ_4 (struct ti_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  TI_CLRBIT (struct ti_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_MISC_LOCAL_CTL ; 
 int /*<<< orphan*/  TI_MLC_EE_CLK ; 
 int TI_MLC_EE_DIN ; 
 int /*<<< orphan*/  TI_MLC_EE_DOUT ; 
 int /*<<< orphan*/  TI_MLC_EE_TXEN ; 
 int /*<<< orphan*/  TI_SETBIT (struct ti_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
ti_eeprom_putbyte(struct ti_softc *sc, int byte)
{
	int i, ack = 0;

	/*
	 * Make sure we're in TX mode.
	 */
	TI_SETBIT(sc, TI_MISC_LOCAL_CTL, TI_MLC_EE_TXEN);

	/*
	 * Feed in each bit and stobe the clock.
	 */
	for (i = 0x80; i; i >>= 1) {
		if (byte & i) {
			TI_SETBIT(sc, TI_MISC_LOCAL_CTL, TI_MLC_EE_DOUT);
		} else {
			TI_CLRBIT(sc, TI_MISC_LOCAL_CTL, TI_MLC_EE_DOUT);
		}
		DELAY(1);
		TI_SETBIT(sc, TI_MISC_LOCAL_CTL, TI_MLC_EE_CLK);
		DELAY(1);
		TI_CLRBIT(sc, TI_MISC_LOCAL_CTL, TI_MLC_EE_CLK);
	}

	/*
	 * Turn off TX mode.
	 */
	TI_CLRBIT(sc, TI_MISC_LOCAL_CTL, TI_MLC_EE_TXEN);

	/*
	 * Check for ack.
	 */
	TI_SETBIT(sc, TI_MISC_LOCAL_CTL, TI_MLC_EE_CLK);
	ack = CSR_READ_4(sc, TI_MISC_LOCAL_CTL) & TI_MLC_EE_DIN;
	TI_CLRBIT(sc, TI_MISC_LOCAL_CTL, TI_MLC_EE_CLK);

	return (ack);
}