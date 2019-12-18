#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vals ;
struct wpabuf {int dummy; } ;
struct wpa_supplicant {TYPE_1__* ap_iface; } ;
struct wpa_dbus_property_desc {int dummy; } ;
struct wpa_dbus_dict_entry {scalar_t__ type; scalar_t__ array_type; int array_len; struct wpabuf** binarray_value; int /*<<< orphan*/  key; } ;
struct hostapd_data {TYPE_2__* conf; } ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
struct TYPE_4__ {struct wpabuf** wps_vendor_ext; } ;
struct TYPE_3__ {struct hostapd_data** bss; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_ERROR_INVALID_ARGS ; 
 scalar_t__ DBUS_TYPE_ARRAY ; 
 scalar_t__ DBUS_TYPE_BYTE ; 
 scalar_t__ DBUS_TYPE_DICT_ENTRY ; 
 scalar_t__ DBUS_TYPE_STRING ; 
 int /*<<< orphan*/  FALSE ; 
 int MAX_WPS_VENDOR_EXTENSIONS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WPAS_DBUS_TYPE_BINARRAY ; 
 scalar_t__ WPAS_P2P_ROLE_GO ; 
 scalar_t__ dbus_message_iter_get_arg_type (int /*<<< orphan*/ *) ; 
 scalar_t__ dbus_message_iter_get_element_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_get_fixed_array (int /*<<< orphan*/ *,char**,int*) ; 
 int /*<<< orphan*/  dbus_message_iter_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_recurse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_set_error_const (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hostapd_update_wps (struct hostapd_data*) ; 
 int /*<<< orphan*/  os_memset (struct wpabuf**,int /*<<< orphan*/ ,int) ; 
 scalar_t__ os_strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_dbus_dict_entry_clear (struct wpa_dbus_dict_entry*) ; 
 int /*<<< orphan*/  wpa_dbus_dict_get_entry (int /*<<< orphan*/ *,struct wpa_dbus_dict_entry*) ; 
 scalar_t__ wpa_dbus_dict_has_dict_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_open_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc_copy (char*,int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wpas_get_p2p_role (struct wpa_supplicant*) ; 

dbus_bool_t wpas_dbus_setter_p2p_group_vendor_ext(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, DBusError *error, void *user_data)
{
	struct wpa_supplicant *wpa_s = user_data;
	DBusMessageIter variant_iter, iter_dict, array_iter, sub;
	struct wpa_dbus_dict_entry entry = { .type = DBUS_TYPE_STRING };
	unsigned int i;
	struct hostapd_data *hapd = NULL;

	if (wpas_get_p2p_role(wpa_s) == WPAS_P2P_ROLE_GO &&
	    wpa_s->ap_iface != NULL)
		hapd = wpa_s->ap_iface->bss[0];
	else
		return FALSE;

	dbus_message_iter_recurse(iter, &variant_iter);
	if (dbus_message_iter_get_arg_type(&variant_iter) != DBUS_TYPE_ARRAY)
		return FALSE;

	/*
	 * This is supposed to be array of bytearrays (aay), but the earlier
	 * implementation used a dict with "WPSVendorExtensions" as the key in
	 * this setter function which does not match the format used by the
	 * getter function. For backwards compatibility, allow both formats to
	 * be used in the setter.
	 */
	if (dbus_message_iter_get_element_type(&variant_iter) ==
	    DBUS_TYPE_ARRAY) {
		/* This is the proper format matching the getter */
		struct wpabuf *vals[MAX_WPS_VENDOR_EXTENSIONS];

		dbus_message_iter_recurse(&variant_iter, &array_iter);

		if (dbus_message_iter_get_arg_type(&array_iter) !=
		    DBUS_TYPE_ARRAY ||
		    dbus_message_iter_get_element_type(&array_iter) !=
		    DBUS_TYPE_BYTE) {
			wpa_printf(MSG_DEBUG,
				   "dbus: Not an array of array of bytes");
			return FALSE;
		}

		i = 0;
		os_memset(vals, 0, sizeof(vals));

		while (dbus_message_iter_get_arg_type(&array_iter) ==
		       DBUS_TYPE_ARRAY) {
			char *val;
			int len;

			if (i == MAX_WPS_VENDOR_EXTENSIONS) {
				wpa_printf(MSG_DEBUG,
					   "dbus: Too many WPSVendorExtensions values");
				i = MAX_WPS_VENDOR_EXTENSIONS + 1;
				break;
			}

			dbus_message_iter_recurse(&array_iter, &sub);
			dbus_message_iter_get_fixed_array(&sub, &val, &len);
			wpa_hexdump(MSG_DEBUG, "dbus: WPSVendorExtentions[]",
				    val, len);
			vals[i] = wpabuf_alloc_copy(val, len);
			if (vals[i] == NULL) {
				i = MAX_WPS_VENDOR_EXTENSIONS + 1;
				break;
			}
			i++;
			dbus_message_iter_next(&array_iter);
		}

		if (i > MAX_WPS_VENDOR_EXTENSIONS) {
			for (i = 0; i < MAX_WPS_VENDOR_EXTENSIONS; i++)
				wpabuf_free(vals[i]);
			return FALSE;
		}

		for (i = 0; i < MAX_WPS_VENDOR_EXTENSIONS; i++) {
			wpabuf_free(hapd->conf->wps_vendor_ext[i]);
			hapd->conf->wps_vendor_ext[i] = vals[i];
		}

		hostapd_update_wps(hapd);

		return TRUE;
	}

	if (dbus_message_iter_get_element_type(&variant_iter) !=
	    DBUS_TYPE_DICT_ENTRY)
		return FALSE;

	wpa_printf(MSG_DEBUG,
		   "dbus: Try to use backwards compatibility version of WPSVendorExtensions setter");
	if (!wpa_dbus_dict_open_read(&variant_iter, &iter_dict, error))
		return FALSE;

	while (wpa_dbus_dict_has_dict_entry(&iter_dict)) {
		if (!wpa_dbus_dict_get_entry(&iter_dict, &entry)) {
			dbus_set_error_const(error, DBUS_ERROR_INVALID_ARGS,
					     "invalid message format");
			return FALSE;
		}

		if (os_strcmp(entry.key, "WPSVendorExtensions") == 0) {
			if (entry.type != DBUS_TYPE_ARRAY ||
			    entry.array_type != WPAS_DBUS_TYPE_BINARRAY ||
			    entry.array_len > MAX_WPS_VENDOR_EXTENSIONS)
				goto error;

			for (i = 0; i < MAX_WPS_VENDOR_EXTENSIONS; i++) {
				wpabuf_free(hapd->conf->wps_vendor_ext[i]);
				if (i < entry.array_len) {
					hapd->conf->wps_vendor_ext[i] =
						entry.binarray_value[i];
					entry.binarray_value[i] = NULL;
				} else
					hapd->conf->wps_vendor_ext[i] = NULL;
			}

			hostapd_update_wps(hapd);
		} else
			goto error;

		wpa_dbus_dict_entry_clear(&entry);
	}

	return TRUE;

error:
	wpa_dbus_dict_entry_clear(&entry);
	dbus_set_error_const(error, DBUS_ERROR_INVALID_ARGS,
			     "invalid message format");
	return FALSE;
}