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
typedef  enum hostapd_chan_status { ____Placeholder_hostapd_chan_status } hostapd_chan_status ;
struct TYPE_2__ {scalar_t__ channel; } ;

/* Variables and functions */
#define  HOSTAPD_CHAN_ACS 130 
#define  HOSTAPD_CHAN_INVALID 129 
#define  HOSTAPD_CHAN_VALID 128 
 int acs_init (struct hostapd_iface*) ; 
 scalar_t__ hostapd_is_usable_chans (struct hostapd_iface*) ; 

__attribute__((used)) static enum hostapd_chan_status
hostapd_check_chans(struct hostapd_iface *iface)
{
	if (iface->conf->channel) {
		if (hostapd_is_usable_chans(iface))
			return HOSTAPD_CHAN_VALID;
		else
			return HOSTAPD_CHAN_INVALID;
	}

	/*
	 * The user set channel=0 or channel=acs_survey
	 * which is used to trigger ACS.
	 */

	switch (acs_init(iface)) {
	case HOSTAPD_CHAN_ACS:
		return HOSTAPD_CHAN_ACS;
	case HOSTAPD_CHAN_VALID:
	case HOSTAPD_CHAN_INVALID:
	default:
		return HOSTAPD_CHAN_INVALID;
	}
}