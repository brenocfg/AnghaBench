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
typedef  int uint16_t ;
struct ural_softc {scalar_t__ rf_rev; } ;

/* Variables and functions */
 int RAL_BBP_ANTA ; 
 int RAL_BBP_ANTB ; 
 int RAL_BBP_ANTMASK ; 
 int RAL_BBP_DIVERSITY ; 
 int RAL_BBP_FLIPIQ ; 
 int /*<<< orphan*/  RAL_BBP_TX ; 
 int /*<<< orphan*/  RAL_PHY_CSR5 ; 
 int /*<<< orphan*/  RAL_PHY_CSR6 ; 
 scalar_t__ RAL_RF_2525E ; 
 scalar_t__ RAL_RF_2526 ; 
 scalar_t__ RAL_RF_5222 ; 
 int ural_bbp_read (struct ural_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ural_bbp_write (struct ural_softc*,int /*<<< orphan*/ ,int) ; 
 int ural_read (struct ural_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ural_write (struct ural_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ural_set_txantenna(struct ural_softc *sc, int antenna)
{
	uint16_t tmp;
	uint8_t tx;

	tx = ural_bbp_read(sc, RAL_BBP_TX) & ~RAL_BBP_ANTMASK;
	if (antenna == 1)
		tx |= RAL_BBP_ANTA;
	else if (antenna == 2)
		tx |= RAL_BBP_ANTB;
	else
		tx |= RAL_BBP_DIVERSITY;

	/* need to force I/Q flip for RF 2525e, 2526 and 5222 */
	if (sc->rf_rev == RAL_RF_2525E || sc->rf_rev == RAL_RF_2526 ||
	    sc->rf_rev == RAL_RF_5222)
		tx |= RAL_BBP_FLIPIQ;

	ural_bbp_write(sc, RAL_BBP_TX, tx);

	/* update values in PHY_CSR5 and PHY_CSR6 */
	tmp = ural_read(sc, RAL_PHY_CSR5) & ~0x7;
	ural_write(sc, RAL_PHY_CSR5, tmp | (tx & 0x7));

	tmp = ural_read(sc, RAL_PHY_CSR6) & ~0x7;
	ural_write(sc, RAL_PHY_CSR6, tmp | (tx & 0x7));
}