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
struct wpa_driver_scan_ssid {scalar_t__ ssid_len; int /*<<< orphan*/ * ssid; } ;
struct wpa_bss {scalar_t__ freq; scalar_t__ ssid_len; int /*<<< orphan*/  ssid; } ;
struct scan_info {size_t num_freqs; scalar_t__* freqs; size_t num_ssids; struct wpa_driver_scan_ssid* ssids; } ;

/* Variables and functions */
 scalar_t__ os_memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int wpa_bss_included_in_scan(const struct wpa_bss *bss,
				    const struct scan_info *info)
{
	int found;
	size_t i;

	if (info == NULL)
		return 1;

	if (info->num_freqs) {
		found = 0;
		for (i = 0; i < info->num_freqs; i++) {
			if (bss->freq == info->freqs[i]) {
				found = 1;
				break;
			}
		}
		if (!found)
			return 0;
	}

	if (info->num_ssids) {
		found = 0;
		for (i = 0; i < info->num_ssids; i++) {
			const struct wpa_driver_scan_ssid *s = &info->ssids[i];
			if ((s->ssid == NULL || s->ssid_len == 0) ||
			    (s->ssid_len == bss->ssid_len &&
			     os_memcmp(s->ssid, bss->ssid, bss->ssid_len) ==
			     0)) {
				found = 1;
				break;
			}
		}
		if (!found)
			return 0;
	}

	return 1;
}