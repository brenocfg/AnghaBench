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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int dummy; } ;
struct wpa_driver_scan_params {unsigned int num_ssids; TYPE_1__* ssids; } ;
struct TYPE_2__ {size_t ssid_len; int /*<<< orphan*/  const* ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_ssid_txt (int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static void wpa_add_scan_ssid(struct wpa_supplicant *wpa_s,
			      struct wpa_driver_scan_params *params,
			      size_t max_ssids, const u8 *ssid, size_t ssid_len)
{
	unsigned int j;

	for (j = 0; j < params->num_ssids; j++) {
		if (params->ssids[j].ssid_len == ssid_len &&
		    params->ssids[j].ssid &&
		    os_memcmp(params->ssids[j].ssid, ssid, ssid_len) == 0)
			return; /* already in the list */
	}

	if (params->num_ssids + 1 > max_ssids) {
		wpa_printf(MSG_DEBUG, "Over max scan SSIDs for manual request");
		return;
	}

	wpa_printf(MSG_DEBUG, "Scan SSID (manual request): %s",
		   wpa_ssid_txt(ssid, ssid_len));

	params->ssids[params->num_ssids].ssid = ssid;
	params->ssids[params->num_ssids].ssid_len = ssid_len;
	params->num_ssids++;
}