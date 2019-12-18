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
struct hostapd_iface {int /*<<< orphan*/ * bss; TYPE_2__* current_mode; TYPE_1__* conf; } ;
struct TYPE_4__ {int /*<<< orphan*/  mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTAPD_LEVEL_WARNING ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_IEEE80211 ; 
 int /*<<< orphan*/  hostapd_hw_mode_txt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_logger (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void hostapd_notify_bad_chans(struct hostapd_iface *iface)
{
	if (!iface->current_mode) {
		hostapd_logger(iface->bss[0], NULL, HOSTAPD_MODULE_IEEE80211,
			       HOSTAPD_LEVEL_WARNING,
			       "Hardware does not support configured mode");
		return;
	}
	hostapd_logger(iface->bss[0], NULL,
		       HOSTAPD_MODULE_IEEE80211,
		       HOSTAPD_LEVEL_WARNING,
		       "Configured channel (%d) not found from the "
		       "channel list of current mode (%d) %s",
		       iface->conf->channel,
		       iface->current_mode->mode,
		       hostapd_hw_mode_txt(iface->current_mode->mode));
	hostapd_logger(iface->bss[0], NULL, HOSTAPD_MODULE_IEEE80211,
		       HOSTAPD_LEVEL_WARNING,
		       "Hardware does not support configured channel");
}