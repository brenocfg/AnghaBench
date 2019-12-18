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
typedef  void* u8 ;
struct TYPE_2__ {int bandwidth; int center_freq2; int center_freq1; int freq; int /*<<< orphan*/  vht_enabled; int /*<<< orphan*/  channel; } ;
struct hostapd_data {TYPE_1__ cs_freq_params; } ;

/* Variables and functions */
 scalar_t__ HOSTAPD_MODE_IEEE80211A ; 
 int /*<<< orphan*/  WLAN_EID_VHT_CHANNEL_SWITCH_WRAPPER ; 
 int /*<<< orphan*/  WLAN_EID_VHT_WIDE_BW_CHSWITCH ; 
 scalar_t__ ieee80211_freq_to_chan (int,void**) ; 

u8 * hostapd_eid_wb_chsw_wrapper(struct hostapd_data *hapd, u8 *eid)
{
	u8 bw, chan1, chan2 = 0;
	int freq1;

	if (!hapd->cs_freq_params.channel ||
	    !hapd->cs_freq_params.vht_enabled)
		return eid;

	/* bandwidth: 0: 40, 1: 80, 2: 160, 3: 80+80 */
	switch (hapd->cs_freq_params.bandwidth) {
	case 40:
		bw = 0;
		break;
	case 80:
		/* check if it's 80+80 */
		if (!hapd->cs_freq_params.center_freq2)
			bw = 1;
		else
			bw = 3;
		break;
	case 160:
		bw = 2;
		break;
	default:
		/* not valid VHT bandwidth or not in CSA */
		return eid;
	}

	freq1 = hapd->cs_freq_params.center_freq1 ?
		hapd->cs_freq_params.center_freq1 :
		hapd->cs_freq_params.freq;
	if (ieee80211_freq_to_chan(freq1, &chan1) !=
	    HOSTAPD_MODE_IEEE80211A)
		return eid;

	if (hapd->cs_freq_params.center_freq2 &&
	    ieee80211_freq_to_chan(hapd->cs_freq_params.center_freq2,
				   &chan2) != HOSTAPD_MODE_IEEE80211A)
		return eid;

	*eid++ = WLAN_EID_VHT_CHANNEL_SWITCH_WRAPPER;
	*eid++ = 5; /* Length of Channel Switch Wrapper */
	*eid++ = WLAN_EID_VHT_WIDE_BW_CHSWITCH;
	*eid++ = 3; /* Length of Wide Bandwidth Channel Switch element */
	*eid++ = bw; /* New Channel Width */
	*eid++ = chan1; /* New Channel Center Frequency Segment 0 */
	*eid++ = chan2; /* New Channel Center Frequency Segment 1 */

	return eid;
}