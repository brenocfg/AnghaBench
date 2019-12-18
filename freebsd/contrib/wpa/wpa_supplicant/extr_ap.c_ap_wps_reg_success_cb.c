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
 int /*<<< orphan*/  wpas_p2p_wps_success (struct wpa_supplicant*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void ap_wps_reg_success_cb(void *ctx, const u8 *mac_addr,
				  const u8 *uuid_e)
{
	struct wpa_supplicant *wpa_s = ctx;
	wpas_p2p_wps_success(wpa_s, mac_addr, 1);
}