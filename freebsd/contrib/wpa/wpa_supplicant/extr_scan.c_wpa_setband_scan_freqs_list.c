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
struct TYPE_3__ {int /*<<< orphan*/  num_modes; int /*<<< orphan*/  modes; } ;
struct wpa_supplicant {TYPE_1__ hw; } ;
struct wpa_driver_scan_params {int /*<<< orphan*/ * freqs; } ;
struct hostapd_hw_modes {int num_channels; TYPE_2__* channels; } ;
typedef  enum hostapd_hw_mode { ____Placeholder_hostapd_hw_mode } hostapd_hw_mode ;
struct TYPE_4__ {int flag; int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int HOSTAPD_CHAN_DISABLED ; 
 struct hostapd_hw_modes* get_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * os_calloc (int,int) ; 
 int /*<<< orphan*/ * os_zalloc (int) ; 

__attribute__((used)) static void wpa_setband_scan_freqs_list(struct wpa_supplicant *wpa_s,
					enum hostapd_hw_mode band,
					struct wpa_driver_scan_params *params)
{
	/* Include only supported channels for the specified band */
	struct hostapd_hw_modes *mode;
	int count, i;

	mode = get_mode(wpa_s->hw.modes, wpa_s->hw.num_modes, band);
	if (mode == NULL) {
		/* No channels supported in this band - use empty list */
		params->freqs = os_zalloc(sizeof(int));
		return;
	}

	params->freqs = os_calloc(mode->num_channels + 1, sizeof(int));
	if (params->freqs == NULL)
		return;
	for (count = 0, i = 0; i < mode->num_channels; i++) {
		if (mode->channels[i].flag & HOSTAPD_CHAN_DISABLED)
			continue;
		params->freqs[count++] = mode->channels[i].freq;
	}
}