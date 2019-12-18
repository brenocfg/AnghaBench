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
typedef  int u32 ;
typedef  void* u16 ;
struct ieee80211_vht_capabilities {int dummy; } ;
struct ieee80211_ht_capabilities {int dummy; } ;
struct ieee80211_he_capabilities {int dummy; } ;
struct hostapd_sta_add_params {void* const* addr; void* const* supp_rates; size_t supp_rates_len; size_t he_capab_len; int vht_opmode_enabled; int support_p2p_ps; int set; void* qosinfo; int /*<<< orphan*/  flags; void* vht_opmode; struct ieee80211_he_capabilities const* he_capab; struct ieee80211_vht_capabilities const* vht_capabilities; struct ieee80211_ht_capabilities const* ht_capabilities; void* listen_interval; void* capability; void* aid; } ;
struct hostapd_data {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
typedef  int /*<<< orphan*/  params ;
struct TYPE_2__ {int (* sta_add ) (int /*<<< orphan*/ ,struct hostapd_sta_add_params*) ;} ;

/* Variables and functions */
 int WLAN_STA_VHT_OPMODE_ENABLED ; 
 int /*<<< orphan*/  hostapd_sta_flags_to_drv (int) ; 
 int /*<<< orphan*/  os_memset (struct hostapd_sta_add_params*,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ,struct hostapd_sta_add_params*) ; 

int hostapd_sta_add(struct hostapd_data *hapd,
		    const u8 *addr, u16 aid, u16 capability,
		    const u8 *supp_rates, size_t supp_rates_len,
		    u16 listen_interval,
		    const struct ieee80211_ht_capabilities *ht_capab,
		    const struct ieee80211_vht_capabilities *vht_capab,
		    const struct ieee80211_he_capabilities *he_capab,
		    size_t he_capab_len,
		    u32 flags, u8 qosinfo, u8 vht_opmode, int supp_p2p_ps,
		    int set)
{
	struct hostapd_sta_add_params params;

	if (hapd->driver == NULL)
		return 0;
	if (hapd->driver->sta_add == NULL)
		return 0;

	os_memset(&params, 0, sizeof(params));
	params.addr = addr;
	params.aid = aid;
	params.capability = capability;
	params.supp_rates = supp_rates;
	params.supp_rates_len = supp_rates_len;
	params.listen_interval = listen_interval;
	params.ht_capabilities = ht_capab;
	params.vht_capabilities = vht_capab;
	params.he_capab = he_capab;
	params.he_capab_len = he_capab_len;
	params.vht_opmode_enabled = !!(flags & WLAN_STA_VHT_OPMODE_ENABLED);
	params.vht_opmode = vht_opmode;
	params.flags = hostapd_sta_flags_to_drv(flags);
	params.qosinfo = qosinfo;
	params.support_p2p_ps = supp_p2p_ps;
	params.set = set;
	return hapd->driver->sta_add(hapd->drv_priv, &params);
}