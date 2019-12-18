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
struct wpa_driver_ndis_data {scalar_t__ mode; int /*<<< orphan*/  ctx; int /*<<< orphan*/  bssid; scalar_t__ wired; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  EVENT_ASSOC ; 
 int /*<<< orphan*/  EVENT_DISASSOC ; 
 scalar_t__ IEEE80211_MODE_IBSS ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int /*<<< orphan*/ ,void (*) (void*,void*),struct wpa_driver_ndis_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_driver_ndis_get_associnfo (struct wpa_driver_ndis_data*) ; 
 scalar_t__ wpa_driver_ndis_get_bssid (struct wpa_driver_ndis_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wpa_driver_ndis_poll_timeout(void *eloop_ctx, void *timeout_ctx)
{
	struct wpa_driver_ndis_data *drv = eloop_ctx;
	u8 bssid[ETH_ALEN];
	int poll;

	if (drv->wired)
		return;

	if (wpa_driver_ndis_get_bssid(drv, bssid)) {
		/* Disconnected */
		if (!is_zero_ether_addr(drv->bssid)) {
			os_memset(drv->bssid, 0, ETH_ALEN);
			wpa_supplicant_event(drv->ctx, EVENT_DISASSOC, NULL);
		}
	} else {
		/* Connected */
		if (os_memcmp(drv->bssid, bssid, ETH_ALEN) != 0) {
			os_memcpy(drv->bssid, bssid, ETH_ALEN);
			wpa_driver_ndis_get_associnfo(drv);
			wpa_supplicant_event(drv->ctx, EVENT_ASSOC, NULL);
		}
	}

	/* When using integrated NDIS event receiver, we can skip BSSID
	 * polling when using infrastructure network. However, when using
	 * IBSS mode, many driver do not seem to generate connection event,
	 * so we need to enable BSSID polling to figure out when IBSS network
	 * has been formed.
	 */
	poll = drv->mode == IEEE80211_MODE_IBSS;
#ifndef CONFIG_NDIS_EVENTS_INTEGRATED
#ifndef _WIN32_WCE
	poll = 1;
#endif /* _WIN32_WCE */
#endif /* CONFIG_NDIS_EVENTS_INTEGRATED */

	if (poll) {
		eloop_register_timeout(1, 0, wpa_driver_ndis_poll_timeout,
					drv, NULL);
	}
}