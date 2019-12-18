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
struct hostapd_iface {TYPE_2__* conf; int /*<<< orphan*/ * bss; TYPE_1__* current_mode; } ;
struct TYPE_4__ {scalar_t__ secondary_channel; int /*<<< orphan*/  channel; } ;
struct TYPE_3__ {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ HOSTAPD_MODE_IEEE80211G ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int hostapd_hw_get_freq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int is_40_allowed(struct hostapd_iface *iface, int channel)
{
	int pri_freq, sec_freq;
	int affected_start, affected_end;
	int pri = 2407 + 5 * channel;

	if (iface->current_mode->mode != HOSTAPD_MODE_IEEE80211G)
		return 1;

	pri_freq = hostapd_hw_get_freq(iface->bss[0], iface->conf->channel);

	if (iface->conf->secondary_channel > 0)
		sec_freq = pri_freq + 20;
	else
		sec_freq = pri_freq - 20;

	affected_start = (pri_freq + sec_freq) / 2 - 25;
	affected_end = (pri_freq + sec_freq) / 2 + 25;
	if ((pri < affected_start || pri > affected_end))
		return 1; /* not within affected channel range */

	wpa_printf(MSG_ERROR, "40 MHz affected channel range: [%d,%d] MHz",
		   affected_start, affected_end);
	wpa_printf(MSG_ERROR, "Neighboring BSS: freq=%d", pri);
	return 0;
}