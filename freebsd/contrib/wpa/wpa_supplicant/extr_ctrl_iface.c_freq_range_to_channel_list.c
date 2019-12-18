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
typedef  size_t u16 ;
struct TYPE_3__ {size_t num_modes; struct hostapd_hw_modes* modes; } ;
struct wpa_supplicant {TYPE_1__ hw; } ;
struct wpa_freq_range_list {int /*<<< orphan*/  range; } ;
struct hostapd_hw_modes {int num_channels; TYPE_2__* channels; } ;
typedef  int /*<<< orphan*/  ranges ;
struct TYPE_4__ {int flag; unsigned int freq; } ;

/* Variables and functions */
 int HOSTAPD_CHAN_DISABLED ; 
 int /*<<< orphan*/  freq_range_list_includes (struct wpa_freq_range_list*,unsigned int) ; 
 scalar_t__ freq_range_list_parse (struct wpa_freq_range_list*,char*) ; 
 int /*<<< orphan*/  int_array_add_unique (int**,unsigned int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (struct wpa_freq_range_list*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int * freq_range_to_channel_list(struct wpa_supplicant *wpa_s, char *val)
{
	struct wpa_freq_range_list ranges;
	int *freqs = NULL;
	struct hostapd_hw_modes *mode;
	u16 i;

	if (wpa_s->hw.modes == NULL)
		return NULL;

	os_memset(&ranges, 0, sizeof(ranges));
	if (freq_range_list_parse(&ranges, val) < 0)
		return NULL;

	for (i = 0; i < wpa_s->hw.num_modes; i++) {
		int j;

		mode = &wpa_s->hw.modes[i];
		for (j = 0; j < mode->num_channels; j++) {
			unsigned int freq;

			if (mode->channels[j].flag & HOSTAPD_CHAN_DISABLED)
				continue;

			freq = mode->channels[j].freq;
			if (!freq_range_list_includes(&ranges, freq))
				continue;

			int_array_add_unique(&freqs, freq);
		}
	}

	os_free(ranges.range);
	return freqs;
}