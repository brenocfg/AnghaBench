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
struct TYPE_2__ {scalar_t__ usec; scalar_t__ sec; } ;
struct wpa_supplicant {TYPE_1__ scan_min_time; int /*<<< orphan*/  conf; } ;
struct wpa_ssid {int disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int atoi (char*) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 scalar_t__ os_strstr (char*,char*) ; 
 struct wpa_ssid* wpa_config_get_network (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_supplicant_enable_network (struct wpa_supplicant*,struct wpa_ssid*) ; 

__attribute__((used)) static int wpa_supplicant_ctrl_iface_enable_network(
	struct wpa_supplicant *wpa_s, char *cmd)
{
	int id;
	struct wpa_ssid *ssid;

	/* cmd: "<network id>" or "all" */
	if (os_strcmp(cmd, "all") == 0) {
		wpa_printf(MSG_DEBUG, "CTRL_IFACE: ENABLE_NETWORK all");
		ssid = NULL;
	} else {
		id = atoi(cmd);
		wpa_printf(MSG_DEBUG, "CTRL_IFACE: ENABLE_NETWORK id=%d", id);

		ssid = wpa_config_get_network(wpa_s->conf, id);
		if (ssid == NULL) {
			wpa_printf(MSG_DEBUG, "CTRL_IFACE: Could not find "
				   "network id=%d", id);
			return -1;
		}
		if (ssid->disabled == 2) {
			wpa_printf(MSG_DEBUG, "CTRL_IFACE: Cannot use "
				   "ENABLE_NETWORK with persistent P2P group");
			return -1;
		}

		if (os_strstr(cmd, " no-connect")) {
			ssid->disabled = 0;
			return 0;
		}
	}
	wpa_s->scan_min_time.sec = 0;
	wpa_s->scan_min_time.usec = 0;
	wpa_supplicant_enable_network(wpa_s, ssid);

	return 0;
}