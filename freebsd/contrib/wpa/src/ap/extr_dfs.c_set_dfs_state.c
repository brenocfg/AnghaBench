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
typedef  int /*<<< orphan*/  u32 ;
struct hostapd_iface {struct hostapd_hw_modes* current_mode; } ;
struct hostapd_hw_modes {scalar_t__ mode; } ;

/* Variables and functions */
#define  CHAN_WIDTH_160 132 
#define  CHAN_WIDTH_20 131 
#define  CHAN_WIDTH_20_NOHT 130 
#define  CHAN_WIDTH_40 129 
#define  CHAN_WIDTH_80 128 
 scalar_t__ HOSTAPD_MODE_IEEE80211A ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 scalar_t__ set_dfs_state_freq (struct hostapd_iface*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int set_dfs_state(struct hostapd_iface *iface, int freq, int ht_enabled,
			 int chan_offset, int chan_width, int cf1,
			 int cf2, u32 state)
{
	int n_chans = 1, i;
	struct hostapd_hw_modes *mode;
	int frequency = freq;
	int ret = 0;

	mode = iface->current_mode;
	if (mode == NULL)
		return 0;

	if (mode->mode != HOSTAPD_MODE_IEEE80211A) {
		wpa_printf(MSG_WARNING, "current_mode != IEEE80211A");
		return 0;
	}

	/* Seems cf1 and chan_width is enough here */
	switch (chan_width) {
	case CHAN_WIDTH_20_NOHT:
	case CHAN_WIDTH_20:
		n_chans = 1;
		if (frequency == 0)
			frequency = cf1;
		break;
	case CHAN_WIDTH_40:
		n_chans = 2;
		frequency = cf1 - 10;
		break;
	case CHAN_WIDTH_80:
		n_chans = 4;
		frequency = cf1 - 30;
		break;
	case CHAN_WIDTH_160:
		n_chans = 8;
		frequency = cf1 - 70;
		break;
	default:
		wpa_printf(MSG_INFO, "DFS chan_width %d not supported",
			   chan_width);
		break;
	}

	wpa_printf(MSG_DEBUG, "DFS freq: %dMHz, n_chans: %d", frequency,
		   n_chans);
	for (i = 0; i < n_chans; i++) {
		ret += set_dfs_state_freq(iface, frequency, state);
		frequency = frequency + 20;
	}

	return ret;
}