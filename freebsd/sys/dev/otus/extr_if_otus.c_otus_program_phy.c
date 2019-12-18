#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int deviceType; } ;
struct TYPE_4__ {TYPE_1__ baseEepHeader; } ;
struct otus_softc {int const* phy_vals; TYPE_2__ eeprom; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR_PHY_POWER_TX_RATE1 ; 
 int /*<<< orphan*/  AR_PHY_POWER_TX_RATE2 ; 
 int /*<<< orphan*/  AR_PHY_POWER_TX_RATE3 ; 
 int /*<<< orphan*/  AR_PHY_POWER_TX_RATE4 ; 
 int /*<<< orphan*/  AR_PHY_POWER_TX_RATE5 ; 
 int /*<<< orphan*/  AR_PHY_POWER_TX_RATE6 ; 
 int /*<<< orphan*/  AR_PHY_POWER_TX_RATE7 ; 
 int /*<<< orphan*/  AR_PHY_POWER_TX_RATE8 ; 
 int /*<<< orphan*/  AR_PHY_POWER_TX_RATE9 ; 
 int /*<<< orphan*/  AR_PHY_POWER_TX_RATE_MAX ; 
 int /*<<< orphan*/  AR_PWR_REG_PLL_ADDAC ; 
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (struct ieee80211_channel*) ; 
 int /*<<< orphan*/ * ar5416_phy_regs ; 
 int* ar5416_phy_vals_2ghz_20mhz ; 
 int* ar5416_phy_vals_5ghz_20mhz ; 
 int nitems (int /*<<< orphan*/ *) ; 
 int otus_set_board_values (struct otus_softc*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  otus_write (struct otus_softc*,int /*<<< orphan*/ ,int const) ; 
 int otus_write_barrier (struct otus_softc*) ; 

int
otus_program_phy(struct otus_softc *sc, struct ieee80211_channel *c)
{
	const uint32_t *vals;
	int error, i;

	/* Select PHY programming based on band and bandwidth. */
	if (IEEE80211_IS_CHAN_2GHZ(c))
		vals = ar5416_phy_vals_2ghz_20mhz;
	else
		vals = ar5416_phy_vals_5ghz_20mhz;
	for (i = 0; i < nitems(ar5416_phy_regs); i++)
		otus_write(sc, AR_PHY(ar5416_phy_regs[i]), vals[i]);
	sc->phy_vals = vals;

	if (sc->eeprom.baseEepHeader.deviceType == 0x80)	/* FEM */
		if ((error = otus_set_board_values(sc, c)) != 0)
			return error;

	/* Initial Tx power settings. */
	otus_write(sc, AR_PHY_POWER_TX_RATE_MAX, 0x7f);
	otus_write(sc, AR_PHY_POWER_TX_RATE1, 0x3f3f3f3f);
	otus_write(sc, AR_PHY_POWER_TX_RATE2, 0x3f3f3f3f);
	otus_write(sc, AR_PHY_POWER_TX_RATE3, 0x3f3f3f3f);
	otus_write(sc, AR_PHY_POWER_TX_RATE4, 0x3f3f3f3f);
	otus_write(sc, AR_PHY_POWER_TX_RATE5, 0x3f3f3f3f);
	otus_write(sc, AR_PHY_POWER_TX_RATE6, 0x3f3f3f3f);
	otus_write(sc, AR_PHY_POWER_TX_RATE7, 0x3f3f3f3f);
	otus_write(sc, AR_PHY_POWER_TX_RATE8, 0x3f3f3f3f);
	otus_write(sc, AR_PHY_POWER_TX_RATE9, 0x3f3f3f3f);

	if (IEEE80211_IS_CHAN_2GHZ(c))
		otus_write(sc, AR_PWR_REG_PLL_ADDAC, 0x5163);
	else
		otus_write(sc, AR_PWR_REG_PLL_ADDAC, 0x5143);

	return otus_write_barrier(sc);
}