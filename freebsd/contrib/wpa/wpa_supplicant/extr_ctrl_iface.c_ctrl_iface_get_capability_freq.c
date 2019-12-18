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
struct TYPE_4__ {int num_modes; TYPE_1__* modes; } ;
struct wpa_supplicant {TYPE_2__ hw; } ;
struct hostapd_channel_data {int flag; int /*<<< orphan*/  freq; int /*<<< orphan*/  chan; } ;
struct TYPE_3__ {int mode; int num_channels; struct hostapd_channel_data* channels; } ;

/* Variables and functions */
 int HOSTAPD_CHAN_DISABLED ; 
 int HOSTAPD_CHAN_NO_IR ; 
 int HOSTAPD_CHAN_RADAR ; 
#define  HOSTAPD_MODE_IEEE80211A 131 
#define  HOSTAPD_MODE_IEEE80211AD 130 
#define  HOSTAPD_MODE_IEEE80211B 129 
#define  HOSTAPD_MODE_IEEE80211G 128 
 int os_snprintf (char*,int,char*,...) ; 
 scalar_t__ os_snprintf_error (int,int) ; 

__attribute__((used)) static int ctrl_iface_get_capability_freq(struct wpa_supplicant *wpa_s,
					  char *buf, size_t buflen)
{
	struct hostapd_channel_data *chnl;
	int ret, i, j;
	char *pos, *end, *hmode;

	pos = buf;
	end = pos + buflen;

	for (j = 0; j < wpa_s->hw.num_modes; j++) {
		switch (wpa_s->hw.modes[j].mode) {
		case HOSTAPD_MODE_IEEE80211B:
			hmode = "B";
			break;
		case HOSTAPD_MODE_IEEE80211G:
			hmode = "G";
			break;
		case HOSTAPD_MODE_IEEE80211A:
			hmode = "A";
			break;
		case HOSTAPD_MODE_IEEE80211AD:
			hmode = "AD";
			break;
		default:
			continue;
		}
		ret = os_snprintf(pos, end - pos, "Mode[%s] Channels:\n",
				  hmode);
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
		chnl = wpa_s->hw.modes[j].channels;
		for (i = 0; i < wpa_s->hw.modes[j].num_channels; i++) {
			if (chnl[i].flag & HOSTAPD_CHAN_DISABLED)
				continue;
			ret = os_snprintf(pos, end - pos, " %d = %d MHz%s%s\n",
					  chnl[i].chan, chnl[i].freq,
					  chnl[i].flag & HOSTAPD_CHAN_NO_IR ?
					  " (NO_IR)" : "",
					  chnl[i].flag & HOSTAPD_CHAN_RADAR ?
					  " (DFS)" : "");

			if (os_snprintf_error(end - pos, ret))
				return pos - buf;
			pos += ret;
		}
		ret = os_snprintf(pos, end - pos, "\n");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}

	return pos - buf;
}