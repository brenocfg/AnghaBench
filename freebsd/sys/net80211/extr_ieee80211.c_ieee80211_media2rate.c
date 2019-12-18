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

/* Variables and functions */
 size_t IFM_SUBTYPE (int) ; 
 size_t nitems (int const*) ; 

int
ieee80211_media2rate(int mword)
{
	static const int ieeerates[] = {
		-1,		/* IFM_AUTO */
		0,		/* IFM_MANUAL */
		0,		/* IFM_NONE */
		2,		/* IFM_IEEE80211_FH1 */
		4,		/* IFM_IEEE80211_FH2 */
		2,		/* IFM_IEEE80211_DS1 */
		4,		/* IFM_IEEE80211_DS2 */
		11,		/* IFM_IEEE80211_DS5 */
		22,		/* IFM_IEEE80211_DS11 */
		44,		/* IFM_IEEE80211_DS22 */
		12,		/* IFM_IEEE80211_OFDM6 */
		18,		/* IFM_IEEE80211_OFDM9 */
		24,		/* IFM_IEEE80211_OFDM12 */
		36,		/* IFM_IEEE80211_OFDM18 */
		48,		/* IFM_IEEE80211_OFDM24 */
		72,		/* IFM_IEEE80211_OFDM36 */
		96,		/* IFM_IEEE80211_OFDM48 */
		108,		/* IFM_IEEE80211_OFDM54 */
		144,		/* IFM_IEEE80211_OFDM72 */
		0,		/* IFM_IEEE80211_DS354k */
		0,		/* IFM_IEEE80211_DS512k */
		6,		/* IFM_IEEE80211_OFDM3 */
		9,		/* IFM_IEEE80211_OFDM4 */
		54,		/* IFM_IEEE80211_OFDM27 */
		-1,		/* IFM_IEEE80211_MCS */
		-1,		/* IFM_IEEE80211_VHT */
	};
	return IFM_SUBTYPE(mword) < nitems(ieeerates) ?
		ieeerates[IFM_SUBTYPE(mword)] : 0;
}