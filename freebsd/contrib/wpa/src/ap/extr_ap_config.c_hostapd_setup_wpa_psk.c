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
struct hostapd_ssid {int /*<<< orphan*/  wpa_psk_file; TYPE_1__* wpa_psk; int /*<<< orphan*/ * wpa_passphrase; } ;
struct hostapd_bss_config {struct hostapd_ssid ssid; } ;
struct TYPE_2__ {int group; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int hostapd_config_read_wpa_psk (int /*<<< orphan*/ ,struct hostapd_ssid*) ; 
 scalar_t__ hostapd_derive_psk (struct hostapd_ssid*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int hostapd_setup_wpa_psk(struct hostapd_bss_config *conf)
{
	struct hostapd_ssid *ssid = &conf->ssid;

	if (ssid->wpa_passphrase != NULL) {
		if (ssid->wpa_psk != NULL) {
			wpa_printf(MSG_DEBUG, "Using pre-configured WPA PSK "
				   "instead of passphrase");
		} else {
			wpa_printf(MSG_DEBUG, "Deriving WPA PSK based on "
				   "passphrase");
			if (hostapd_derive_psk(ssid) < 0)
				return -1;
		}
		ssid->wpa_psk->group = 1;
	}

	return hostapd_config_read_wpa_psk(ssid->wpa_psk_file, &conf->ssid);
}