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
struct wpa_driver_capa {int dummy; } ;
struct TYPE_2__ {int (* get_capa ) (int /*<<< orphan*/ ,struct wpa_driver_capa*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct wpa_driver_capa*) ; 

__attribute__((used)) static inline int wpa_drv_get_capa(struct wpa_supplicant *wpa_s,
				   struct wpa_driver_capa *capa)
{
	if (wpa_s->driver->get_capa) {
		return wpa_s->driver->get_capa(wpa_s->drv_priv, capa);
	}
	return -1;
}