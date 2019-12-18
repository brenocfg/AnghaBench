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
struct wpa_channel_info {int dummy; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int hostapd_drv_channel_info (struct hostapd_data*,struct wpa_channel_info*) ; 

__attribute__((used)) static int hostapd_channel_info(void *ctx, struct wpa_channel_info *ci)
{
	struct hostapd_data *hapd = ctx;

	return hostapd_drv_channel_info(hapd, ci);
}