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
typedef  int /*<<< orphan*/  u16 ;
struct wpa_supplicant {int /*<<< orphan*/  wps_pin_start_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_get_reltime (int /*<<< orphan*/ *) ; 
 int wpas_wps_start_dev_pw (struct wpa_supplicant*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wpas_wps_start_pin(struct wpa_supplicant *wpa_s, const u8 *bssid,
		       const char *pin, int p2p_group, u16 dev_pw_id)
{
	os_get_reltime(&wpa_s->wps_pin_start_time);
	return wpas_wps_start_dev_pw(wpa_s, NULL, bssid, pin, p2p_group,
				     dev_pw_id, NULL, NULL, 0, 0);
}