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
typedef  int /*<<< orphan*/  u32 ;
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpas_dbus_signal_preq (struct wpa_supplicant*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 

void wpas_notify_preq(struct wpa_supplicant *wpa_s,
		      const u8 *addr, const u8 *dst, const u8 *bssid,
		      const u8 *ie, size_t ie_len, u32 ssi_signal)
{
#ifdef CONFIG_AP
	wpas_dbus_signal_preq(wpa_s, addr, dst, bssid, ie, ie_len, ssi_signal);
#endif /* CONFIG_AP */
}