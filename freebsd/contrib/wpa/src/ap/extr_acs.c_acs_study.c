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
struct hostapd_iface {TYPE_1__* conf; } ;
struct hostapd_channel_data {int /*<<< orphan*/  chan; } ;
struct TYPE_2__ {scalar_t__ ieee80211ax; scalar_t__ ieee80211ac; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 scalar_t__ HOSTAPD_CHAN_VALID ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  acs_adjust_center_freq (struct hostapd_iface*) ; 
 int /*<<< orphan*/  acs_cleanup (struct hostapd_iface*) ; 
 int /*<<< orphan*/  acs_fail (struct hostapd_iface*) ; 
 struct hostapd_channel_data* acs_find_ideal_chan (struct hostapd_iface*) ; 
 int acs_study_options (struct hostapd_iface*) ; 
 scalar_t__ hostapd_acs_completed (struct hostapd_iface*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void acs_study(struct hostapd_iface *iface)
{
	struct hostapd_channel_data *ideal_chan;
	int err;

	err = acs_study_options(iface);
	if (err < 0) {
		wpa_printf(MSG_ERROR, "ACS: All study options have failed");
		goto fail;
	}

	ideal_chan = acs_find_ideal_chan(iface);
	if (!ideal_chan) {
		wpa_printf(MSG_ERROR, "ACS: Failed to compute ideal channel");
		err = -1;
		goto fail;
	}

	iface->conf->channel = ideal_chan->chan;

	if (iface->conf->ieee80211ac || iface->conf->ieee80211ax)
		acs_adjust_center_freq(iface);

	err = 0;
fail:
	/*
	 * hostapd_setup_interface_complete() will return -1 on failure,
	 * 0 on success and 0 is HOSTAPD_CHAN_VALID :)
	 */
	if (hostapd_acs_completed(iface, err) == HOSTAPD_CHAN_VALID) {
		acs_cleanup(iface);
		return;
	}

	/* This can possibly happen if channel parameters (secondary
	 * channel, center frequencies) are misconfigured */
	wpa_printf(MSG_ERROR, "ACS: Possibly channel configuration is invalid, please report this along with your config file.");
	acs_fail(iface);
}