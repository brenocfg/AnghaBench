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
typedef  int u8 ;
struct ieee80211_spatial_reuse {int sr_ctrl; int* params; } ;
struct hostapd_data {TYPE_3__* iface; } ;
struct TYPE_6__ {TYPE_2__* conf; } ;
struct TYPE_4__ {int sr_control; int /*<<< orphan*/  srg_obss_pd_max_offset; int /*<<< orphan*/  srg_obss_pd_min_offset; int /*<<< orphan*/  non_srg_obss_pd_max_offset; } ;
struct TYPE_5__ {TYPE_1__ spr; } ;

/* Variables and functions */
 int SPATIAL_REUSE_NON_SRG_OFFSET_PRESENT ; 
 int SPATIAL_REUSE_SRG_INFORMATION_PRESENT ; 
 int /*<<< orphan*/  WLAN_EID_EXTENSION ; 
 scalar_t__ WLAN_EID_EXT_SPATIAL_REUSE ; 
 int /*<<< orphan*/  os_memset (struct ieee80211_spatial_reuse*,int /*<<< orphan*/ ,int) ; 

u8 * hostapd_eid_spatial_reuse(struct hostapd_data *hapd, u8 *eid)
{
	struct ieee80211_spatial_reuse *spr;
	u8 *pos = eid, *spr_param;
	u8 sz = 1;

	if (!hapd->iface->conf->spr.sr_control)
		return eid;

	if (hapd->iface->conf->spr.sr_control &
	    SPATIAL_REUSE_NON_SRG_OFFSET_PRESENT)
		sz++;

	if (hapd->iface->conf->spr.sr_control &
	    SPATIAL_REUSE_SRG_INFORMATION_PRESENT)
		sz += 18;

	*pos++ = WLAN_EID_EXTENSION;
	*pos++ = 1 + sz;
	*pos++ = WLAN_EID_EXT_SPATIAL_REUSE;

	spr = (struct ieee80211_spatial_reuse *) pos;
	os_memset(spr, 0, sizeof(*spr));

	spr->sr_ctrl = hapd->iface->conf->spr.sr_control;
	pos++;
	spr_param = spr->params;
	if (spr->sr_ctrl & SPATIAL_REUSE_NON_SRG_OFFSET_PRESENT) {
		*spr_param++ =
			hapd->iface->conf->spr.non_srg_obss_pd_max_offset;
		pos++;
	}
	if (spr->sr_ctrl & SPATIAL_REUSE_SRG_INFORMATION_PRESENT) {
		*spr_param++ = hapd->iface->conf->spr.srg_obss_pd_min_offset;
		*spr_param++ = hapd->iface->conf->spr.srg_obss_pd_max_offset;
		pos += 18;
	}

	return pos;
}