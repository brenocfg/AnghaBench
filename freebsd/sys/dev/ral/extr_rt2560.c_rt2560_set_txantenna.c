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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct rt2560_softc {scalar_t__ rf_rev; } ;

/* Variables and functions */
 int RAL_READ (struct rt2560_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2560_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT2560_BBPCSR1 ; 
 int RT2560_BBP_ANTA ; 
 int RT2560_BBP_ANTB ; 
 int RT2560_BBP_ANTMASK ; 
 int RT2560_BBP_DIVERSITY ; 
 int RT2560_BBP_FLIPIQ ; 
 int /*<<< orphan*/  RT2560_BBP_TX ; 
 scalar_t__ RT2560_RF_2525E ; 
 scalar_t__ RT2560_RF_2526 ; 
 scalar_t__ RT2560_RF_5222 ; 
 int rt2560_bbp_read (struct rt2560_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2560_bbp_write (struct rt2560_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rt2560_set_txantenna(struct rt2560_softc *sc, int antenna)
{
	uint32_t tmp;
	uint8_t tx;

	tx = rt2560_bbp_read(sc, RT2560_BBP_TX) & ~RT2560_BBP_ANTMASK;
	if (antenna == 1)
		tx |= RT2560_BBP_ANTA;
	else if (antenna == 2)
		tx |= RT2560_BBP_ANTB;
	else
		tx |= RT2560_BBP_DIVERSITY;

	/* need to force I/Q flip for RF 2525e, 2526 and 5222 */
	if (sc->rf_rev == RT2560_RF_2525E || sc->rf_rev == RT2560_RF_2526 ||
	    sc->rf_rev == RT2560_RF_5222)
		tx |= RT2560_BBP_FLIPIQ;

	rt2560_bbp_write(sc, RT2560_BBP_TX, tx);

	/* update values for CCK and OFDM in BBPCSR1 */
	tmp = RAL_READ(sc, RT2560_BBPCSR1) & ~0x00070007;
	tmp |= (tx & 0x7) << 16 | (tx & 0x7);
	RAL_WRITE(sc, RT2560_BBPCSR1, tmp);
}