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
 int BWI_BBP_ATTEN_MAX ; 
 int BWI_RF_ATTEN_FACTOR ; 
 int BWI_RF_ATTEN_MAX0 ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 

__attribute__((used)) static __inline void
bwi_mac_balance_atten(int *bbp_atten0, int *rf_atten0)
{
	int bbp_atten, rf_atten, rf_atten_lim = -1;

	bbp_atten = *bbp_atten0;
	rf_atten = *rf_atten0;

	/*
	 * RF attenuation affects TX power BWI_RF_ATTEN_FACTOR times
	 * as much as BBP attenuation, so we try our best to keep RF
	 * attenuation within range.  BBP attenuation will be clamped
	 * later if it is out of range during balancing.
	 *
	 * BWI_RF_ATTEN_MAX0 is used as RF attenuation upper limit.
	 */

	/*
	 * Use BBP attenuation to balance RF attenuation
	 */
	if (rf_atten < 0)
		rf_atten_lim = 0;
	else if (rf_atten > BWI_RF_ATTEN_MAX0)
		rf_atten_lim = BWI_RF_ATTEN_MAX0;

	if (rf_atten_lim >= 0) {
		bbp_atten += (BWI_RF_ATTEN_FACTOR * (rf_atten - rf_atten_lim));
		rf_atten = rf_atten_lim;
	}

	/*
	 * If possible, use RF attenuation to balance BBP attenuation
	 * NOTE: RF attenuation is still kept within range.
	 */
	while (rf_atten < BWI_RF_ATTEN_MAX0 && bbp_atten > BWI_BBP_ATTEN_MAX) {
		bbp_atten -= BWI_RF_ATTEN_FACTOR;
		++rf_atten;
	}
	while (rf_atten > 0 && bbp_atten < 0) {
		bbp_atten += BWI_RF_ATTEN_FACTOR;
		--rf_atten;
	}

	/* RF attenuation MUST be within range */
	KASSERT(rf_atten >= 0 && rf_atten <= BWI_RF_ATTEN_MAX0,
	    ("rf_atten %d", rf_atten));

	/*
	 * Clamp BBP attenuation
	 */
	if (bbp_atten < 0)
		bbp_atten = 0;
	else if (bbp_atten > BWI_BBP_ATTEN_MAX)
		bbp_atten = BWI_BBP_ATTEN_MAX;

	*rf_atten0 = rf_atten;
	*bbp_atten0 = bbp_atten;
}