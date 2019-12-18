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
struct wpa_supplicant {TYPE_1__* conf; } ;
struct wpa_driver_capa {int dummy; } ;
struct wowlan_triggers {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wowlan_triggers; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct wowlan_triggers*) ; 
 int wpa_drv_wowlan (struct wpa_supplicant*,struct wowlan_triggers*) ; 
 struct wowlan_triggers* wpa_get_wowlan_triggers (int /*<<< orphan*/ ,struct wpa_driver_capa const*) ; 

__attribute__((used)) static int wpas_set_wowlan_triggers(struct wpa_supplicant *wpa_s,
				    const struct wpa_driver_capa *capa)
{
	struct wowlan_triggers *triggers;
	int ret = 0;

	if (!wpa_s->conf->wowlan_triggers)
		return 0;

	triggers = wpa_get_wowlan_triggers(wpa_s->conf->wowlan_triggers, capa);
	if (triggers) {
		ret = wpa_drv_wowlan(wpa_s, triggers);
		os_free(triggers);
	}
	return ret;
}