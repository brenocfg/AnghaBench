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
struct wpa_supplicant {int /*<<< orphan*/  radio_list; int /*<<< orphan*/  ifname; struct wpa_supplicant* next; struct wpa_radio* radio; TYPE_1__* global; } ;
struct wpa_radio {int /*<<< orphan*/  ifaces; int /*<<< orphan*/  work; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {struct wpa_supplicant* ifaces; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  dl_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_list_init (int /*<<< orphan*/ *) ; 
 scalar_t__ os_strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 struct wpa_radio* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct wpa_radio * radio_add_interface(struct wpa_supplicant *wpa_s,
					      const char *rn)
{
	struct wpa_supplicant *iface = wpa_s->global->ifaces;
	struct wpa_radio *radio;

	while (rn && iface) {
		radio = iface->radio;
		if (radio && os_strcmp(rn, radio->name) == 0) {
			wpa_printf(MSG_DEBUG, "Add interface %s to existing radio %s",
				   wpa_s->ifname, rn);
			dl_list_add(&radio->ifaces, &wpa_s->radio_list);
			return radio;
		}

		iface = iface->next;
	}

	wpa_printf(MSG_DEBUG, "Add interface %s to a new radio %s",
		   wpa_s->ifname, rn ? rn : "N/A");
	radio = os_zalloc(sizeof(*radio));
	if (radio == NULL)
		return NULL;

	if (rn)
		os_strlcpy(radio->name, rn, sizeof(radio->name));
	dl_list_init(&radio->ifaces);
	dl_list_init(&radio->work);
	dl_list_add(&radio->ifaces, &wpa_s->radio_list);

	return radio;
}