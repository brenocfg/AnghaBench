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
struct wpa_supplicant {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
struct wpa_channel_info {int dummy; } ;
struct TYPE_2__ {int (* channel_info ) (int /*<<< orphan*/ ,struct wpa_channel_info*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct wpa_channel_info*) ; 

__attribute__((used)) static inline int wpa_drv_channel_info(struct wpa_supplicant *wpa_s,
				       struct wpa_channel_info *ci)
{
	if (wpa_s->driver->channel_info)
		return wpa_s->driver->channel_info(wpa_s->drv_priv, ci);
	return -1;
}