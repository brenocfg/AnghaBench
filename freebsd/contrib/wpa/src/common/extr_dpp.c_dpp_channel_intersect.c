#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct hostapd_hw_modes {int dummy; } ;
struct dpp_bootstrap_info {unsigned int num_freq; unsigned int* freq; } ;
struct dpp_authentication {unsigned int* freq; unsigned int curr_freq; int /*<<< orphan*/  num_freq; struct dpp_bootstrap_info* peer_bi; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ dpp_channel_ok_init (struct hostapd_hw_modes*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ freq_included (unsigned int*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int dpp_channel_intersect(struct dpp_authentication *auth,
				 struct hostapd_hw_modes *own_modes,
				 u16 num_modes)
{
	struct dpp_bootstrap_info *peer_bi = auth->peer_bi;
	unsigned int i, freq;

	for (i = 0; i < peer_bi->num_freq; i++) {
		freq = peer_bi->freq[i];
		if (freq_included(auth->freq, auth->num_freq, freq))
			continue;
		if (dpp_channel_ok_init(own_modes, num_modes, freq))
			auth->freq[auth->num_freq++] = freq;
	}
	if (!auth->num_freq) {
		wpa_printf(MSG_INFO,
			   "DPP: No available channels for initiating DPP Authentication");
		return -1;
	}
	auth->curr_freq = auth->freq[0];
	return 0;
}