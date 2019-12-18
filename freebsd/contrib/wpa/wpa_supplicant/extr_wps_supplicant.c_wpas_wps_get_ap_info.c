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
struct wps_ap_info {int /*<<< orphan*/  bssid; } ;
struct wpa_supplicant {size_t num_wps_ap; struct wps_ap_info* wps_ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wps_ap_info * wpas_wps_get_ap_info(struct wpa_supplicant *wpa_s,
						 const u8 *bssid)
{
	size_t i;

	if (wpa_s->wps_ap == NULL)
		return NULL;

	for (i = 0; i < wpa_s->num_wps_ap; i++) {
		struct wps_ap_info *ap = &wpa_s->wps_ap[i];
		if (os_memcmp(ap->bssid, bssid, ETH_ALEN) == 0)
			return ap;
	}

	return NULL;
}