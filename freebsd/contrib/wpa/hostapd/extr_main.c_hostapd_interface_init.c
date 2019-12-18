#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hostapd_iface {TYPE_4__** bss; TYPE_3__* conf; struct hapd_interfaces* interfaces; } ;
struct hapd_interfaces {int dummy; } ;
struct TYPE_8__ {TYPE_1__* conf; } ;
struct TYPE_7__ {TYPE_2__** bss; } ;
struct TYPE_6__ {char* iface; } ;
struct TYPE_5__ {scalar_t__ logger_stdout_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  hostapd_drv_none (TYPE_4__*) ; 
 struct hostapd_iface* hostapd_init (struct hapd_interfaces*,char const*) ; 
 int /*<<< orphan*/  hostapd_interface_deinit_free (struct hostapd_iface*) ; 
 int /*<<< orphan*/  os_strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static struct hostapd_iface *
hostapd_interface_init(struct hapd_interfaces *interfaces, const char *if_name,
		       const char *config_fname, int debug)
{
	struct hostapd_iface *iface;
	int k;

	wpa_printf(MSG_ERROR, "Configuration file: %s", config_fname);
	iface = hostapd_init(interfaces, config_fname);
	if (!iface)
		return NULL;

	if (if_name) {
		os_strlcpy(iface->conf->bss[0]->iface, if_name,
			   sizeof(iface->conf->bss[0]->iface));
	}

	iface->interfaces = interfaces;

	for (k = 0; k < debug; k++) {
		if (iface->bss[0]->conf->logger_stdout_level > 0)
			iface->bss[0]->conf->logger_stdout_level--;
	}

	if (iface->conf->bss[0]->iface[0] == '\0' &&
	    !hostapd_drv_none(iface->bss[0])) {
		wpa_printf(MSG_ERROR,
			   "Interface name not specified in %s, nor by '-i' parameter",
			   config_fname);
		hostapd_interface_deinit_free(iface);
		return NULL;
	}

	return iface;
}