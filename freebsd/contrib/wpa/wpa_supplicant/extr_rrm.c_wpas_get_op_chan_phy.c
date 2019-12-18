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
typedef  int u8 ;
struct ieee80211_vht_operation {int vht_op_info_chwidth; int vht_op_info_chan_center_freq_seg0_idx; int vht_op_info_chan_center_freq_seg1_idx; } ;
struct ieee80211_ht_operation {int ht_param; } ;

/* Variables and functions */
 int CHANWIDTH_160MHZ ; 
 int CHANWIDTH_80MHZ ; 
 int CHANWIDTH_80P80MHZ ; 
 int CHANWIDTH_USE_HT ; 
 int HT_INFO_HT_PARAM_SECONDARY_CHNL_ABOVE ; 
 int HT_INFO_HT_PARAM_SECONDARY_CHNL_BELOW ; 
 int HT_INFO_HT_PARAM_SECONDARY_CHNL_OFF_MASK ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ NUM_HOSTAPD_MODES ; 
 int PHY_TYPE_UNSPECIFIED ; 
 int /*<<< orphan*/  WLAN_EID_HT_OPERATION ; 
 int /*<<< orphan*/  WLAN_EID_VHT_OPERATION ; 
 int abs (int) ; 
 int* get_ie (int const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_freq_to_channel_ext (int,int,int,int*,int*) ; 
 int ieee80211_get_phy_type (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int wpas_get_op_chan_phy(int freq, const u8 *ies, size_t ies_len,
				u8 *op_class, u8 *chan, u8 *phy_type)
{
	const u8 *ie;
	int sec_chan = 0, vht = 0;
	struct ieee80211_ht_operation *ht_oper = NULL;
	struct ieee80211_vht_operation *vht_oper = NULL;
	u8 seg0, seg1;

	ie = get_ie(ies, ies_len, WLAN_EID_HT_OPERATION);
	if (ie && ie[1] >= sizeof(struct ieee80211_ht_operation)) {
		u8 sec_chan_offset;

		ht_oper = (struct ieee80211_ht_operation *) (ie + 2);
		sec_chan_offset = ht_oper->ht_param &
			HT_INFO_HT_PARAM_SECONDARY_CHNL_OFF_MASK;
		if (sec_chan_offset == HT_INFO_HT_PARAM_SECONDARY_CHNL_ABOVE)
			sec_chan = 1;
		else if (sec_chan_offset ==
			 HT_INFO_HT_PARAM_SECONDARY_CHNL_BELOW)
			sec_chan = -1;
	}

	ie = get_ie(ies, ies_len, WLAN_EID_VHT_OPERATION);
	if (ie && ie[1] >= sizeof(struct ieee80211_vht_operation)) {
		vht_oper = (struct ieee80211_vht_operation *) (ie + 2);

		switch (vht_oper->vht_op_info_chwidth) {
		case 1:
			seg0 = vht_oper->vht_op_info_chan_center_freq_seg0_idx;
			seg1 = vht_oper->vht_op_info_chan_center_freq_seg1_idx;
			if (seg1 && abs(seg1 - seg0) == 8)
				vht = CHANWIDTH_160MHZ;
			else if (seg1)
				vht = CHANWIDTH_80P80MHZ;
			else
				vht = CHANWIDTH_80MHZ;
			break;
		case 2:
			vht = CHANWIDTH_160MHZ;
			break;
		case 3:
			vht = CHANWIDTH_80P80MHZ;
			break;
		default:
			vht = CHANWIDTH_USE_HT;
			break;
		}
	}

	if (ieee80211_freq_to_channel_ext(freq, sec_chan, vht, op_class,
					  chan) == NUM_HOSTAPD_MODES) {
		wpa_printf(MSG_DEBUG,
			   "Cannot determine operating class and channel");
		return -1;
	}

	*phy_type = ieee80211_get_phy_type(freq, ht_oper != NULL,
					   vht_oper != NULL);
	if (*phy_type == PHY_TYPE_UNSPECIFIED) {
		wpa_printf(MSG_DEBUG, "Cannot determine phy type");
		return -1;
	}

	return 0;
}