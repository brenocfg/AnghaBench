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
struct hostapd_iface {scalar_t__ acs_num_completed_scans; scalar_t__ chans_surveyed; TYPE_1__* current_mode; } ;
struct hostapd_channel_data {int flag; scalar_t__ min_nf; int /*<<< orphan*/  survey_list; } ;
struct TYPE_2__ {int num_channels; struct hostapd_channel_data* channels; } ;

/* Variables and functions */
 int HOSTAPD_CHAN_SURVEY_LIST_INITIALIZED ; 
 int /*<<< orphan*/  acs_clean_chan_surveys (struct hostapd_channel_data*) ; 
 int /*<<< orphan*/  dl_list_init (int /*<<< orphan*/ *) ; 

void acs_cleanup(struct hostapd_iface *iface)
{
	int i;
	struct hostapd_channel_data *chan;

	for (i = 0; i < iface->current_mode->num_channels; i++) {
		chan = &iface->current_mode->channels[i];

		if (chan->flag & HOSTAPD_CHAN_SURVEY_LIST_INITIALIZED)
			acs_clean_chan_surveys(chan);

		dl_list_init(&chan->survey_list);
		chan->flag |= HOSTAPD_CHAN_SURVEY_LIST_INITIALIZED;
		chan->min_nf = 0;
	}

	iface->chans_surveyed = 0;
	iface->acs_num_completed_scans = 0;
}