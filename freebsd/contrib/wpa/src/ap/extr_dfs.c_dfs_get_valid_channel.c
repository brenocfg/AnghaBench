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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct hostapd_iface {TYPE_1__* conf; struct hostapd_hw_modes* current_mode; } ;
struct hostapd_hw_modes {scalar_t__ mode; } ;
struct hostapd_channel_data {int dummy; } ;
typedef  int /*<<< orphan*/  _rand ;
struct TYPE_2__ {scalar_t__ secondary_channel; } ;

/* Variables and functions */
 scalar_t__ HOSTAPD_MODE_IEEE80211A ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  dfs_adjust_center_freq (struct hostapd_iface*,struct hostapd_channel_data*,int,scalar_t__*,scalar_t__*) ; 
 int dfs_find_channel (struct hostapd_iface*,struct hostapd_channel_data**,int,int) ; 
 scalar_t__ os_get_random (scalar_t__*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct hostapd_channel_data *
dfs_get_valid_channel(struct hostapd_iface *iface,
		      int *secondary_channel,
		      u8 *oper_centr_freq_seg0_idx,
		      u8 *oper_centr_freq_seg1_idx,
		      int skip_radar)
{
	struct hostapd_hw_modes *mode;
	struct hostapd_channel_data *chan = NULL;
	int num_available_chandefs;
	int chan_idx;
	u32 _rand;

	wpa_printf(MSG_DEBUG, "DFS: Selecting random channel");
	*secondary_channel = 0;
	*oper_centr_freq_seg0_idx = 0;
	*oper_centr_freq_seg1_idx = 0;

	if (iface->current_mode == NULL)
		return NULL;

	mode = iface->current_mode;
	if (mode->mode != HOSTAPD_MODE_IEEE80211A)
		return NULL;

	/* Get the count first */
	num_available_chandefs = dfs_find_channel(iface, NULL, 0, skip_radar);
	if (num_available_chandefs == 0)
		return NULL;

	if (os_get_random((u8 *) &_rand, sizeof(_rand)) < 0)
		return NULL;
	chan_idx = _rand % num_available_chandefs;
	dfs_find_channel(iface, &chan, chan_idx, skip_radar);

	/* dfs_find_channel() calculations assume HT40+ */
	if (iface->conf->secondary_channel)
		*secondary_channel = 1;
	else
		*secondary_channel = 0;

	dfs_adjust_center_freq(iface, chan,
			       *secondary_channel,
			       oper_centr_freq_seg0_idx,
			       oper_centr_freq_seg1_idx);

	return chan;
}