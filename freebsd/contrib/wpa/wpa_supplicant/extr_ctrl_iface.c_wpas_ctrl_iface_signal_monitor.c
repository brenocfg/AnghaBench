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
struct wpa_supplicant {scalar_t__ bgscan_priv; scalar_t__ bgscan; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int atoi (char const*) ; 
 char* os_strstr (char const*,char*) ; 
 int wpa_drv_signal_monitor (struct wpa_supplicant*,int,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int wpas_ctrl_iface_signal_monitor(struct wpa_supplicant *wpa_s,
					  const char *cmd)
{
	const char *pos;
	int threshold = 0;
	int hysteresis = 0;

	if (wpa_s->bgscan && wpa_s->bgscan_priv) {
		wpa_printf(MSG_DEBUG,
			   "Reject SIGNAL_MONITOR command - bgscan is active");
		return -1;
	}
	pos = os_strstr(cmd, "THRESHOLD=");
	if (pos)
		threshold = atoi(pos + 10);
	pos = os_strstr(cmd, "HYSTERESIS=");
	if (pos)
		hysteresis = atoi(pos + 11);
	return wpa_drv_signal_monitor(wpa_s, threshold, hysteresis);
}