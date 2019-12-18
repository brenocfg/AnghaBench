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
 int wpa_drv_get_bssid (struct wpa_supplicant*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wpa_supplicant_get_bssid(void *ctx, u8 *bssid)
{
	struct wpa_supplicant *wpa_s = ctx;
	return wpa_drv_get_bssid(wpa_s, bssid);
}