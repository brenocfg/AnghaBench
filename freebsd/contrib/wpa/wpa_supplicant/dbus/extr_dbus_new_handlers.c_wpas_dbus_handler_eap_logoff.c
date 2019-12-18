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
struct wpa_supplicant {int /*<<< orphan*/  eapol; } ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  eapol_sm_notify_logoff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

DBusMessage * wpas_dbus_handler_eap_logoff(DBusMessage *message,
					   struct wpa_supplicant *wpa_s)
{
	eapol_sm_notify_logoff(wpa_s->eapol, TRUE);
	return NULL;
}