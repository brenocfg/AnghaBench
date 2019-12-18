#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wpa_channel_info {int dummy; } ;
struct hostapd_data {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
struct TYPE_2__ {int (* channel_info ) (int /*<<< orphan*/ ,struct wpa_channel_info*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct wpa_channel_info*) ; 

__attribute__((used)) static inline int hostapd_drv_channel_info(struct hostapd_data *hapd,
					   struct wpa_channel_info *ci)
{
	if (!hapd->driver || !hapd->driver->channel_info)
		return -1;
	return hapd->driver->channel_info(hapd->drv_priv, ci);
}