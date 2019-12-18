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
typedef  int u32 ;
struct wpa_supplicant {int keys_cleared; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  MLME_SETPROTECTION_KEY_TYPE_PAIRWISE ; 
 int /*<<< orphan*/  MLME_SETPROTECTION_PROTECT_TYPE_NONE ; 
 int /*<<< orphan*/  WPA_ALG_NONE ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_drv_mlme_setprotection (struct wpa_supplicant*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_drv_set_key (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void wpa_clear_keys(struct wpa_supplicant *wpa_s, const u8 *addr)
{
	int i, max;

#ifdef CONFIG_IEEE80211W
	max = 6;
#else /* CONFIG_IEEE80211W */
	max = 4;
#endif /* CONFIG_IEEE80211W */

	/* MLME-DELETEKEYS.request */
	for (i = 0; i < max; i++) {
		if (wpa_s->keys_cleared & BIT(i))
			continue;
		wpa_drv_set_key(wpa_s, WPA_ALG_NONE, NULL, i, 0, NULL, 0,
				NULL, 0);
	}
	if (!(wpa_s->keys_cleared & BIT(0)) && addr &&
	    !is_zero_ether_addr(addr)) {
		wpa_drv_set_key(wpa_s, WPA_ALG_NONE, addr, 0, 0, NULL, 0, NULL,
				0);
		/* MLME-SETPROTECTION.request(None) */
		wpa_drv_mlme_setprotection(
			wpa_s, addr,
			MLME_SETPROTECTION_PROTECT_TYPE_NONE,
			MLME_SETPROTECTION_KEY_TYPE_PAIRWISE);
	}
	wpa_s->keys_cleared = (u32) -1;
}