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
struct wpa_interface_info {char* desc; int /*<<< orphan*/  ifname; int /*<<< orphan*/  drv_name; struct wpa_interface_info* next; } ;
struct wpa_global {int /*<<< orphan*/ * drv_priv; } ;
struct wpa_driver_ops {struct wpa_interface_info* (* get_interfaces ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int os_snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 struct wpa_interface_info* stub1 (int /*<<< orphan*/ ) ; 
 struct wpa_driver_ops** wpa_drivers ; 
 int /*<<< orphan*/  wpa_free_iface_info (struct wpa_interface_info*) ; 

__attribute__((used)) static int wpa_supplicant_global_iface_list(struct wpa_global *global,
					    char *buf, int len)
{
	int i, res;
	struct wpa_interface_info *iface = NULL, *last = NULL, *tmp;
	char *pos, *end;

	for (i = 0; wpa_drivers[i]; i++) {
		const struct wpa_driver_ops *drv = wpa_drivers[i];
		if (drv->get_interfaces == NULL)
			continue;
		tmp = drv->get_interfaces(global->drv_priv[i]);
		if (tmp == NULL)
			continue;

		if (last == NULL)
			iface = last = tmp;
		else
			last->next = tmp;
		while (last->next)
			last = last->next;
	}

	pos = buf;
	end = buf + len;
	for (tmp = iface; tmp; tmp = tmp->next) {
		res = os_snprintf(pos, end - pos, "%s\t%s\t%s\n",
				  tmp->drv_name, tmp->ifname,
				  tmp->desc ? tmp->desc : "");
		if (os_snprintf_error(end - pos, res)) {
			*pos = '\0';
			break;
		}
		pos += res;
	}

	wpa_free_iface_info(iface);

	return pos - buf;
}