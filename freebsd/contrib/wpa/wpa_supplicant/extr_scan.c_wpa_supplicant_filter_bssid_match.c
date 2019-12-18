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
struct wpa_supplicant {size_t bssid_filter_count; int /*<<< orphan*/ * bssid_filter; } ;

/* Variables and functions */
 size_t ETH_ALEN ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

int wpa_supplicant_filter_bssid_match(struct wpa_supplicant *wpa_s,
				      const u8 *bssid)
{
	size_t i;

	if (wpa_s->bssid_filter == NULL)
		return 1;

	for (i = 0; i < wpa_s->bssid_filter_count; i++) {
		if (os_memcmp(wpa_s->bssid_filter + i * ETH_ALEN, bssid,
			      ETH_ALEN) == 0)
			return 1;
	}

	return 0;
}