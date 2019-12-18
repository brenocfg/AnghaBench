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
struct wpa_supplicant {struct wpa_radio* radio; int /*<<< orphan*/  radio_list; int /*<<< orphan*/  ifname; } ;
struct wpa_radio {int /*<<< orphan*/  name; int /*<<< orphan*/  ifaces; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  dl_list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_radio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct wpa_radio*) ; 
 int /*<<< orphan*/  radio_remove_works (struct wpa_supplicant*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radio_start_next_work ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void radio_remove_interface(struct wpa_supplicant *wpa_s)
{
	struct wpa_radio *radio = wpa_s->radio;

	if (!radio)
		return;

	wpa_printf(MSG_DEBUG, "Remove interface %s from radio %s",
		   wpa_s->ifname, radio->name);
	dl_list_del(&wpa_s->radio_list);
	radio_remove_works(wpa_s, NULL, 0);
	wpa_s->radio = NULL;
	if (!dl_list_empty(&radio->ifaces))
		return; /* Interfaces remain for this radio */

	wpa_printf(MSG_DEBUG, "Remove radio %s", radio->name);
	eloop_cancel_timeout(radio_start_next_work, radio, NULL);
	os_free(radio);
}