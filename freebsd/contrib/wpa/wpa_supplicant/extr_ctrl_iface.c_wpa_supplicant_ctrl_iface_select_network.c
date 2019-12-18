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
struct wpa_supplicant {int* select_network_scan_freqs; TYPE_1__ scan_min_time; int /*<<< orphan*/  conf; } ;
struct wpa_ssid {int disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int atoi (char*) ; 
 int* freq_range_to_channel_list (struct wpa_supplicant*,char*) ; 
 int /*<<< orphan*/  os_free (int*) ; 
 scalar_t__ os_strncmp (char*,char*,int) ; 
 char* os_strstr (char*,char*) ; 
 struct wpa_ssid* wpa_config_get_network (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_supplicant_select_network (struct wpa_supplicant*,struct wpa_ssid*) ; 

__attribute__((used)) static int wpa_supplicant_ctrl_iface_select_network(
	struct wpa_supplicant *wpa_s, char *cmd)
{
	int id;
	struct wpa_ssid *ssid;
	char *pos;

	/* cmd: "<network id>" or "any" */
	if (os_strncmp(cmd, "any", 3) == 0) {
		wpa_printf(MSG_DEBUG, "CTRL_IFACE: SELECT_NETWORK any");
		ssid = NULL;
	} else {
		id = atoi(cmd);
		wpa_printf(MSG_DEBUG, "CTRL_IFACE: SELECT_NETWORK id=%d", id);

		ssid = wpa_config_get_network(wpa_s->conf, id);
		if (ssid == NULL) {
			wpa_printf(MSG_DEBUG, "CTRL_IFACE: Could not find "
				   "network id=%d", id);
			return -1;
		}
		if (ssid->disabled == 2) {
			wpa_printf(MSG_DEBUG, "CTRL_IFACE: Cannot use "
				   "SELECT_NETWORK with persistent P2P group");
			return -1;
		}
	}

	pos = os_strstr(cmd, " freq=");
	if (pos) {
		int *freqs = freq_range_to_channel_list(wpa_s, pos + 6);
		if (freqs) {
			os_free(wpa_s->select_network_scan_freqs);
			wpa_s->select_network_scan_freqs = freqs;
		}
	}

	wpa_s->scan_min_time.sec = 0;
	wpa_s->scan_min_time.usec = 0;
	wpa_supplicant_select_network(wpa_s, ssid);

	return 0;
}