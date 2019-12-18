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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {size_t disallow_aps_ssid_count; struct wpa_ssid_value* disallow_aps_ssid; } ;
struct wpa_ssid_value {size_t ssid_len; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,size_t) ; 

int disallowed_ssid(struct wpa_supplicant *wpa_s, const u8 *ssid,
		    size_t ssid_len)
{
	size_t i;

	if (wpa_s->disallow_aps_ssid == NULL || ssid == NULL)
		return 0;

	for (i = 0; i < wpa_s->disallow_aps_ssid_count; i++) {
		struct wpa_ssid_value *s = &wpa_s->disallow_aps_ssid[i];
		if (ssid_len == s->ssid_len &&
		    os_memcmp(ssid, s->ssid, ssid_len) == 0)
			return 1;
	}

	return 0;
}