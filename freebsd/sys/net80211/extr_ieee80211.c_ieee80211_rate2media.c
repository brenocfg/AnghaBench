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
struct ratemedia {int member_0; int /*<<< orphan*/  const member_1; } ;
struct ieee80211com {int /*<<< orphan*/  ic_phytype; } ;
typedef  enum ieee80211_phymode { ____Placeholder_ieee80211_phymode } ieee80211_phymode ;

/* Variables and functions */
#define  IEEE80211_MODE_11A 164 
#define  IEEE80211_MODE_11B 163 
#define  IEEE80211_MODE_11G 162 
#define  IEEE80211_MODE_11NA 161 
#define  IEEE80211_MODE_11NG 160 
#define  IEEE80211_MODE_AUTO 159 
#define  IEEE80211_MODE_FH 158 
#define  IEEE80211_MODE_HALF 157 
#define  IEEE80211_MODE_QUARTER 156 
#define  IEEE80211_MODE_STURBO_A 155 
#define  IEEE80211_MODE_TURBO_A 154 
#define  IEEE80211_MODE_TURBO_G 153 
#define  IEEE80211_MODE_VHT_2GHZ 152 
#define  IEEE80211_MODE_VHT_5GHZ 151 
 int IEEE80211_RATE_MCS ; 
 int IEEE80211_RATE_VAL ; 
 int /*<<< orphan*/  IEEE80211_T_FH ; 
 int IFM_AUTO ; 
#define  IFM_IEEE80211_11A 150 
#define  IFM_IEEE80211_11B 149 
#define  IFM_IEEE80211_11G 148 
 int IFM_IEEE80211_11NA ; 
 int IFM_IEEE80211_11NG ; 
#define  IFM_IEEE80211_DS1 147 
#define  IFM_IEEE80211_DS11 146 
#define  IFM_IEEE80211_DS2 145 
#define  IFM_IEEE80211_DS22 144 
#define  IFM_IEEE80211_DS5 143 
#define  IFM_IEEE80211_FH 142 
#define  IFM_IEEE80211_FH1 141 
#define  IFM_IEEE80211_FH2 140 
#define  IFM_IEEE80211_MCS 139 
#define  IFM_IEEE80211_OFDM12 138 
#define  IFM_IEEE80211_OFDM18 137 
#define  IFM_IEEE80211_OFDM24 136 
#define  IFM_IEEE80211_OFDM27 135 
#define  IFM_IEEE80211_OFDM3 134 
#define  IFM_IEEE80211_OFDM36 133 
#define  IFM_IEEE80211_OFDM4 132 
#define  IFM_IEEE80211_OFDM48 131 
#define  IFM_IEEE80211_OFDM54 130 
#define  IFM_IEEE80211_OFDM6 129 
#define  IFM_IEEE80211_OFDM9 128 
 int findmedia (struct ratemedia const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nitems (struct ratemedia const*) ; 

int
ieee80211_rate2media(struct ieee80211com *ic, int rate, enum ieee80211_phymode mode)
{
	static const struct ratemedia rates[] = {
		{   2 | IFM_IEEE80211_FH, IFM_IEEE80211_FH1 },
		{   4 | IFM_IEEE80211_FH, IFM_IEEE80211_FH2 },
		{   2 | IFM_IEEE80211_11B, IFM_IEEE80211_DS1 },
		{   4 | IFM_IEEE80211_11B, IFM_IEEE80211_DS2 },
		{  11 | IFM_IEEE80211_11B, IFM_IEEE80211_DS5 },
		{  22 | IFM_IEEE80211_11B, IFM_IEEE80211_DS11 },
		{  44 | IFM_IEEE80211_11B, IFM_IEEE80211_DS22 },
		{  12 | IFM_IEEE80211_11A, IFM_IEEE80211_OFDM6 },
		{  18 | IFM_IEEE80211_11A, IFM_IEEE80211_OFDM9 },
		{  24 | IFM_IEEE80211_11A, IFM_IEEE80211_OFDM12 },
		{  36 | IFM_IEEE80211_11A, IFM_IEEE80211_OFDM18 },
		{  48 | IFM_IEEE80211_11A, IFM_IEEE80211_OFDM24 },
		{  72 | IFM_IEEE80211_11A, IFM_IEEE80211_OFDM36 },
		{  96 | IFM_IEEE80211_11A, IFM_IEEE80211_OFDM48 },
		{ 108 | IFM_IEEE80211_11A, IFM_IEEE80211_OFDM54 },
		{   2 | IFM_IEEE80211_11G, IFM_IEEE80211_DS1 },
		{   4 | IFM_IEEE80211_11G, IFM_IEEE80211_DS2 },
		{  11 | IFM_IEEE80211_11G, IFM_IEEE80211_DS5 },
		{  22 | IFM_IEEE80211_11G, IFM_IEEE80211_DS11 },
		{  12 | IFM_IEEE80211_11G, IFM_IEEE80211_OFDM6 },
		{  18 | IFM_IEEE80211_11G, IFM_IEEE80211_OFDM9 },
		{  24 | IFM_IEEE80211_11G, IFM_IEEE80211_OFDM12 },
		{  36 | IFM_IEEE80211_11G, IFM_IEEE80211_OFDM18 },
		{  48 | IFM_IEEE80211_11G, IFM_IEEE80211_OFDM24 },
		{  72 | IFM_IEEE80211_11G, IFM_IEEE80211_OFDM36 },
		{  96 | IFM_IEEE80211_11G, IFM_IEEE80211_OFDM48 },
		{ 108 | IFM_IEEE80211_11G, IFM_IEEE80211_OFDM54 },
		{   6 | IFM_IEEE80211_11A, IFM_IEEE80211_OFDM3 },
		{   9 | IFM_IEEE80211_11A, IFM_IEEE80211_OFDM4 },
		{  54 | IFM_IEEE80211_11A, IFM_IEEE80211_OFDM27 },
		/* NB: OFDM72 doesn't really exist so we don't handle it */
	};
	static const struct ratemedia htrates[] = {
		{   0, IFM_IEEE80211_MCS },
		{   1, IFM_IEEE80211_MCS },
		{   2, IFM_IEEE80211_MCS },
		{   3, IFM_IEEE80211_MCS },
		{   4, IFM_IEEE80211_MCS },
		{   5, IFM_IEEE80211_MCS },
		{   6, IFM_IEEE80211_MCS },
		{   7, IFM_IEEE80211_MCS },
		{   8, IFM_IEEE80211_MCS },
		{   9, IFM_IEEE80211_MCS },
		{  10, IFM_IEEE80211_MCS },
		{  11, IFM_IEEE80211_MCS },
		{  12, IFM_IEEE80211_MCS },
		{  13, IFM_IEEE80211_MCS },
		{  14, IFM_IEEE80211_MCS },
		{  15, IFM_IEEE80211_MCS },
		{  16, IFM_IEEE80211_MCS },
		{  17, IFM_IEEE80211_MCS },
		{  18, IFM_IEEE80211_MCS },
		{  19, IFM_IEEE80211_MCS },
		{  20, IFM_IEEE80211_MCS },
		{  21, IFM_IEEE80211_MCS },
		{  22, IFM_IEEE80211_MCS },
		{  23, IFM_IEEE80211_MCS },
		{  24, IFM_IEEE80211_MCS },
		{  25, IFM_IEEE80211_MCS },
		{  26, IFM_IEEE80211_MCS },
		{  27, IFM_IEEE80211_MCS },
		{  28, IFM_IEEE80211_MCS },
		{  29, IFM_IEEE80211_MCS },
		{  30, IFM_IEEE80211_MCS },
		{  31, IFM_IEEE80211_MCS },
		{  32, IFM_IEEE80211_MCS },
		{  33, IFM_IEEE80211_MCS },
		{  34, IFM_IEEE80211_MCS },
		{  35, IFM_IEEE80211_MCS },
		{  36, IFM_IEEE80211_MCS },
		{  37, IFM_IEEE80211_MCS },
		{  38, IFM_IEEE80211_MCS },
		{  39, IFM_IEEE80211_MCS },
		{  40, IFM_IEEE80211_MCS },
		{  41, IFM_IEEE80211_MCS },
		{  42, IFM_IEEE80211_MCS },
		{  43, IFM_IEEE80211_MCS },
		{  44, IFM_IEEE80211_MCS },
		{  45, IFM_IEEE80211_MCS },
		{  46, IFM_IEEE80211_MCS },
		{  47, IFM_IEEE80211_MCS },
		{  48, IFM_IEEE80211_MCS },
		{  49, IFM_IEEE80211_MCS },
		{  50, IFM_IEEE80211_MCS },
		{  51, IFM_IEEE80211_MCS },
		{  52, IFM_IEEE80211_MCS },
		{  53, IFM_IEEE80211_MCS },
		{  54, IFM_IEEE80211_MCS },
		{  55, IFM_IEEE80211_MCS },
		{  56, IFM_IEEE80211_MCS },
		{  57, IFM_IEEE80211_MCS },
		{  58, IFM_IEEE80211_MCS },
		{  59, IFM_IEEE80211_MCS },
		{  60, IFM_IEEE80211_MCS },
		{  61, IFM_IEEE80211_MCS },
		{  62, IFM_IEEE80211_MCS },
		{  63, IFM_IEEE80211_MCS },
		{  64, IFM_IEEE80211_MCS },
		{  65, IFM_IEEE80211_MCS },
		{  66, IFM_IEEE80211_MCS },
		{  67, IFM_IEEE80211_MCS },
		{  68, IFM_IEEE80211_MCS },
		{  69, IFM_IEEE80211_MCS },
		{  70, IFM_IEEE80211_MCS },
		{  71, IFM_IEEE80211_MCS },
		{  72, IFM_IEEE80211_MCS },
		{  73, IFM_IEEE80211_MCS },
		{  74, IFM_IEEE80211_MCS },
		{  75, IFM_IEEE80211_MCS },
		{  76, IFM_IEEE80211_MCS },
	};
	int m;

	/*
	 * Check 11n rates first for match as an MCS.
	 */
	if (mode == IEEE80211_MODE_11NA) {
		if (rate & IEEE80211_RATE_MCS) {
			rate &= ~IEEE80211_RATE_MCS;
			m = findmedia(htrates, nitems(htrates), rate);
			if (m != IFM_AUTO)
				return m | IFM_IEEE80211_11NA;
		}
	} else if (mode == IEEE80211_MODE_11NG) {
		/* NB: 12 is ambiguous, it will be treated as an MCS */
		if (rate & IEEE80211_RATE_MCS) {
			rate &= ~IEEE80211_RATE_MCS;
			m = findmedia(htrates, nitems(htrates), rate);
			if (m != IFM_AUTO)
				return m | IFM_IEEE80211_11NG;
		}
	}
	rate &= IEEE80211_RATE_VAL;
	switch (mode) {
	case IEEE80211_MODE_11A:
	case IEEE80211_MODE_HALF:		/* XXX good 'nuf */
	case IEEE80211_MODE_QUARTER:
	case IEEE80211_MODE_11NA:
	case IEEE80211_MODE_TURBO_A:
	case IEEE80211_MODE_STURBO_A:
		return findmedia(rates, nitems(rates),
		    rate | IFM_IEEE80211_11A);
	case IEEE80211_MODE_11B:
		return findmedia(rates, nitems(rates),
		    rate | IFM_IEEE80211_11B);
	case IEEE80211_MODE_FH:
		return findmedia(rates, nitems(rates),
		    rate | IFM_IEEE80211_FH);
	case IEEE80211_MODE_AUTO:
		/* NB: ic may be NULL for some drivers */
		if (ic != NULL && ic->ic_phytype == IEEE80211_T_FH)
			return findmedia(rates, nitems(rates),
			    rate | IFM_IEEE80211_FH);
		/* NB: hack, 11g matches both 11b+11a rates */
		/* fall thru... */
	case IEEE80211_MODE_11G:
	case IEEE80211_MODE_11NG:
	case IEEE80211_MODE_TURBO_G:
		return findmedia(rates, nitems(rates), rate | IFM_IEEE80211_11G);
	case IEEE80211_MODE_VHT_2GHZ:
	case IEEE80211_MODE_VHT_5GHZ:
		/* XXX TODO: need to figure out mapping for VHT rates */
		return IFM_AUTO;
	}
	return IFM_AUTO;
}