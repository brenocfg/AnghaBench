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
struct hostapd_iface {scalar_t__ lowest_nf; int /*<<< orphan*/  chans_surveyed; } ;
struct hostapd_channel_data {scalar_t__ min_nf; int /*<<< orphan*/  survey_list; } ;
struct freq_survey {scalar_t__ nf; } ;

/* Variables and functions */
 scalar_t__ dl_list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hostapd_update_nf(struct hostapd_iface *iface,
			      struct hostapd_channel_data *chan,
			      struct freq_survey *survey)
{
	if (!iface->chans_surveyed) {
		chan->min_nf = survey->nf;
		iface->lowest_nf = survey->nf;
	} else {
		if (dl_list_empty(&chan->survey_list))
			chan->min_nf = survey->nf;
		else if (survey->nf < chan->min_nf)
			chan->min_nf = survey->nf;
		if (survey->nf < iface->lowest_nf)
			iface->lowest_nf = survey->nf;
	}
}