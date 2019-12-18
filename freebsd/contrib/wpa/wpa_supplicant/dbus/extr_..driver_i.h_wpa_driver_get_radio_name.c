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
struct TYPE_2__ {char const* (* get_radio_name ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 char const* stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline const char *
wpa_driver_get_radio_name(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->driver->get_radio_name)
		return wpa_s->driver->get_radio_name(wpa_s->drv_priv);
	return NULL;
}