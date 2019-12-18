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
typedef  int uint16_t ;
struct bwn_softc {int /*<<< orphan*/  sc_dev; } ;
struct bwn_mac {struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_NPHY_CLASSCTL ; 
 int BWN_NPHY_CLASSCTL_CCKEN ; 
 int BWN_NPHY_CLASSCTL_OFDMEN ; 
 int BWN_NPHY_CLASSCTL_WAITEDEN ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int bhnd_get_hwrev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_mac_enable (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_mac_suspend (struct bwn_mac*) ; 

__attribute__((used)) static uint16_t bwn_nphy_classifier(struct bwn_mac *mac, uint16_t mask, uint16_t val)
{
	struct bwn_softc *sc = mac->mac_sc;
	uint16_t tmp;

	if (bhnd_get_hwrev(sc->sc_dev) == 16)
		bwn_mac_suspend(mac);

	tmp = BWN_PHY_READ(mac, BWN_NPHY_CLASSCTL);
	tmp &= (BWN_NPHY_CLASSCTL_CCKEN | BWN_NPHY_CLASSCTL_OFDMEN |
		BWN_NPHY_CLASSCTL_WAITEDEN);
	tmp &= ~mask;
	tmp |= (val & mask);
	BWN_PHY_SETMASK(mac, BWN_NPHY_CLASSCTL, 0xFFF8, tmp);

	if (bhnd_get_hwrev(sc->sc_dev) == 16)
		bwn_mac_enable(mac);

	return tmp;
}