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
struct wpa_supplicant {int dummy; } ;
struct wpa_signal_info {int current_signal; int current_txrate; int current_noise; scalar_t__ chanwidth; int center_frq1; int center_frq2; int avg_signal; int /*<<< orphan*/  frequency; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 scalar_t__ CHAN_WIDTH_UNKNOWN ; 
 int /*<<< orphan*/  DBUS_ERROR_FAILED ; 
 int /*<<< orphan*/  DBUS_TYPE_VARIANT ; 
 int /*<<< orphan*/  channel_width_to_string (scalar_t__) ; 
 int /*<<< orphan*/  dbus_message_iter_close_container (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_init_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_open_container (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbus_message_new_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * dbus_message_new_method_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_append_int32 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  wpa_dbus_dict_append_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_dbus_dict_append_uint32 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_dbus_dict_close_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_open_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int wpa_drv_signal_poll (struct wpa_supplicant*,struct wpa_signal_info*) ; 
 int /*<<< orphan*/ * wpas_dbus_error_no_memory (int /*<<< orphan*/ *) ; 

DBusMessage * wpas_dbus_handler_signal_poll(DBusMessage *message,
					    struct wpa_supplicant *wpa_s)
{
	struct wpa_signal_info si;
	DBusMessage *reply = NULL;
	DBusMessageIter iter, iter_dict, variant_iter;
	int ret;

	ret = wpa_drv_signal_poll(wpa_s, &si);
	if (ret) {
		return dbus_message_new_error(message, DBUS_ERROR_FAILED,
					      "Failed to read signal");
	}

	reply = dbus_message_new_method_return(message);
	if (reply == NULL)
		goto nomem;

	dbus_message_iter_init_append(reply, &iter);

	if (!dbus_message_iter_open_container(&iter, DBUS_TYPE_VARIANT,
					      "a{sv}", &variant_iter) ||
	    !wpa_dbus_dict_open_write(&variant_iter, &iter_dict) ||
	    !wpa_dbus_dict_append_int32(&iter_dict, "rssi",
					si.current_signal) ||
	    !wpa_dbus_dict_append_int32(&iter_dict, "linkspeed",
					si.current_txrate / 1000) ||
	    !wpa_dbus_dict_append_int32(&iter_dict, "noise",
					si.current_noise) ||
	    !wpa_dbus_dict_append_uint32(&iter_dict, "frequency",
					 si.frequency) ||
	    (si.chanwidth != CHAN_WIDTH_UNKNOWN &&
	     !wpa_dbus_dict_append_string(
		     &iter_dict, "width",
		     channel_width_to_string(si.chanwidth))) ||
	    (si.center_frq1 > 0 && si.center_frq2 > 0 &&
	     (!wpa_dbus_dict_append_int32(&iter_dict, "center-frq1",
					  si.center_frq1) ||
	      !wpa_dbus_dict_append_int32(&iter_dict, "center-frq2",
					  si.center_frq2))) ||
	    (si.avg_signal &&
	     !wpa_dbus_dict_append_int32(&iter_dict, "avg-rssi",
					 si.avg_signal)) ||
	    !wpa_dbus_dict_close_write(&variant_iter, &iter_dict) ||
	    !dbus_message_iter_close_container(&iter, &variant_iter))
		goto nomem;

	return reply;

nomem:
	if (reply)
		dbus_message_unref(reply);
	return wpas_dbus_error_no_memory(message);
}