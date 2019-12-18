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
struct hostapd_hw_modes {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BW160 ; 
 int wpas_p2p_get_center_160mhz (struct wpa_supplicant*,struct hostapd_hw_modes*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_p2p_verify_channel (struct wpa_supplicant*,struct hostapd_hw_modes*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wpas_p2p_get_vht160_center(struct wpa_supplicant *wpa_s,
			       struct hostapd_hw_modes *mode, u8 channel)
{
	if (!wpas_p2p_verify_channel(wpa_s, mode, channel, BW160))
		return 0;
	return wpas_p2p_get_center_160mhz(wpa_s, mode, channel);
}