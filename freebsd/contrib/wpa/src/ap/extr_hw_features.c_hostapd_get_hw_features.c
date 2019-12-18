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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct hostapd_iface {int hw_flags; int num_hw_features; int drv_flags; struct hostapd_hw_modes* hw_features; int /*<<< orphan*/  dfs_domain; struct hostapd_data** bss; } ;
struct hostapd_hw_modes {int num_channels; TYPE_2__* channels; int /*<<< orphan*/  mode; } ;
struct hostapd_data {TYPE_1__* iconf; } ;
struct TYPE_4__ {int flag; int /*<<< orphan*/  max_tx_power; int /*<<< orphan*/  freq; int /*<<< orphan*/  chan; } ;
struct TYPE_3__ {scalar_t__ ieee80211h; } ;

/* Variables and functions */
 int HOSTAPD_CHAN_DISABLED ; 
 int HOSTAPD_CHAN_NO_IR ; 
 int HOSTAPD_CHAN_RADAR ; 
 int /*<<< orphan*/  HOSTAPD_LEVEL_DEBUG ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_IEEE80211 ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int WPA_DRIVER_FLAGS_DFS_OFFLOAD ; 
 int WPA_DRIVER_FLAGS_RADAR ; 
 char* dfs_info (TYPE_2__*) ; 
 scalar_t__ hostapd_drv_none (struct hostapd_data*) ; 
 int /*<<< orphan*/  hostapd_free_hw_features (struct hostapd_hw_modes*,int) ; 
 struct hostapd_hw_modes* hostapd_get_hw_feature_data (struct hostapd_data*,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostapd_logger (struct hostapd_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int hostapd_get_hw_features(struct hostapd_iface *iface)
{
	struct hostapd_data *hapd = iface->bss[0];
	int i, j;
	u16 num_modes, flags;
	struct hostapd_hw_modes *modes;
	u8 dfs_domain;

	if (hostapd_drv_none(hapd))
		return -1;
	modes = hostapd_get_hw_feature_data(hapd, &num_modes, &flags,
					    &dfs_domain);
	if (modes == NULL) {
		hostapd_logger(hapd, NULL, HOSTAPD_MODULE_IEEE80211,
			       HOSTAPD_LEVEL_DEBUG,
			       "Fetching hardware channel/rate support not "
			       "supported.");
		return -1;
	}

	iface->hw_flags = flags;
	iface->dfs_domain = dfs_domain;

	hostapd_free_hw_features(iface->hw_features, iface->num_hw_features);
	iface->hw_features = modes;
	iface->num_hw_features = num_modes;

	for (i = 0; i < num_modes; i++) {
		struct hostapd_hw_modes *feature = &modes[i];
		int dfs_enabled = hapd->iconf->ieee80211h &&
			(iface->drv_flags & WPA_DRIVER_FLAGS_RADAR);

		/* set flag for channels we can use in current regulatory
		 * domain */
		for (j = 0; j < feature->num_channels; j++) {
			int dfs = 0;

			/*
			 * Disable all channels that are marked not to allow
			 * to initiate radiation (a.k.a. passive scan and no
			 * IBSS).
			 * Use radar channels only if the driver supports DFS.
			 */
			if ((feature->channels[j].flag &
			     HOSTAPD_CHAN_RADAR) && dfs_enabled) {
				dfs = 1;
			} else if (((feature->channels[j].flag &
				     HOSTAPD_CHAN_RADAR) &&
				    !(iface->drv_flags &
				      WPA_DRIVER_FLAGS_DFS_OFFLOAD)) ||
				   (feature->channels[j].flag &
				    HOSTAPD_CHAN_NO_IR)) {
				feature->channels[j].flag |=
					HOSTAPD_CHAN_DISABLED;
			}

			if (feature->channels[j].flag & HOSTAPD_CHAN_DISABLED)
				continue;

			wpa_printf(MSG_MSGDUMP, "Allowed channel: mode=%d "
				   "chan=%d freq=%d MHz max_tx_power=%d dBm%s",
				   feature->mode,
				   feature->channels[j].chan,
				   feature->channels[j].freq,
				   feature->channels[j].max_tx_power,
				   dfs ? dfs_info(&feature->channels[j]) : "");
		}
	}

	return 0;
}