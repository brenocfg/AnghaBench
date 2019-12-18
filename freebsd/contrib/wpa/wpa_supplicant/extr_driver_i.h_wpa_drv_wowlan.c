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
struct wowlan_triggers {int dummy; } ;
struct TYPE_2__ {int (* set_wowlan ) (int /*<<< orphan*/ ,struct wowlan_triggers const*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct wowlan_triggers const*) ; 

__attribute__((used)) static inline int wpa_drv_wowlan(struct wpa_supplicant *wpa_s,
				 const struct wowlan_triggers *triggers)
{
	if (!wpa_s->driver->set_wowlan)
		return -1;
	return wpa_s->driver->set_wowlan(wpa_s->drv_priv, triggers);
}