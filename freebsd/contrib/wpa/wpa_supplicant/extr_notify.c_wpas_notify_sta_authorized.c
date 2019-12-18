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
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpas_notify_ap_sta_authorized (struct wpa_supplicant*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpas_notify_ap_sta_deauthorized (struct wpa_supplicant*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

void wpas_notify_sta_authorized(struct wpa_supplicant *wpa_s,
				const u8 *mac_addr, int authorized,
				const u8 *p2p_dev_addr)
{
	if (authorized)
		wpas_notify_ap_sta_authorized(wpa_s, mac_addr, p2p_dev_addr);
	else
		wpas_notify_ap_sta_deauthorized(wpa_s, mac_addr, p2p_dev_addr);
}