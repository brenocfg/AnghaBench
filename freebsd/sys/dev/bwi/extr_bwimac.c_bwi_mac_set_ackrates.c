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
struct ieee80211_rateset {int rs_nrates; int* rs_rates; } ;
struct ieee80211_rate_table {int dummy; } ;
struct bwi_mac {int dummy; } ;
typedef  enum ieee80211_phytype { ____Placeholder_ieee80211_phytype } ieee80211_phytype ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_COMM_MOBJ ; 
 int IEEE80211_RATE_VAL ; 
#define  IEEE80211_T_DS 129 
#define  IEEE80211_T_OFDM 128 
 int /*<<< orphan*/  MOBJ_READ_2 (struct bwi_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MOBJ_WRITE_2 (struct bwi_mac*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ieee80211_rate2phytype (struct ieee80211_rate_table const*,int) ; 
 int ieee80211_rate2plcp (int,int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static void
bwi_mac_set_ackrates(struct bwi_mac *mac, const struct ieee80211_rate_table *rt,
	const struct ieee80211_rateset *rs)
{
	int i;

	/* XXX not standard conforming */
	for (i = 0; i < rs->rs_nrates; ++i) {
		enum ieee80211_phytype modtype;
		uint16_t ofs;

		modtype = ieee80211_rate2phytype(rt,
		    rs->rs_rates[i] & IEEE80211_RATE_VAL);
		switch (modtype) {
		case IEEE80211_T_DS:
			ofs = 0x4c0;
			break;
		case IEEE80211_T_OFDM:
			ofs = 0x480;
			break;
		default:
			panic("unsupported modtype %u\n", modtype);
		}
		ofs += 2*(ieee80211_rate2plcp(
		    rs->rs_rates[i] & IEEE80211_RATE_VAL,
		    modtype) & 0xf);

		MOBJ_WRITE_2(mac, BWI_COMM_MOBJ, ofs + 0x20,
			     MOBJ_READ_2(mac, BWI_COMM_MOBJ, ofs));
	}
}