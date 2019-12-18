#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_channel {int dummy; } ;
struct ath_softc {int sc_dodfs; int /*<<< orphan*/  sc_ah; } ;
typedef  int /*<<< orphan*/  pe ;
struct TYPE_5__ {int pe_enabled; int pe_extchannel; } ;
typedef  TYPE_1__ HAL_PHYERR_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_CAP_DIVERSITY ; 
 int /*<<< orphan*/  HAL_CAP_PHYDIAG ; 
 scalar_t__ HAL_OK ; 
 int /*<<< orphan*/  IEEE80211_IS_CHAN_DFS (struct ieee80211_channel*) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT40 (struct ieee80211_channel*) ; 
 int /*<<< orphan*/  ath_hal_enabledfs (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ ath_hal_getcapability (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_hal_getdfsdefaultthresh (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ath_hal_setcapability (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,char,int) ; 

int
ath_dfs_radar_enable(struct ath_softc *sc, struct ieee80211_channel *chan)
{
#if 1
	HAL_PHYERR_PARAM pe;

	/* Check if the hardware supports radar reporting */
	/* XXX TODO: migrate HAL_CAP_RADAR/HAL_CAP_AR to somewhere public! */
	if (ath_hal_getcapability(sc->sc_ah,
	    HAL_CAP_PHYDIAG, 0, NULL) != HAL_OK)
		return (0);

	/* Check if the current channel is radar-enabled */
	if (! IEEE80211_IS_CHAN_DFS(chan))
		return (0);

	/* Fetch the default parameters */
	memset(&pe, '\0', sizeof(pe));
	if (! ath_hal_getdfsdefaultthresh(sc->sc_ah, &pe))
		return (0);

	/* Enable radar PHY error reporting */
	sc->sc_dodfs = 1;

	/* Tell the hardware to enable radar reporting */
	pe.pe_enabled = 1;

	/* Flip on extension channel events only if doing HT40 */
	if (IEEE80211_IS_CHAN_HT40(chan))
		pe.pe_extchannel = 1;
	else
		pe.pe_extchannel = 0;

	ath_hal_enabledfs(sc->sc_ah, &pe);

	/*
	 * Disable strong signal fast diversity - needed for
	 * AR5212 and similar PHYs for reliable short pulse
	 * duration.
	 */
	(void) ath_hal_setcapability(sc->sc_ah, HAL_CAP_DIVERSITY, 2, 0, NULL);

	return (1);
#else
	return (0);
#endif
}