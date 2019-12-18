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
struct hostapd_iface {int drv_flags; TYPE_1__** bss; int /*<<< orphan*/  current_mode; } ;
typedef  enum hostapd_chan_status { ____Placeholder_hostapd_chan_status } hostapd_chan_status ;
struct TYPE_2__ {int /*<<< orphan*/  msg_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACS_EVENT_STARTED ; 
 int /*<<< orphan*/  HAPD_IFACE_ACS ; 
 int HOSTAPD_CHAN_ACS ; 
 int HOSTAPD_CHAN_INVALID ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int WPA_DRIVER_FLAGS_ACS_OFFLOAD ; 
 int /*<<< orphan*/  acs_cleanup (struct hostapd_iface*) ; 
 scalar_t__ acs_request_scan (struct hostapd_iface*) ; 
 scalar_t__ hostapd_drv_do_acs (TYPE_1__*) ; 
 int /*<<< orphan*/  hostapd_set_state (struct hostapd_iface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

enum hostapd_chan_status acs_init(struct hostapd_iface *iface)
{
	wpa_printf(MSG_INFO, "ACS: Automatic channel selection started, this may take a bit");

	if (iface->drv_flags & WPA_DRIVER_FLAGS_ACS_OFFLOAD) {
		wpa_printf(MSG_INFO, "ACS: Offloading to driver");
		if (hostapd_drv_do_acs(iface->bss[0]))
			return HOSTAPD_CHAN_INVALID;
		return HOSTAPD_CHAN_ACS;
	}

	if (!iface->current_mode)
		return HOSTAPD_CHAN_INVALID;

	acs_cleanup(iface);

	if (acs_request_scan(iface) < 0)
		return HOSTAPD_CHAN_INVALID;

	hostapd_set_state(iface, HAPD_IFACE_ACS);
	wpa_msg(iface->bss[0]->msg_ctx, MSG_INFO, ACS_EVENT_STARTED);

	return HOSTAPD_CHAN_ACS;
}