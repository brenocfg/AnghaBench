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
struct wpa_ctrl_dst {int events; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_PROBE_REQUEST ; 
 int WPA_EVENT_RX_PROBE_REQUEST ; 
 scalar_t__ str_starts (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hostapd_ctrl_check_event_enabled(struct wpa_ctrl_dst *dst,
					    const char *buf)
{
	/* Enable Probe Request events based on explicit request.
	 * Other events are enabled by default.
	 */
	if (str_starts(buf, RX_PROBE_REQUEST))
		return !!(dst->events & WPA_EVENT_RX_PROBE_REQUEST);
	return 1;
}