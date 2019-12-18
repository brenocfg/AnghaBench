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
struct wpa_supplicant {int /*<<< orphan*/  bss_tmp_disallowed; } ;
struct wpa_bss_tmp_disallowed {int rssi_threshold; int /*<<< orphan*/  list; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  dl_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,struct wpa_bss_tmp_disallowed*) ; 
 int /*<<< orphan*/  eloop_register_timeout (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_supplicant*,struct wpa_bss_tmp_disallowed*) ; 
 struct wpa_bss_tmp_disallowed* os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_bss_tmp_disallow_timeout ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_set_driver_tmp_disallow_list (struct wpa_supplicant*) ; 
 struct wpa_bss_tmp_disallowed* wpas_get_disallowed_bss (struct wpa_supplicant*,int /*<<< orphan*/  const*) ; 

void wpa_bss_tmp_disallow(struct wpa_supplicant *wpa_s, const u8 *bssid,
			  unsigned int sec, int rssi_threshold)
{
	struct wpa_bss_tmp_disallowed *bss;

	bss = wpas_get_disallowed_bss(wpa_s, bssid);
	if (bss) {
		eloop_cancel_timeout(wpa_bss_tmp_disallow_timeout, wpa_s, bss);
		goto finish;
	}

	bss = os_malloc(sizeof(*bss));
	if (!bss) {
		wpa_printf(MSG_DEBUG,
			   "Failed to allocate memory for temp disallow BSS");
		return;
	}

	os_memcpy(bss->bssid, bssid, ETH_ALEN);
	dl_list_add(&wpa_s->bss_tmp_disallowed, &bss->list);
	wpa_set_driver_tmp_disallow_list(wpa_s);

finish:
	bss->rssi_threshold = rssi_threshold;
	eloop_register_timeout(sec, 0, wpa_bss_tmp_disallow_timeout,
			       wpa_s, bss);
}