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
struct wpa_driver_ap_params {int dummy; } ;
struct hostapd_data {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
struct TYPE_2__ {int (* set_ap ) (int /*<<< orphan*/ ,struct wpa_driver_ap_params*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct wpa_driver_ap_params*) ; 

__attribute__((used)) static inline int hostapd_drv_set_ap(struct hostapd_data *hapd,
				     struct wpa_driver_ap_params *params)
{
	if (hapd->driver == NULL || hapd->driver->set_ap == NULL)
		return 0;
	return hapd->driver->set_ap(hapd->drv_priv, params);
}