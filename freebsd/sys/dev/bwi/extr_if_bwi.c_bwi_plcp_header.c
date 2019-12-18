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
struct ieee80211_rate_table {int dummy; } ;
typedef  enum ieee80211_phytype { ____Placeholder_ieee80211_phytype } ieee80211_phytype ;

/* Variables and functions */
 int IEEE80211_T_DS ; 
 int IEEE80211_T_OFDM ; 
 int /*<<< orphan*/  bwi_ds_plcp_header (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwi_ofdm_plcp_header (void*,int,int /*<<< orphan*/ ) ; 
 int ieee80211_rate2phytype (struct ieee80211_rate_table const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static __inline void
bwi_plcp_header(const struct ieee80211_rate_table *rt,
	void *plcp, int pkt_len, uint8_t rate)
{
	enum ieee80211_phytype modtype;

	/*
	 * Assume caller has zeroed 'plcp'
	 */
	modtype = ieee80211_rate2phytype(rt, rate);
	if (modtype == IEEE80211_T_OFDM)
		bwi_ofdm_plcp_header(plcp, pkt_len, rate);
	else if (modtype == IEEE80211_T_DS)
		bwi_ds_plcp_header(plcp, pkt_len, rate);
	else
		panic("unsupport modulation type %u\n", modtype);
}