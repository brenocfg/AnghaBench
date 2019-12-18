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
struct ural_softc {scalar_t__ rf_rev; } ;

/* Variables and functions */
 int RAL_BBP_ANTA ; 
 int RAL_BBP_ANTB ; 
 int RAL_BBP_ANTMASK ; 
 int RAL_BBP_DIVERSITY ; 
 int RAL_BBP_FLIPIQ ; 
 int /*<<< orphan*/  RAL_BBP_RX ; 
 scalar_t__ RAL_RF_2525E ; 
 scalar_t__ RAL_RF_2526 ; 
 int ural_bbp_read (struct ural_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ural_bbp_write (struct ural_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ural_set_rxantenna(struct ural_softc *sc, int antenna)
{
	uint8_t rx;

	rx = ural_bbp_read(sc, RAL_BBP_RX) & ~RAL_BBP_ANTMASK;
	if (antenna == 1)
		rx |= RAL_BBP_ANTA;
	else if (antenna == 2)
		rx |= RAL_BBP_ANTB;
	else
		rx |= RAL_BBP_DIVERSITY;

	/* need to force no I/Q flip for RF 2525e and 2526 */
	if (sc->rf_rev == RAL_RF_2525E || sc->rf_rev == RAL_RF_2526)
		rx &= ~RAL_BBP_FLIPIQ;

	ural_bbp_write(sc, RAL_BBP_RX, rx);
}