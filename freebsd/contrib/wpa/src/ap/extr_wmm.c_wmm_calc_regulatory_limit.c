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
struct hostapd_wmm_ac_params {int dummy; } ;
struct hostapd_hw_modes {int num_channels; struct hostapd_channel_data* channels; } ;
struct hostapd_data {int /*<<< orphan*/  parameter_set_count; TYPE_2__* iface; TYPE_1__* iconf; } ;
struct hostapd_channel_data {scalar_t__ freq; int /*<<< orphan*/  wmm_rules; scalar_t__ wmm_rules_valid; } ;
struct TYPE_4__ {scalar_t__ freq; struct hostapd_wmm_ac_params* prev_wmm; struct hostapd_hw_modes* current_mode; } ;
struct TYPE_3__ {struct hostapd_wmm_ac_params* wmm_ac_params; } ;

/* Variables and functions */
 scalar_t__ os_memcmp (struct hostapd_wmm_ac_params*,struct hostapd_wmm_ac_params*,int) ; 
 int /*<<< orphan*/  os_memcpy (struct hostapd_wmm_ac_params*,struct hostapd_wmm_ac_params*,int) ; 
 int /*<<< orphan*/  wmm_set_regulatory_limit (struct hostapd_wmm_ac_params*,struct hostapd_wmm_ac_params*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wmm_calc_regulatory_limit(struct hostapd_data *hapd,
				      struct hostapd_wmm_ac_params *acp)
{
	struct hostapd_hw_modes *mode = hapd->iface->current_mode;
	int c;

	os_memcpy(acp, hapd->iconf->wmm_ac_params,
		  sizeof(hapd->iconf->wmm_ac_params));

	for (c = 0; mode && c < mode->num_channels; c++) {
		struct hostapd_channel_data *chan = &mode->channels[c];

		if (chan->freq != hapd->iface->freq)
			continue;

		if (chan->wmm_rules_valid)
			wmm_set_regulatory_limit(hapd->iconf->wmm_ac_params,
						 acp, chan->wmm_rules);
		break;
	}

	/*
	 * Check if we need to update set count. Since both were initialized to
	 * zero we can compare the whole array in one shot.
	 */
	if (os_memcmp(acp, hapd->iface->prev_wmm,
		      sizeof(hapd->iconf->wmm_ac_params)) != 0) {
		os_memcpy(hapd->iface->prev_wmm, acp,
			  sizeof(hapd->iconf->wmm_ac_params));
		hapd->parameter_set_count++;
	}
}