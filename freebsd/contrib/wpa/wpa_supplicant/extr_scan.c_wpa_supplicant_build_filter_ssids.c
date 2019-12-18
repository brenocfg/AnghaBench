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
struct wpa_ssid {scalar_t__ ssid_len; scalar_t__ ssid; struct wpa_ssid* next; } ;
struct wpa_driver_scan_filter {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; } ;
struct wpa_config {struct wpa_ssid* ssid; int /*<<< orphan*/  filter_ssids; } ;

/* Variables and functions */
 struct wpa_driver_scan_filter* os_calloc (size_t,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct wpa_driver_scan_filter *
wpa_supplicant_build_filter_ssids(struct wpa_config *conf, size_t *num_ssids)
{
	struct wpa_driver_scan_filter *ssids;
	struct wpa_ssid *ssid;
	size_t count;

	*num_ssids = 0;
	if (!conf->filter_ssids)
		return NULL;

	for (count = 0, ssid = conf->ssid; ssid; ssid = ssid->next) {
		if (ssid->ssid && ssid->ssid_len)
			count++;
	}
	if (count == 0)
		return NULL;
	ssids = os_calloc(count, sizeof(struct wpa_driver_scan_filter));
	if (ssids == NULL)
		return NULL;

	for (ssid = conf->ssid; ssid; ssid = ssid->next) {
		if (!ssid->ssid || !ssid->ssid_len)
			continue;
		os_memcpy(ssids[*num_ssids].ssid, ssid->ssid, ssid->ssid_len);
		ssids[*num_ssids].ssid_len = ssid->ssid_len;
		(*num_ssids)++;
	}

	return ssids;
}