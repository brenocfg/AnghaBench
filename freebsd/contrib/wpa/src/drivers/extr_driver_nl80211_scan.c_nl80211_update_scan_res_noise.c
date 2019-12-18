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
struct wpa_scan_res {int freq; int flags; int /*<<< orphan*/  noise; } ;
struct nl80211_noise_info {unsigned int count; int /*<<< orphan*/ * noise; scalar_t__* freq; } ;

/* Variables and functions */
 int WPA_SCAN_NOISE_INVALID ; 

__attribute__((used)) static void nl80211_update_scan_res_noise(struct wpa_scan_res *res,
					  struct nl80211_noise_info *info)
{
	unsigned int i;

	for (i = 0; res && i < info->count; i++) {
		if ((int) info->freq[i] != res->freq ||
		    !(res->flags & WPA_SCAN_NOISE_INVALID))
			continue;
		res->noise = info->noise[i];
		res->flags &= ~WPA_SCAN_NOISE_INVALID;
	}
}