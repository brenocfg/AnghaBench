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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int num_modes; struct hostapd_hw_modes* modes; } ;
struct wpa_supplicant {TYPE_1__ hw; } ;
struct wpa_ssid {int /*<<< orphan*/  frequency; } ;
struct hostapd_hw_modes {int mode; scalar_t__ vht_capab; } ;
typedef  enum hostapd_hw_mode { ____Placeholder_hostapd_hw_mode } hostapd_hw_mode ;

/* Variables and functions */
 int NUM_HOSTAPD_MODES ; 
 int ieee80211_freq_to_chan (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drv_supports_vht(struct wpa_supplicant *wpa_s,
			    const struct wpa_ssid *ssid)
{
	enum hostapd_hw_mode hw_mode;
	struct hostapd_hw_modes *mode = NULL;
	u8 channel;
	int i;

	hw_mode = ieee80211_freq_to_chan(ssid->frequency, &channel);
	if (hw_mode == NUM_HOSTAPD_MODES)
		return 0;
	for (i = 0; wpa_s->hw.modes && i < wpa_s->hw.num_modes; i++) {
		if (wpa_s->hw.modes[i].mode == hw_mode) {
			mode = &wpa_s->hw.modes[i];
			break;
		}
	}

	if (!mode)
		return 0;

	return mode->vht_capab != 0;
}