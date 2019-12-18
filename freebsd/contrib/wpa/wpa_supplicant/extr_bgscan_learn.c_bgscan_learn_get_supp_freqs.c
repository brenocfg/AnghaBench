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
struct TYPE_3__ {int num_modes; struct hostapd_hw_modes* modes; } ;
struct wpa_supplicant {TYPE_1__ hw; } ;
struct hostapd_hw_modes {int num_channels; TYPE_2__* channels; } ;
struct TYPE_4__ {int flag; int freq; } ;

/* Variables and functions */
 int HOSTAPD_CHAN_DISABLED ; 
 scalar_t__ in_array (int*,int) ; 
 int* os_realloc_array (int*,size_t,int) ; 

__attribute__((used)) static int * bgscan_learn_get_supp_freqs(struct wpa_supplicant *wpa_s)
{
	struct hostapd_hw_modes *modes;
	int i, j, *freqs = NULL, *n;
	size_t count = 0;

	modes = wpa_s->hw.modes;
	if (modes == NULL)
		return NULL;

	for (i = 0; i < wpa_s->hw.num_modes; i++) {
		for (j = 0; j < modes[i].num_channels; j++) {
			if (modes[i].channels[j].flag & HOSTAPD_CHAN_DISABLED)
				continue;
			/* some hw modes (e.g. 11b & 11g) contain same freqs */
			if (in_array(freqs, modes[i].channels[j].freq))
				continue;
			n = os_realloc_array(freqs, count + 2, sizeof(int));
			if (n == NULL)
				continue;

			freqs = n;
			freqs[count] = modes[i].channels[j].freq;
			count++;
			freqs[count] = 0;
		}
	}

	return freqs;
}