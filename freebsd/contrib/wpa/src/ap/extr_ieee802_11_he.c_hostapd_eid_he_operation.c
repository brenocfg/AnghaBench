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
typedef  int u32 ;
struct ieee80211_he_operation {int /*<<< orphan*/  he_oper_params; int /*<<< orphan*/  he_mcs_nss_set; } ;
struct hostapd_data {TYPE_3__* iface; } ;
struct TYPE_6__ {TYPE_2__* conf; int /*<<< orphan*/  current_mode; } ;
struct TYPE_4__ {int he_default_pe_duration; int he_rts_threshold; int he_bss_color; int /*<<< orphan*/  he_basic_mcs_nss_set; scalar_t__ he_twt_required; } ;
struct TYPE_5__ {TYPE_1__ he_op; } ;

/* Variables and functions */
 int HE_OPERATION_BSS_COLOR_OFFSET ; 
 int HE_OPERATION_DFLT_PE_DURATION_OFFSET ; 
 int HE_OPERATION_RTS_THRESHOLD_OFFSET ; 
 int HE_OPERATION_TWT_REQUIRED ; 
 int /*<<< orphan*/  WLAN_EID_EXTENSION ; 
 int /*<<< orphan*/  WLAN_EID_EXT_HE_OPERATION ; 
 int /*<<< orphan*/  host_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_to_le32 (int) ; 
 int /*<<< orphan*/  os_memset (struct ieee80211_he_operation*,int /*<<< orphan*/ ,int) ; 

u8 * hostapd_eid_he_operation(struct hostapd_data *hapd, u8 *eid)
{
	struct ieee80211_he_operation *oper;
	u8 *pos = eid;
	int oper_size = 6;
	u32 params = 0;

	if (!hapd->iface->current_mode)
		return eid;

	*pos++ = WLAN_EID_EXTENSION;
	*pos++ = 1 + oper_size;
	*pos++ = WLAN_EID_EXT_HE_OPERATION;

	oper = (struct ieee80211_he_operation *) pos;
	os_memset(oper, 0, sizeof(*oper));

	if (hapd->iface->conf->he_op.he_default_pe_duration)
		params |= (hapd->iface->conf->he_op.he_default_pe_duration <<
			   HE_OPERATION_DFLT_PE_DURATION_OFFSET);

	if (hapd->iface->conf->he_op.he_twt_required)
		params |= HE_OPERATION_TWT_REQUIRED;

	if (hapd->iface->conf->he_op.he_rts_threshold)
		params |= (hapd->iface->conf->he_op.he_rts_threshold <<
			   HE_OPERATION_RTS_THRESHOLD_OFFSET);

	if (hapd->iface->conf->he_op.he_bss_color)
		params |= (hapd->iface->conf->he_op.he_bss_color <<
			   HE_OPERATION_BSS_COLOR_OFFSET);

	/* HE minimum required basic MCS and NSS for STAs */
	oper->he_mcs_nss_set =
		host_to_le16(hapd->iface->conf->he_op.he_basic_mcs_nss_set);

	/* TODO: conditional MaxBSSID Indicator subfield */

	oper->he_oper_params = host_to_le32(params);

	pos += oper_size;

	return pos;
}