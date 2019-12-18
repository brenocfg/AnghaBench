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
struct ieee80211_vht_operation {int vht_op_info_chan_center_freq_seg0_idx; int vht_op_info_chan_center_freq_seg1_idx; int vht_op_info_chwidth; int /*<<< orphan*/  vht_basic_mcs_set; } ;
struct hostapd_data {TYPE_1__* iconf; } ;
struct TYPE_2__ {int vht_oper_centr_freq_seg0_idx; int vht_oper_centr_freq_seg1_idx; int vht_oper_chwidth; scalar_t__ channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_VHT_OPERATION ; 
 int /*<<< orphan*/  host_to_le16 (int) ; 
 int /*<<< orphan*/  os_memset (struct ieee80211_vht_operation*,int /*<<< orphan*/ ,int) ; 

u8 * hostapd_eid_vht_operation(struct hostapd_data *hapd, u8 *eid)
{
	struct ieee80211_vht_operation *oper;
	u8 *pos = eid;

	*pos++ = WLAN_EID_VHT_OPERATION;
	*pos++ = sizeof(*oper);

	oper = (struct ieee80211_vht_operation *) pos;
	os_memset(oper, 0, sizeof(*oper));

	/*
	 * center freq = 5 GHz + (5 * index)
	 * So index 42 gives center freq 5.210 GHz
	 * which is channel 42 in 5G band
	 */
	oper->vht_op_info_chan_center_freq_seg0_idx =
		hapd->iconf->vht_oper_centr_freq_seg0_idx;
	oper->vht_op_info_chan_center_freq_seg1_idx =
		hapd->iconf->vht_oper_centr_freq_seg1_idx;

	oper->vht_op_info_chwidth = hapd->iconf->vht_oper_chwidth;
	if (hapd->iconf->vht_oper_chwidth == 2) {
		/*
		 * Convert 160 MHz channel width to new style as interop
		 * workaround.
		 */
		oper->vht_op_info_chwidth = 1;
		oper->vht_op_info_chan_center_freq_seg1_idx =
			oper->vht_op_info_chan_center_freq_seg0_idx;
		if (hapd->iconf->channel <
		    hapd->iconf->vht_oper_centr_freq_seg0_idx)
			oper->vht_op_info_chan_center_freq_seg0_idx -= 8;
		else
			oper->vht_op_info_chan_center_freq_seg0_idx += 8;
	} else if (hapd->iconf->vht_oper_chwidth == 3) {
		/*
		 * Convert 80+80 MHz channel width to new style as interop
		 * workaround.
		 */
		oper->vht_op_info_chwidth = 1;
	}

	/* VHT Basic MCS set comes from hw */
	/* Hard code 1 stream, MCS0-7 is a min Basic VHT MCS rates */
	oper->vht_basic_mcs_set = host_to_le16(0xfffc);
	pos += sizeof(*oper);

	return pos;
}