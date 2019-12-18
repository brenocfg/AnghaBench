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
struct wpa_supplicant {int dummy; } ;
struct wpa_channel_info {int dummy; } ;

/* Variables and functions */
 int wpa_drv_channel_info (struct wpa_supplicant*,struct wpa_channel_info*) ; 

__attribute__((used)) static int wpa_supplicant_channel_info(void *_wpa_s,
				       struct wpa_channel_info *ci)
{
	struct wpa_supplicant *wpa_s = _wpa_s;

	return wpa_drv_channel_info(wpa_s, ci);
}