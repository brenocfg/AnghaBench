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
struct wpa_supplicant {TYPE_1__* conf; int /*<<< orphan*/  confname; struct wpa_supplicant* next; } ;
struct wpa_global {struct wpa_supplicant* ifaces; } ;
struct TYPE_2__ {int /*<<< orphan*/  update_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ wpa_config_write (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int wpas_global_ctrl_iface_save_config(struct wpa_global *global)
{
	int ret = 0, saved = 0;
	struct wpa_supplicant *wpa_s;

	for (wpa_s = global->ifaces; wpa_s; wpa_s = wpa_s->next) {
		if (!wpa_s->conf->update_config) {
			wpa_dbg(wpa_s, MSG_DEBUG, "CTRL_IFACE: SAVE_CONFIG - Not allowed to update configuration (update_config=0)");
			continue;
		}

		if (wpa_config_write(wpa_s->confname, wpa_s->conf)) {
			wpa_dbg(wpa_s, MSG_DEBUG, "CTRL_IFACE: SAVE_CONFIG - Failed to update configuration");
			ret = 1;
		} else {
			wpa_dbg(wpa_s, MSG_DEBUG, "CTRL_IFACE: SAVE_CONFIG - Configuration updated");
			saved++;
		}
	}

	if (!saved && !ret) {
		wpa_dbg(wpa_s, MSG_DEBUG,
			"CTRL_IFACE: SAVE_CONFIG - No configuration files could be updated");
		ret = 1;
	}

	return ret;
}