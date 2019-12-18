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
struct wpa_driver_auth_params {int dummy; } ;
struct TYPE_2__ {int (* authenticate ) (int /*<<< orphan*/ ,struct wpa_driver_auth_params*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct wpa_driver_auth_params*) ; 

__attribute__((used)) static inline int wpa_drv_authenticate(struct wpa_supplicant *wpa_s,
				       struct wpa_driver_auth_params *params)
{
	if (wpa_s->driver->authenticate)
		return wpa_s->driver->authenticate(wpa_s->drv_priv, params);
	return -1;
}