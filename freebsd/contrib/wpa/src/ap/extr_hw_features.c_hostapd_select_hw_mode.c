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
struct hostapd_iface {int num_hw_features; int drv_flags; TYPE_1__* conf; int /*<<< orphan*/ * bss; struct hostapd_hw_modes* current_mode; struct hostapd_hw_modes* hw_features; } ;
struct hostapd_hw_modes {scalar_t__ mode; } ;
struct TYPE_2__ {scalar_t__ hw_mode; int channel; scalar_t__ ieee80211ax; scalar_t__ ieee80211ac; scalar_t__ ieee80211n; } ;

/* Variables and functions */
#define  HOSTAPD_CHAN_ACS 130 
#define  HOSTAPD_CHAN_INVALID 129 
#define  HOSTAPD_CHAN_VALID 128 
 int /*<<< orphan*/  HOSTAPD_LEVEL_WARNING ; 
 scalar_t__ HOSTAPD_MODE_IEEE80211B ; 
 scalar_t__ HOSTAPD_MODE_IEEE80211G ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_IEEE80211 ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int WPA_DRIVER_FLAGS_ACS_OFFLOAD ; 
 int WPA_DRIVER_FLAGS_SUPPORT_HW_MODE_ANY ; 
 int hostapd_check_chans (struct hostapd_iface*) ; 
 int /*<<< orphan*/  hostapd_logger (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hostapd_notify_bad_chans (struct hostapd_iface*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int hostapd_select_hw_mode(struct hostapd_iface *iface)
{
	int i;

	if (iface->num_hw_features < 1)
		return -1;

	if ((iface->conf->hw_mode == HOSTAPD_MODE_IEEE80211G ||
	     iface->conf->ieee80211n || iface->conf->ieee80211ac ||
	     iface->conf->ieee80211ax) &&
	    iface->conf->channel == 14) {
		wpa_printf(MSG_INFO, "Disable OFDM/HT/VHT/HE on channel 14");
		iface->conf->hw_mode = HOSTAPD_MODE_IEEE80211B;
		iface->conf->ieee80211n = 0;
		iface->conf->ieee80211ac = 0;
		iface->conf->ieee80211ax = 0;
	}

	iface->current_mode = NULL;
	for (i = 0; i < iface->num_hw_features; i++) {
		struct hostapd_hw_modes *mode = &iface->hw_features[i];
		if (mode->mode == iface->conf->hw_mode) {
			iface->current_mode = mode;
			break;
		}
	}

	if (iface->current_mode == NULL) {
		if (!(iface->drv_flags & WPA_DRIVER_FLAGS_ACS_OFFLOAD) ||
		    !(iface->drv_flags & WPA_DRIVER_FLAGS_SUPPORT_HW_MODE_ANY))
		{
			wpa_printf(MSG_ERROR,
				   "Hardware does not support configured mode");
			hostapd_logger(iface->bss[0], NULL,
				       HOSTAPD_MODULE_IEEE80211,
				       HOSTAPD_LEVEL_WARNING,
				       "Hardware does not support configured mode (%d) (hw_mode in hostapd.conf)",
				       (int) iface->conf->hw_mode);
			return -2;
		}
	}

	switch (hostapd_check_chans(iface)) {
	case HOSTAPD_CHAN_VALID:
		return 0;
	case HOSTAPD_CHAN_ACS: /* ACS will run and later complete */
		return 1;
	case HOSTAPD_CHAN_INVALID:
	default:
		hostapd_notify_bad_chans(iface);
		return -3;
	}
}