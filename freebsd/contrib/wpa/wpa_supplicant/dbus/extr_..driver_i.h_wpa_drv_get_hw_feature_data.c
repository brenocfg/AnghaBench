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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wpa_supplicant {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
struct hostapd_hw_modes {int dummy; } ;
struct TYPE_2__ {struct hostapd_hw_modes* (* get_hw_feature_data ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 struct hostapd_hw_modes* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct hostapd_hw_modes *
wpa_drv_get_hw_feature_data(struct wpa_supplicant *wpa_s, u16 *num_modes,
			    u16 *flags, u8 *dfs_domain)
{
	if (wpa_s->driver->get_hw_feature_data)
		return wpa_s->driver->get_hw_feature_data(wpa_s->drv_priv,
							  num_modes, flags,
							  dfs_domain);
	return NULL;
}