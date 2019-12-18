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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_scan_res {int /*<<< orphan*/  ie_len; } ;
struct ieee802_11_elems {scalar_t__ ht_operation; } ;
struct ieee80211_ht_operation {int primary_chan; int ht_param; } ;

/* Variables and functions */
 int HT_INFO_HT_PARAM_SECONDARY_CHNL_ABOVE ; 
 int HT_INFO_HT_PARAM_SECONDARY_CHNL_BELOW ; 
 int HT_INFO_HT_PARAM_SECONDARY_CHNL_OFF_MASK ; 
 int HT_INFO_HT_PARAM_STA_CHNL_WIDTH ; 
 int /*<<< orphan*/  ieee802_11_parse_elems (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ieee802_11_elems*,int /*<<< orphan*/ ) ; 

void get_pri_sec_chan(struct wpa_scan_res *bss, int *pri_chan, int *sec_chan)
{
	struct ieee80211_ht_operation *oper;
	struct ieee802_11_elems elems;

	*pri_chan = *sec_chan = 0;

	ieee802_11_parse_elems((u8 *) (bss + 1), bss->ie_len, &elems, 0);
	if (elems.ht_operation) {
		oper = (struct ieee80211_ht_operation *) elems.ht_operation;
		*pri_chan = oper->primary_chan;
		if (oper->ht_param & HT_INFO_HT_PARAM_STA_CHNL_WIDTH) {
			int sec = oper->ht_param &
				HT_INFO_HT_PARAM_SECONDARY_CHNL_OFF_MASK;
			if (sec == HT_INFO_HT_PARAM_SECONDARY_CHNL_ABOVE)
				*sec_chan = *pri_chan + 4;
			else if (sec == HT_INFO_HT_PARAM_SECONDARY_CHNL_BELOW)
				*sec_chan = *pri_chan - 4;
		}
	}
}