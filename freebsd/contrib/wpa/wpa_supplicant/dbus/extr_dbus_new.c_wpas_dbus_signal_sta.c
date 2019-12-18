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
typedef  int /*<<< orphan*/  u8 ;
struct wpas_dbus_priv {int /*<<< orphan*/  con; } ;
struct wpa_supplicant {int /*<<< orphan*/  dbus_new_path; TYPE_1__* global; } ;
struct TYPE_2__ {struct wpas_dbus_priv* dbus; } ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int /*<<< orphan*/  MAC2STR (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  MACSTR ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  WPAS_DBUS_NEW_IFACE_INTERFACE ; 
 int WPAS_DBUS_OBJECT_PATH_MAX ; 
 int /*<<< orphan*/  dbus_connection_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dbus_message_append_args (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dbus_message_new_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dbus_message_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void wpas_dbus_signal_sta(struct wpa_supplicant *wpa_s,
				 const u8 *sta, const char *sig_name)
{
	struct wpas_dbus_priv *iface;
	DBusMessage *msg;
	char sta_mac[WPAS_DBUS_OBJECT_PATH_MAX];
	char *dev_mac;

	os_snprintf(sta_mac, WPAS_DBUS_OBJECT_PATH_MAX, MACSTR, MAC2STR(sta));
	dev_mac = sta_mac;

	iface = wpa_s->global->dbus;

	/* Do nothing if the control interface is not turned on */
	if (iface == NULL || !wpa_s->dbus_new_path)
		return;

	msg = dbus_message_new_signal(wpa_s->dbus_new_path,
				      WPAS_DBUS_NEW_IFACE_INTERFACE, sig_name);
	if (msg == NULL)
		return;

	if (dbus_message_append_args(msg, DBUS_TYPE_STRING, &dev_mac,
				     DBUS_TYPE_INVALID))
		dbus_connection_send(iface->con, msg, NULL);
	else
		wpa_printf(MSG_ERROR, "dbus: Failed to construct signal");
	dbus_message_unref(msg);

	wpa_printf(MSG_DEBUG, "dbus: Station MAC address '%s' '%s'",
		   sta_mac, sig_name);
}