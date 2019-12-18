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
struct wpa_supplicant {TYPE_1__* global; } ;
struct p2p_go_neg_results {int freq; } ;
struct p2p_channels {int dummy; } ;
typedef  int /*<<< orphan*/  r ;
struct TYPE_2__ {int /*<<< orphan*/  p2p; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ freq_included (struct wpa_supplicant*,struct p2p_channels const*,int) ; 
 scalar_t__ os_get_random (int /*<<< orphan*/ *,int) ; 
 scalar_t__ p2p_supported_freq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpas_p2p_disallowed_freq (TYPE_1__*,int) ; 
 scalar_t__ wpas_p2p_supported_freq_go (struct wpa_supplicant*,struct p2p_channels const*,int) ; 

__attribute__((used)) static void wpas_p2p_select_go_freq_no_pref(struct wpa_supplicant *wpa_s,
					    struct p2p_go_neg_results *params,
					    const struct p2p_channels *channels)
{
	unsigned int i, r;

	/* try all channels in operating class 115 */
	for (i = 0; i < 4; i++) {
		params->freq = 5180 + i * 20;
		if (!wpas_p2p_disallowed_freq(wpa_s->global, params->freq) &&
		    freq_included(wpa_s, channels, params->freq) &&
		    p2p_supported_freq(wpa_s->global->p2p, params->freq))
			goto out;
	}

	/* try all channels in operating class 124 */
	for (i = 0; i < 4; i++) {
		params->freq = 5745 + i * 20;
		if (!wpas_p2p_disallowed_freq(wpa_s->global, params->freq) &&
		    freq_included(wpa_s, channels, params->freq) &&
		    p2p_supported_freq(wpa_s->global->p2p, params->freq))
			goto out;
	}

	/* try social channel class 180 channel 2 */
	params->freq = 58320 + 1 * 2160;
	if (!wpas_p2p_disallowed_freq(wpa_s->global, params->freq) &&
	    freq_included(wpa_s, channels, params->freq) &&
	    p2p_supported_freq(wpa_s->global->p2p, params->freq))
		goto out;

	/* try all channels in reg. class 180 */
	for (i = 0; i < 4; i++) {
		params->freq = 58320 + i * 2160;
		if (!wpas_p2p_disallowed_freq(wpa_s->global, params->freq) &&
		    freq_included(wpa_s, channels, params->freq) &&
		    p2p_supported_freq(wpa_s->global->p2p, params->freq))
			goto out;
	}

	/* try some random selection of the social channels */
	if (os_get_random((u8 *) &r, sizeof(r)) < 0)
		return;

	for (i = 0; i < 3; i++) {
		params->freq = 2412 + ((r + i) % 3) * 25;
		if (wpas_p2p_supported_freq_go(wpa_s, channels, params->freq))
			goto out;
	}

	/* try all other channels in operating class 81 */
	for (i = 0; i < 11; i++) {
		params->freq = 2412 + i * 5;

		/* skip social channels; covered in the previous loop */
		if (params->freq == 2412 ||
		    params->freq == 2437 ||
		    params->freq == 2462)
			continue;

		if (wpas_p2p_supported_freq_go(wpa_s, channels, params->freq))
			goto out;
	}

	params->freq = 0;
	wpa_printf(MSG_DEBUG, "P2P: No 2.4, 5, or 60 GHz channel allowed");
	return;
out:
	wpa_printf(MSG_DEBUG, "P2P: Set GO freq %d MHz (no preference known)",
		   params->freq);
}