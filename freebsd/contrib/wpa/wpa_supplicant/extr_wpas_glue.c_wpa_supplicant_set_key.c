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
struct wpa_supplicant {size_t last_gtk_len; int last_tk_alg; int last_tk_key_idx; size_t last_tk_len; int /*<<< orphan*/  last_tk; int /*<<< orphan*/  last_tk_addr; int /*<<< orphan*/  last_gtk; scalar_t__ mic_errors_seen; } ;
typedef  enum wpa_alg { ____Placeholder_wpa_alg } wpa_alg ;

/* Variables and functions */
 size_t ETH_ALEN ; 
 int WPA_ALG_NONE ; 
 int WPA_ALG_TKIP ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int wpa_drv_set_key (struct wpa_supplicant*,int,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int wpa_supplicant_set_key(void *_wpa_s, enum wpa_alg alg,
				  const u8 *addr, int key_idx, int set_tx,
				  const u8 *seq, size_t seq_len,
				  const u8 *key, size_t key_len)
{
	struct wpa_supplicant *wpa_s = _wpa_s;
	if (alg == WPA_ALG_TKIP && key_idx == 0 && key_len == 32) {
		/* Clear the MIC error counter when setting a new PTK. */
		wpa_s->mic_errors_seen = 0;
	}
#ifdef CONFIG_TESTING_GET_GTK
	if (key_idx > 0 && addr && is_broadcast_ether_addr(addr) &&
	    alg != WPA_ALG_NONE && key_len <= sizeof(wpa_s->last_gtk)) {
		os_memcpy(wpa_s->last_gtk, key, key_len);
		wpa_s->last_gtk_len = key_len;
	}
#endif /* CONFIG_TESTING_GET_GTK */
#ifdef CONFIG_TESTING_OPTIONS
	if (addr && !is_broadcast_ether_addr(addr)) {
		wpa_s->last_tk_alg = alg;
		os_memcpy(wpa_s->last_tk_addr, addr, ETH_ALEN);
		wpa_s->last_tk_key_idx = key_idx;
		if (key)
			os_memcpy(wpa_s->last_tk, key, key_len);
		wpa_s->last_tk_len = key_len;
	}
#endif /* CONFIG_TESTING_OPTIONS */
	return wpa_drv_set_key(wpa_s, alg, addr, key_idx, set_tx, seq, seq_len,
			       key, key_len);
}