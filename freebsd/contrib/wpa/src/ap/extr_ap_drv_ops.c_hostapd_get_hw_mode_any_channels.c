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
struct hostapd_hw_modes {int num_channels; struct hostapd_channel_data* channels; } ;
struct hostapd_data {TYPE_2__* iface; } ;
struct hostapd_channel_data {int flag; int /*<<< orphan*/  freq; int /*<<< orphan*/  chan; } ;
struct TYPE_4__ {TYPE_1__* conf; } ;
struct TYPE_3__ {scalar_t__ acs_exclude_dfs; int /*<<< orphan*/  acs_ch_list; } ;

/* Variables and functions */
 int HOSTAPD_CHAN_DISABLED ; 
 int HOSTAPD_CHAN_RADAR ; 
 scalar_t__ freq_range_list_includes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_array_add_unique (int**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hostapd_get_hw_mode_any_channels(struct hostapd_data *hapd,
					     struct hostapd_hw_modes *mode,
					     int acs_ch_list_all,
					     int **freq_list)
{
	int i;

	for (i = 0; i < mode->num_channels; i++) {
		struct hostapd_channel_data *chan = &mode->channels[i];

		if ((acs_ch_list_all ||
		     freq_range_list_includes(&hapd->iface->conf->acs_ch_list,
					      chan->chan)) &&
		    !(chan->flag & HOSTAPD_CHAN_DISABLED) &&
		    !(hapd->iface->conf->acs_exclude_dfs &&
		      (chan->flag & HOSTAPD_CHAN_RADAR)))
			int_array_add_unique(freq_list, chan->freq);
	}
}