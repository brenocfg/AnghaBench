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
struct wpa_supplicant {TYPE_1__* global; } ;
struct TYPE_2__ {int /*<<< orphan*/  p2p_init_wpa_s; } ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  wpas_p2p_stop_find (int /*<<< orphan*/ ) ; 

DBusMessage * wpas_dbus_handler_p2p_stop_find(DBusMessage *message,
					      struct wpa_supplicant *wpa_s)
{
	wpas_p2p_stop_find(wpa_s->global->p2p_init_wpa_s);
	return NULL;
}