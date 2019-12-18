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
struct wpas_dbus_priv {int /*<<< orphan*/  con; } ;
struct wpabuf {int dummy; } ;
struct wpa_supplicant {int /*<<< orphan*/  dbus_new_path; TYPE_1__* global; } ;
struct TYPE_2__ {struct wpas_dbus_priv* dbus; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  WPAS_DBUS_NEW_IFACE_INTERFACE ; 
 int /*<<< orphan*/  dbus_connection_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_init_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbus_message_new_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dbus_message_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_append_byte_array (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_dbus_dict_append_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  wpa_dbus_dict_append_string_array (int /*<<< orphan*/ *,char*,char const**,int) ; 
 int /*<<< orphan*/  wpa_dbus_dict_append_uint32 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  wpa_dbus_dict_close_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_open_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf const*) ; 

void wpas_dbus_signal_certification(struct wpa_supplicant *wpa_s,
				    int depth, const char *subject,
				    const char *altsubject[],
				    int num_altsubject,
				    const char *cert_hash,
				    const struct wpabuf *cert)
{
	struct wpas_dbus_priv *iface;
	DBusMessage *msg;
	DBusMessageIter iter, dict_iter;

	iface = wpa_s->global->dbus;

	/* Do nothing if the control interface is not turned on */
	if (iface == NULL || !wpa_s->dbus_new_path)
		return;

	msg = dbus_message_new_signal(wpa_s->dbus_new_path,
				      WPAS_DBUS_NEW_IFACE_INTERFACE,
				      "Certification");
	if (msg == NULL)
		return;

	dbus_message_iter_init_append(msg, &iter);
	if (!wpa_dbus_dict_open_write(&iter, &dict_iter) ||
	    !wpa_dbus_dict_append_uint32(&dict_iter, "depth", depth) ||
	    !wpa_dbus_dict_append_string(&dict_iter, "subject", subject) ||
	    (altsubject && num_altsubject &&
	     !wpa_dbus_dict_append_string_array(&dict_iter, "altsubject",
						altsubject, num_altsubject)) ||
	    (cert_hash &&
	     !wpa_dbus_dict_append_string(&dict_iter, "cert_hash",
					  cert_hash)) ||
	    (cert &&
	     !wpa_dbus_dict_append_byte_array(&dict_iter, "cert",
					      wpabuf_head(cert),
					      wpabuf_len(cert))) ||
	    !wpa_dbus_dict_close_write(&iter, &dict_iter))
		wpa_printf(MSG_ERROR, "dbus: Failed to construct signal");
	else
		dbus_connection_send(iface->con, msg, NULL);
	dbus_message_unref(msg);
}