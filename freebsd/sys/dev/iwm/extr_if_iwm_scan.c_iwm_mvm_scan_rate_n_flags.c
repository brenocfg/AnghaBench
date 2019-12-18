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
struct iwm_softc {int sc_scan_last_antenna; } ;

/* Variables and functions */
 int IEEE80211_CHAN_2GHZ ; 
 int IWM_RATE_1M_PLCP ; 
 int IWM_RATE_6M_PLCP ; 
 int IWM_RATE_MCS_ANT_NUM ; 
 int IWM_RATE_MCS_ANT_POS ; 
 int IWM_RATE_MCS_CCK_MSK ; 
 int htole32 (int) ; 
 int iwm_mvm_get_valid_tx_ant (struct iwm_softc*) ; 

__attribute__((used)) static uint32_t
iwm_mvm_scan_rate_n_flags(struct iwm_softc *sc, int flags, int no_cck)
{
	uint32_t tx_ant;
	int i, ind;

	for (i = 0, ind = sc->sc_scan_last_antenna;
	    i < IWM_RATE_MCS_ANT_NUM; i++) {
		ind = (ind + 1) % IWM_RATE_MCS_ANT_NUM;
		if (iwm_mvm_get_valid_tx_ant(sc) & (1 << ind)) {
			sc->sc_scan_last_antenna = ind;
			break;
		}
	}
	tx_ant = (1 << sc->sc_scan_last_antenna) << IWM_RATE_MCS_ANT_POS;

	if ((flags & IEEE80211_CHAN_2GHZ) && !no_cck)
		return htole32(IWM_RATE_1M_PLCP | IWM_RATE_MCS_CCK_MSK |
				   tx_ant);
	else
		return htole32(IWM_RATE_6M_PLCP | tx_ant);
}