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
struct wpa_supplicant {scalar_t__ wpa_state; int /*<<< orphan*/  wpa; int /*<<< orphan*/  bssid; int /*<<< orphan*/ * current_ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ WPA_4WAY_HANDSHAKE ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wpa_sm_pmf_enabled (int /*<<< orphan*/ ) ; 

int pmf_in_use(struct wpa_supplicant *wpa_s, const u8 *addr)
{
	if (wpa_s->current_ssid == NULL ||
	    wpa_s->wpa_state < WPA_4WAY_HANDSHAKE ||
	    os_memcmp(addr, wpa_s->bssid, ETH_ALEN) != 0)
		return 0;
	return wpa_sm_pmf_enabled(wpa_s->wpa);
}