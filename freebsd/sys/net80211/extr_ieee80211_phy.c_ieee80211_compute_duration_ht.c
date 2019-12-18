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
typedef  int uint16_t ;

/* Variables and functions */
 int HT_LTF (int) ; 
 int HT_L_LTF ; 
 int HT_L_SIG ; 
 int HT_L_STF ; 
 int HT_SIG ; 
 int HT_STF ; 
 int IEEE80211_RATE_MCS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int OFDM_PLCP_BITS ; 
 int howmany (int,int) ; 
 int* ht20_bps ; 
 int* ht40_bps ; 

uint32_t
ieee80211_compute_duration_ht(uint32_t frameLen, uint16_t rate,
    int streams, int isht40, int isShortGI)
{
	uint32_t bitsPerSymbol, numBits, numSymbols, txTime;

	KASSERT(rate & IEEE80211_RATE_MCS, ("not mcs %d", rate));
	KASSERT((rate &~ IEEE80211_RATE_MCS) < 31, ("bad mcs 0x%x", rate));

	if (isht40)
		bitsPerSymbol = ht40_bps[rate & 0x1f];
	else
		bitsPerSymbol = ht20_bps[rate & 0x1f];
	numBits = OFDM_PLCP_BITS + (frameLen << 3);
	numSymbols = howmany(numBits, bitsPerSymbol);
	if (isShortGI)
		txTime = ((numSymbols * 18) + 4) / 5;   /* 3.6us */
	else
		txTime = numSymbols * 4;                /* 4us */
	return txTime + HT_L_STF + HT_L_LTF +
	    HT_L_SIG + HT_SIG + HT_STF + HT_LTF(streams);
}