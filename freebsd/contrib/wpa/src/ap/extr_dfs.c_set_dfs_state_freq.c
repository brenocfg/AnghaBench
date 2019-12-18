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
typedef  int u32 ;
struct hostapd_iface {struct hostapd_hw_modes* current_mode; } ;
struct hostapd_hw_modes {int num_channels; struct hostapd_channel_data* channels; } ;
struct hostapd_channel_data {int freq; int flag; } ;

/* Variables and functions */
 int HOSTAPD_CHAN_DFS_MASK ; 
 int HOSTAPD_CHAN_RADAR ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int set_dfs_state_freq(struct hostapd_iface *iface, int freq, u32 state)
{
	struct hostapd_hw_modes *mode;
	struct hostapd_channel_data *chan = NULL;
	int i;

	mode = iface->current_mode;
	if (mode == NULL)
		return 0;

	wpa_printf(MSG_DEBUG, "set_dfs_state 0x%X for %d MHz", state, freq);
	for (i = 0; i < iface->current_mode->num_channels; i++) {
		chan = &iface->current_mode->channels[i];
		if (chan->freq == freq) {
			if (chan->flag & HOSTAPD_CHAN_RADAR) {
				chan->flag &= ~HOSTAPD_CHAN_DFS_MASK;
				chan->flag |= state;
				return 1; /* Channel found */
			}
		}
	}
	wpa_printf(MSG_WARNING, "Can't set DFS state for freq %d MHz", freq);
	return 0;
}