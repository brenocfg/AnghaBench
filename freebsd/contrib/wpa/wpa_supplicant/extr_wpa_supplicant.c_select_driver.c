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
struct wpa_supplicant {int /*<<< orphan*/ * global_drv_priv; TYPE_1__* driver; struct wpa_global* global; } ;
struct wpa_global {int /*<<< orphan*/ ** drv_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * (* global_init ) (struct wpa_global*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/ * stub1 (struct wpa_global*) ; 
 TYPE_1__** wpa_drivers ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int select_driver(struct wpa_supplicant *wpa_s, int i)
{
	struct wpa_global *global = wpa_s->global;

	if (wpa_drivers[i]->global_init && global->drv_priv[i] == NULL) {
		global->drv_priv[i] = wpa_drivers[i]->global_init(global);
		if (global->drv_priv[i] == NULL) {
			wpa_printf(MSG_ERROR, "Failed to initialize driver "
				   "'%s'", wpa_drivers[i]->name);
			return -1;
		}
	}

	wpa_s->driver = wpa_drivers[i];
	wpa_s->global_drv_priv = global->drv_priv[i];

	return 0;
}