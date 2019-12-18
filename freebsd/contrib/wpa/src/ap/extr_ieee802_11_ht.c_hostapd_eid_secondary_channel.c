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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int sec_channel_offset; int /*<<< orphan*/  channel; } ;
struct hostapd_data {TYPE_1__ cs_freq_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  HT_INFO_HT_PARAM_SECONDARY_CHNL_ABOVE ; 
 int /*<<< orphan*/  HT_INFO_HT_PARAM_SECONDARY_CHNL_BELOW ; 
 int /*<<< orphan*/  WLAN_EID_SECONDARY_CHANNEL_OFFSET ; 

u8 * hostapd_eid_secondary_channel(struct hostapd_data *hapd, u8 *eid)
{
	u8 sec_ch;

	if (!hapd->cs_freq_params.channel ||
	    !hapd->cs_freq_params.sec_channel_offset)
		return eid;

	if (hapd->cs_freq_params.sec_channel_offset == -1)
		sec_ch = HT_INFO_HT_PARAM_SECONDARY_CHNL_BELOW;
	else if (hapd->cs_freq_params.sec_channel_offset == 1)
		sec_ch = HT_INFO_HT_PARAM_SECONDARY_CHNL_ABOVE;
	else
		return eid;

	*eid++ = WLAN_EID_SECONDARY_CHANNEL_OFFSET;
	*eid++ = 1;
	*eid++ = sec_ch;

	return eid;
}