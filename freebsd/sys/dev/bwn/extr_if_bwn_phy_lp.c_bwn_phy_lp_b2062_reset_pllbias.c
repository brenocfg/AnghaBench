#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ chip_id; } ;
struct bwn_softc {TYPE_1__ sc_cid; } ;
struct bwn_mac {struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 scalar_t__ BHND_CHIPID_BCM5354 ; 
 int /*<<< orphan*/  BWN_B2062_N_COM1 ; 
 int /*<<< orphan*/  BWN_B2062_S_RFPLLCTL2 ; 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 

__attribute__((used)) static void
bwn_phy_lp_b2062_reset_pllbias(struct bwn_mac *mac)
{
	struct bwn_softc *sc = mac->mac_sc;

	BWN_RF_WRITE(mac, BWN_B2062_S_RFPLLCTL2, 0xff);
	DELAY(20);
	if (sc->sc_cid.chip_id == BHND_CHIPID_BCM5354) {
		BWN_RF_WRITE(mac, BWN_B2062_N_COM1, 4);
		BWN_RF_WRITE(mac, BWN_B2062_S_RFPLLCTL2, 4);
	} else {
		BWN_RF_WRITE(mac, BWN_B2062_S_RFPLLCTL2, 0);
	}
	DELAY(5);
}