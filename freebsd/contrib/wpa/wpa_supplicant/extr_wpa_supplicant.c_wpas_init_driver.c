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
struct wpa_supplicant {int /*<<< orphan*/ * radio; int /*<<< orphan*/  ifname; TYPE_1__* conf; int /*<<< orphan*/ * drv_priv; } ;
struct wpa_interface {char* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver_param; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 char* os_strchr (char const*,char) ; 
 scalar_t__ os_strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/ * radio_add_interface (struct wpa_supplicant*,char const*) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,...) ; 
 char* wpa_driver_get_radio_name (struct wpa_supplicant*) ; 
 char* wpa_drv_get_ifname (struct wpa_supplicant*) ; 
 int /*<<< orphan*/ * wpa_drv_init (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_drv_set_param (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ wpa_supplicant_set_driver (struct wpa_supplicant*,char const*) ; 

__attribute__((used)) static int wpas_init_driver(struct wpa_supplicant *wpa_s,
			    const struct wpa_interface *iface)
{
	const char *ifname, *driver, *rn;

	driver = iface->driver;
next_driver:
	if (wpa_supplicant_set_driver(wpa_s, driver) < 0)
		return -1;

	wpa_s->drv_priv = wpa_drv_init(wpa_s, wpa_s->ifname);
	if (wpa_s->drv_priv == NULL) {
		const char *pos;
		pos = driver ? os_strchr(driver, ',') : NULL;
		if (pos) {
			wpa_dbg(wpa_s, MSG_DEBUG, "Failed to initialize "
				"driver interface - try next driver wrapper");
			driver = pos + 1;
			goto next_driver;
		}
		wpa_msg(wpa_s, MSG_ERROR, "Failed to initialize driver "
			"interface");
		return -1;
	}
	if (wpa_drv_set_param(wpa_s, wpa_s->conf->driver_param) < 0) {
		wpa_msg(wpa_s, MSG_ERROR, "Driver interface rejected "
			"driver_param '%s'", wpa_s->conf->driver_param);
		return -1;
	}

	ifname = wpa_drv_get_ifname(wpa_s);
	if (ifname && os_strcmp(ifname, wpa_s->ifname) != 0) {
		wpa_dbg(wpa_s, MSG_DEBUG, "Driver interface replaced "
			"interface name with '%s'", ifname);
		os_strlcpy(wpa_s->ifname, ifname, sizeof(wpa_s->ifname));
	}

	rn = wpa_driver_get_radio_name(wpa_s);
	if (rn && rn[0] == '\0')
		rn = NULL;

	wpa_s->radio = radio_add_interface(wpa_s, rn);
	if (wpa_s->radio == NULL)
		return -1;

	return 0;
}