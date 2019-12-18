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
typedef  int u8 ;
struct wpa_supplicant {int /*<<< orphan*/  global; } ;
struct hostapd_hw_modes {int dummy; } ;
typedef  enum chan_allowed { ____Placeholder_chan_allowed } chan_allowed ;

/* Variables and functions */
 int ALLOWED ; 
 int HOSTAPD_CHAN_VHT_10_70 ; 
 int HOSTAPD_CHAN_VHT_30_50 ; 
 int HOSTAPD_CHAN_VHT_50_30 ; 
 int HOSTAPD_CHAN_VHT_70_10 ; 
 int NOT_ALLOWED ; 
 int NO_IR ; 
 int has_channel (int /*<<< orphan*/ ,struct hostapd_hw_modes*,int,int*) ; 
 int wpas_p2p_get_center_80mhz (struct wpa_supplicant*,struct hostapd_hw_modes*,int) ; 

__attribute__((used)) static enum chan_allowed wpas_p2p_verify_80mhz(struct wpa_supplicant *wpa_s,
					       struct hostapd_hw_modes *mode,
					       u8 channel, u8 bw)
{
	u8 center_chan;
	int i, flags;
	enum chan_allowed res, ret = ALLOWED;

	center_chan = wpas_p2p_get_center_80mhz(wpa_s, mode, channel);
	if (!center_chan)
		return NOT_ALLOWED;
	if (center_chan >= 58 && center_chan <= 138)
		return NOT_ALLOWED; /* Do not allow DFS channels for P2P */

	/* check all the channels are available */
	for (i = 0; i < 4; i++) {
		int adj_chan = center_chan - 6 + i * 4;

		res = has_channel(wpa_s->global, mode, adj_chan, &flags);
		if (res == NOT_ALLOWED)
			return NOT_ALLOWED;
		if (res == NO_IR)
			ret = NO_IR;

		if (i == 0 && !(flags & HOSTAPD_CHAN_VHT_10_70))
			return NOT_ALLOWED;
		if (i == 1 && !(flags & HOSTAPD_CHAN_VHT_30_50))
			return NOT_ALLOWED;
		if (i == 2 && !(flags & HOSTAPD_CHAN_VHT_50_30))
			return NOT_ALLOWED;
		if (i == 3 && !(flags & HOSTAPD_CHAN_VHT_70_10))
			return NOT_ALLOWED;
	}

	return ret;
}