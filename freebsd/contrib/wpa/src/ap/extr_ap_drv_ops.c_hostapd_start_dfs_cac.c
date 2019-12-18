#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hostapd_iface {int cac_started; int /*<<< orphan*/  dfs_cac_start; TYPE_1__* conf; struct hostapd_hw_modes* current_mode; struct hostapd_data** bss; } ;
struct hostapd_hw_modes {int /*<<< orphan*/ * he_capab; int /*<<< orphan*/  vht_capab; } ;
struct hostapd_freq_params {int dummy; } ;
struct hostapd_data {int /*<<< orphan*/  drv_priv; TYPE_2__* driver; } ;
typedef  enum hostapd_hw_mode { ____Placeholder_hostapd_hw_mode } hostapd_hw_mode ;
struct TYPE_4__ {int (* start_dfs_cac ) (int /*<<< orphan*/ ,struct hostapd_freq_params*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  ieee80211h; } ;

/* Variables and functions */
 size_t IEEE80211_MODE_AP ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ hostapd_set_freq_params (struct hostapd_freq_params*,int,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_get_reltime (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,struct hostapd_freq_params*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int hostapd_start_dfs_cac(struct hostapd_iface *iface,
			  enum hostapd_hw_mode mode, int freq,
			  int channel, int ht_enabled, int vht_enabled,
			  int he_enabled,
			  int sec_channel_offset, int oper_chwidth,
			  int center_segment0, int center_segment1)
{
	struct hostapd_data *hapd = iface->bss[0];
	struct hostapd_freq_params data;
	int res;
	struct hostapd_hw_modes *cmode = iface->current_mode;

	if (!hapd->driver || !hapd->driver->start_dfs_cac || !cmode)
		return 0;

	if (!iface->conf->ieee80211h) {
		wpa_printf(MSG_ERROR, "Can't start DFS CAC, DFS functionality "
			   "is not enabled");
		return -1;
	}

	if (hostapd_set_freq_params(&data, mode, freq, channel, ht_enabled,
				    vht_enabled, he_enabled, sec_channel_offset,
				    oper_chwidth, center_segment0,
				    center_segment1,
				    cmode->vht_capab,
				    &cmode->he_capab[IEEE80211_MODE_AP])) {
		wpa_printf(MSG_ERROR, "Can't set freq params");
		return -1;
	}

	res = hapd->driver->start_dfs_cac(hapd->drv_priv, &data);
	if (!res) {
		iface->cac_started = 1;
		os_get_reltime(&iface->dfs_cac_start);
	}

	return res;
}