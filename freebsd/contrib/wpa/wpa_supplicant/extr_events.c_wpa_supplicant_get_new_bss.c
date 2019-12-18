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
struct wpa_supplicant {struct wpa_ssid* current_ssid; } ;
struct wpa_ssid {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; } ;
struct wpa_bss {int dummy; } ;

/* Variables and functions */
 struct wpa_bss* wpa_bss_get (struct wpa_supplicant*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct wpa_bss* wpa_bss_get_bssid (struct wpa_supplicant*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static struct wpa_bss * wpa_supplicant_get_new_bss(
	struct wpa_supplicant *wpa_s, const u8 *bssid)
{
	struct wpa_bss *bss = NULL;
	struct wpa_ssid *ssid = wpa_s->current_ssid;

	if (ssid->ssid_len > 0)
		bss = wpa_bss_get(wpa_s, bssid, ssid->ssid, ssid->ssid_len);
	if (!bss)
		bss = wpa_bss_get_bssid(wpa_s, bssid);

	return bss;
}