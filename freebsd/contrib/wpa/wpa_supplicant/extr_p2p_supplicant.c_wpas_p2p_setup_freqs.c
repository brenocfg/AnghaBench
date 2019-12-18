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
struct wpa_used_freq_data {int freq; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_modes; int /*<<< orphan*/  modes; } ;
struct wpa_supplicant {int drv_flags; TYPE_3__* global; TYPE_2__* conf; TYPE_1__ hw; int /*<<< orphan*/  num_multichan_concurrent; } ;
typedef  enum wpa_driver_if_type { ____Placeholder_wpa_driver_if_type } wpa_driver_if_type ;
struct TYPE_6__ {int /*<<< orphan*/  p2p; } ;
struct TYPE_5__ {int /*<<< orphan*/  num_p2p_pref_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_DRIVER_FLAGS_DFS_OFFLOAD ; 
 int WPA_IF_P2P_CLIENT ; 
 int WPA_IF_P2P_GO ; 
 scalar_t__ ieee80211_is_dfs (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wpa_used_freq_data* os_calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_free (struct wpa_used_freq_data*) ; 
 int p2p_supported_freq (int /*<<< orphan*/ ,unsigned int) ; 
 int p2p_supported_freq_cli (int /*<<< orphan*/ ,int) ; 
 int wpa_drv_get_pref_freq_list (struct wpa_supplicant*,int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ wpas_p2p_disallowed_freq (TYPE_3__*,unsigned int) ; 
 int wpas_p2p_num_unused_channels (struct wpa_supplicant*) ; 
 int wpas_p2p_pick_best_used_freq (struct wpa_supplicant*,struct wpa_used_freq_data*,unsigned int) ; 
 unsigned int wpas_p2p_valid_oper_freqs (struct wpa_supplicant*,struct wpa_used_freq_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpas_p2p_setup_freqs(struct wpa_supplicant *wpa_s, int freq,
				int *force_freq, int *pref_freq, int go,
				unsigned int *pref_freq_list,
				unsigned int *num_pref_freq)
{
	struct wpa_used_freq_data *freqs;
	int res, best_freq, num_unused;
	unsigned int freq_in_use = 0, num, i, max_pref_freq;

	max_pref_freq = *num_pref_freq;
	*num_pref_freq = 0;

	freqs = os_calloc(wpa_s->num_multichan_concurrent,
			  sizeof(struct wpa_used_freq_data));
	if (!freqs)
		return -1;

	num = wpas_p2p_valid_oper_freqs(wpa_s, freqs,
					wpa_s->num_multichan_concurrent);

	/*
	 * It is possible that the total number of used frequencies is bigger
	 * than the number of frequencies used for P2P, so get the system wide
	 * number of unused frequencies.
	 */
	num_unused = wpas_p2p_num_unused_channels(wpa_s);

	wpa_printf(MSG_DEBUG,
		   "P2P: Setup freqs: freq=%d num_MCC=%d shared_freqs=%u num_unused=%d",
		   freq, wpa_s->num_multichan_concurrent, num, num_unused);

	if (freq > 0) {
		int ret;
		if (go)
			ret = p2p_supported_freq(wpa_s->global->p2p, freq);
		else
			ret = p2p_supported_freq_cli(wpa_s->global->p2p, freq);
		if (!ret) {
			if ((wpa_s->drv_flags & WPA_DRIVER_FLAGS_DFS_OFFLOAD) &&
			    ieee80211_is_dfs(freq, wpa_s->hw.modes,
					     wpa_s->hw.num_modes)) {
				/*
				 * If freq is a DFS channel and DFS is offloaded
				 * to the driver, allow P2P GO to use it.
				 */
				wpa_printf(MSG_DEBUG,
					   "P2P: The forced channel for GO (%u MHz) is DFS, and DFS is offloaded to the driver",
					   freq);
			} else {
				wpa_printf(MSG_DEBUG,
					   "P2P: The forced channel (%u MHz) is not supported for P2P uses",
					   freq);
				res = -3;
				goto exit_free;
			}
		}

		for (i = 0; i < num; i++) {
			if (freqs[i].freq == freq)
				freq_in_use = 1;
		}

		if (num_unused <= 0 && !freq_in_use) {
			wpa_printf(MSG_DEBUG, "P2P: Cannot start P2P group on %u MHz as there are no available channels",
				   freq);
			res = -2;
			goto exit_free;
		}
		wpa_printf(MSG_DEBUG, "P2P: Trying to force us to use the "
			   "requested channel (%u MHz)", freq);
		*force_freq = freq;
		goto exit_ok;
	}

	best_freq = wpas_p2p_pick_best_used_freq(wpa_s, freqs, num);

	if (!wpa_s->conf->num_p2p_pref_chan && *pref_freq == 0) {
		enum wpa_driver_if_type iface_type;

		if (go)
			iface_type = WPA_IF_P2P_GO;
		else
			iface_type = WPA_IF_P2P_CLIENT;

		wpa_printf(MSG_DEBUG, "P2P: best_freq=%d, go=%d",
			   best_freq, go);

		res = wpa_drv_get_pref_freq_list(wpa_s, iface_type,
						 &max_pref_freq,
						 pref_freq_list);
		if (!res && max_pref_freq > 0) {
			*num_pref_freq = max_pref_freq;
			i = 0;
			while (i < *num_pref_freq &&
			       (!p2p_supported_freq(wpa_s->global->p2p,
						    pref_freq_list[i]) ||
				wpas_p2p_disallowed_freq(wpa_s->global,
							 pref_freq_list[i]))) {
				wpa_printf(MSG_DEBUG,
					   "P2P: preferred_freq_list[%d]=%d is disallowed",
					   i, pref_freq_list[i]);
				i++;
			}
			if (i != *num_pref_freq) {
				best_freq = pref_freq_list[i];
				wpa_printf(MSG_DEBUG,
					   "P2P: Using preferred_freq_list[%d]=%d",
					   i, best_freq);
			} else {
				wpa_printf(MSG_DEBUG,
					   "P2P: All driver preferred frequencies are disallowed for P2P use");
				*num_pref_freq = 0;
			}
		} else {
			wpa_printf(MSG_DEBUG,
				   "P2P: No preferred frequency list available");
		}
	}

	/* We have a candidate frequency to use */
	if (best_freq > 0) {
		if (*pref_freq == 0 && num_unused > 0) {
			wpa_printf(MSG_DEBUG, "P2P: Try to prefer a frequency (%u MHz) we are already using",
				   best_freq);
			*pref_freq = best_freq;
		} else {
			wpa_printf(MSG_DEBUG, "P2P: Try to force us to use frequency (%u MHz) which is already in use",
				   best_freq);
			*force_freq = best_freq;
		}
	} else if (num_unused > 0) {
		wpa_printf(MSG_DEBUG,
			   "P2P: Current operating channels are not available for P2P. Try to use another channel");
		*force_freq = 0;
	} else {
		wpa_printf(MSG_DEBUG,
			   "P2P: All channels are in use and none of them are P2P enabled. Cannot start P2P group");
		res = -2;
		goto exit_free;
	}

exit_ok:
	res = 0;
exit_free:
	os_free(freqs);
	return res;
}