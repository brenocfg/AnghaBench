#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_ht_operation {int ht_param; int /*<<< orphan*/  operation_mode; int /*<<< orphan*/  primary_chan; } ;
struct hostapd_data {TYPE_3__* iconf; TYPE_2__* iface; TYPE_1__* conf; } ;
struct TYPE_6__ {int secondary_channel; int /*<<< orphan*/  channel; int /*<<< orphan*/  ieee80211n; } ;
struct TYPE_5__ {int /*<<< orphan*/  ht_op_mode; } ;
struct TYPE_4__ {scalar_t__ disable_11n; } ;

/* Variables and functions */
 int HT_INFO_HT_PARAM_SECONDARY_CHNL_ABOVE ; 
 int HT_INFO_HT_PARAM_SECONDARY_CHNL_BELOW ; 
 int HT_INFO_HT_PARAM_STA_CHNL_WIDTH ; 
 int /*<<< orphan*/  WLAN_EID_HT_OPERATION ; 
 int /*<<< orphan*/  host_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (struct ieee80211_ht_operation*,int /*<<< orphan*/ ,int) ; 

u8 * hostapd_eid_ht_operation(struct hostapd_data *hapd, u8 *eid)
{
	struct ieee80211_ht_operation *oper;
	u8 *pos = eid;

	if (!hapd->iconf->ieee80211n || hapd->conf->disable_11n)
		return eid;

	*pos++ = WLAN_EID_HT_OPERATION;
	*pos++ = sizeof(*oper);

	oper = (struct ieee80211_ht_operation *) pos;
	os_memset(oper, 0, sizeof(*oper));

	oper->primary_chan = hapd->iconf->channel;
	oper->operation_mode = host_to_le16(hapd->iface->ht_op_mode);
	if (hapd->iconf->secondary_channel == 1)
		oper->ht_param |= HT_INFO_HT_PARAM_SECONDARY_CHNL_ABOVE |
			HT_INFO_HT_PARAM_STA_CHNL_WIDTH;
	if (hapd->iconf->secondary_channel == -1)
		oper->ht_param |= HT_INFO_HT_PARAM_SECONDARY_CHNL_BELOW |
			HT_INFO_HT_PARAM_STA_CHNL_WIDTH;

	pos += sizeof(*oper);

	return pos;
}