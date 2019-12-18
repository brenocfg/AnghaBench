#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wpa_supplicant {unsigned int added_vif; } ;
struct wpa_global {int /*<<< orphan*/  ifaces; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPA_IF_STATION ; 
 int wpa_drv_if_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*) ; 
 struct wpa_supplicant* wpa_supplicant_get_iface (struct wpa_global*,char*) ; 
 int wpa_supplicant_remove_iface (struct wpa_global*,struct wpa_supplicant*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpa_supplicant_global_iface_remove(struct wpa_global *global,
					      char *cmd)
{
	struct wpa_supplicant *wpa_s;
	int ret;
	unsigned int delete_iface;

	wpa_printf(MSG_DEBUG, "CTRL_IFACE GLOBAL INTERFACE_REMOVE '%s'", cmd);

	wpa_s = wpa_supplicant_get_iface(global, cmd);
	if (wpa_s == NULL)
		return -1;
	delete_iface = wpa_s->added_vif;
	ret = wpa_supplicant_remove_iface(global, wpa_s, 0);
	if (!ret && delete_iface) {
		wpa_printf(MSG_DEBUG, "CTRL_IFACE deleting the interface '%s'",
			   cmd);
		ret = wpa_drv_if_remove(global->ifaces, WPA_IF_STATION, cmd);
	}
	return ret;
}