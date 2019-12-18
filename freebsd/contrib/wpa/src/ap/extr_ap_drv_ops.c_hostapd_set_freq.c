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
struct hostapd_hw_modes {int /*<<< orphan*/ * he_capab; int /*<<< orphan*/  vht_capab; } ;
struct hostapd_freq_params {int dummy; } ;
struct hostapd_data {int /*<<< orphan*/  drv_priv; TYPE_2__* driver; TYPE_1__* iface; } ;
typedef  enum hostapd_hw_mode { ____Placeholder_hostapd_hw_mode } hostapd_hw_mode ;
struct TYPE_4__ {int (* set_freq ) (int /*<<< orphan*/ ,struct hostapd_freq_params*) ;} ;
struct TYPE_3__ {struct hostapd_hw_modes* current_mode; } ;

/* Variables and functions */
 size_t IEEE80211_MODE_AP ; 
 scalar_t__ hostapd_set_freq_params (struct hostapd_freq_params*,int,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,struct hostapd_freq_params*) ; 

int hostapd_set_freq(struct hostapd_data *hapd, enum hostapd_hw_mode mode,
		     int freq, int channel, int ht_enabled, int vht_enabled,
		     int he_enabled,
		     int sec_channel_offset, int oper_chwidth,
		     int center_segment0, int center_segment1)
{
	struct hostapd_freq_params data;
	struct hostapd_hw_modes *cmode = hapd->iface->current_mode;

	if (hostapd_set_freq_params(&data, mode, freq, channel, ht_enabled,
				    vht_enabled, he_enabled, sec_channel_offset,
				    oper_chwidth,
				    center_segment0, center_segment1,
				    cmode ? cmode->vht_capab : 0,
				    cmode ?
				    &cmode->he_capab[IEEE80211_MODE_AP] : NULL))
		return -1;

	if (hapd->driver == NULL)
		return 0;
	if (hapd->driver->set_freq == NULL)
		return 0;
	return hapd->driver->set_freq(hapd->drv_priv, &data);
}