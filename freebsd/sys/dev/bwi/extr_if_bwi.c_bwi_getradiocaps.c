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
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211com {struct bwi_softc* ic_softc; } ;
struct ieee80211_channel {int dummy; } ;
struct bwi_softc {int /*<<< orphan*/  sc_dev; struct bwi_mac* sc_mac; } ;
struct bwi_phy {int phy_mode; } ;
struct bwi_mac {struct bwi_phy mac_phy; } ;
typedef  int /*<<< orphan*/  bands ;

/* Variables and functions */
#define  IEEE80211_MODE_11A 130 
#define  IEEE80211_MODE_11B 129 
#define  IEEE80211_MODE_11G 128 
 int IEEE80211_MODE_BYTES ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ieee80211_add_channels_default_2ghz (struct ieee80211_channel*,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ *,int const) ; 

__attribute__((used)) static void
bwi_getradiocaps(struct ieee80211com *ic,
    int maxchans, int *nchans, struct ieee80211_channel chans[])
{
	struct bwi_softc *sc = ic->ic_softc;
	struct bwi_mac *mac;
	struct bwi_phy *phy;
	uint8_t bands[IEEE80211_MODE_BYTES];

	/*
	 * XXX First MAC is known to exist
	 * TODO2
	 */
	mac = &sc->sc_mac[0];
	phy = &mac->mac_phy;

	memset(bands, 0, sizeof(bands));
	switch (phy->phy_mode) {
	case IEEE80211_MODE_11G:
		setbit(bands, IEEE80211_MODE_11G);
		/* FALLTHROUGH */
	case IEEE80211_MODE_11B:
		setbit(bands, IEEE80211_MODE_11B);
		break;
	case IEEE80211_MODE_11A:
		/* TODO:11A */
		setbit(bands, IEEE80211_MODE_11A);
		device_printf(sc->sc_dev, "no 11a support\n");
		return;
	default:
		panic("unknown phymode %d\n", phy->phy_mode);
	}

	ieee80211_add_channels_default_2ghz(chans, maxchans, nchans, bands, 0);
}