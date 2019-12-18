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
typedef  size_t u16 ;
struct hostapd_hw_modes {int num_channels; TYPE_1__* channels; } ;
struct dpp_authentication {int num_freq; int* freq; } ;
struct TYPE_2__ {unsigned int freq; int flag; } ;

/* Variables and functions */
 int DPP_BOOTSTRAP_MAX_FREQ ; 
 int HOSTAPD_CHAN_DISABLED ; 
 int HOSTAPD_CHAN_NO_IR ; 
 int HOSTAPD_CHAN_RADAR ; 
 scalar_t__ freq_included (int*,int,unsigned int) ; 

__attribute__((used)) static int dpp_channel_local_list(struct dpp_authentication *auth,
				  struct hostapd_hw_modes *own_modes,
				  u16 num_modes)
{
	u16 m;
	int c, flag;
	unsigned int freq;

	auth->num_freq = 0;

	if (!own_modes || !num_modes) {
		auth->freq[0] = 2412;
		auth->freq[1] = 2437;
		auth->freq[2] = 2462;
		auth->num_freq = 3;
		return 0;
	}

	for (m = 0; m < num_modes; m++) {
		for (c = 0; c < own_modes[m].num_channels; c++) {
			freq = own_modes[m].channels[c].freq;
			flag = own_modes[m].channels[c].flag;
			if (flag & (HOSTAPD_CHAN_DISABLED |
				    HOSTAPD_CHAN_NO_IR |
				    HOSTAPD_CHAN_RADAR))
				continue;
			if (freq_included(auth->freq, auth->num_freq, freq))
				continue;
			auth->freq[auth->num_freq++] = freq;
			if (auth->num_freq == DPP_BOOTSTRAP_MAX_FREQ) {
				m = num_modes;
				break;
			}
		}
	}

	return auth->num_freq == 0 ? -1 : 0;
}