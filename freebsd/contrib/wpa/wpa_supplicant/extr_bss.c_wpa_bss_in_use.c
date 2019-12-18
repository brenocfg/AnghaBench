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
struct wpa_supplicant {int /*<<< orphan*/  pending_bssid; int /*<<< orphan*/  bssid; struct wpa_bss* current_bss; } ;
struct wpa_bss {scalar_t__ ssid_len; int /*<<< orphan*/  bssid; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 scalar_t__ ETH_ALEN ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int wpa_bss_in_use(struct wpa_supplicant *wpa_s, struct wpa_bss *bss)
{
	if (bss == wpa_s->current_bss)
		return 1;

	if (wpa_s->current_bss &&
	    (bss->ssid_len != wpa_s->current_bss->ssid_len ||
	     os_memcmp(bss->ssid, wpa_s->current_bss->ssid,
		       bss->ssid_len) != 0))
		return 0; /* SSID has changed */

	return !is_zero_ether_addr(bss->bssid) &&
		(os_memcmp(bss->bssid, wpa_s->bssid, ETH_ALEN) == 0 ||
		 os_memcmp(bss->bssid, wpa_s->pending_bssid, ETH_ALEN) == 0);
}