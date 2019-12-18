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
struct wpa_supplicant {TYPE_2__* conf; TYPE_1__* global; } ;
struct wpa_dbus_property_desc {int dummy; } ;
struct wpa_dbus_dict_entry {scalar_t__ type; scalar_t__ array_type; scalar_t__ array_len; int uint32_value; int /*<<< orphan*/  key; int /*<<< orphan*/  bool_value; int /*<<< orphan*/  bytearray_value; int /*<<< orphan*/  str_value; int /*<<< orphan*/ ** binarray_value; } ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
struct TYPE_4__ {char* device_name; int changed_parameters; unsigned int num_sec_device_types; int p2p_go_intent; int p2p_listen_reg_class; int p2p_listen_channel; int p2p_oper_reg_class; int p2p_oper_channel; char* p2p_ssid_postfix; int p2p_group_idle; int disassoc_low_ack; int p2p_search_delay; int /*<<< orphan*/  p2p_no_group_iface; int /*<<< orphan*/  ip_addr_end; int /*<<< orphan*/  ip_addr_start; int /*<<< orphan*/  ip_addr_mask; int /*<<< orphan*/  ip_addr_go; int /*<<< orphan*/  p2p_intra_bss; int /*<<< orphan*/  persistent_reconnect; int /*<<< orphan*/ ** wps_vendor_ext; int /*<<< orphan*/ * sec_device_type; int /*<<< orphan*/  device_type; } ;
struct TYPE_3__ {struct wpa_supplicant* p2p_init_wpa_s; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int CFG_CHANGED_DEVICE_NAME ; 
 int CFG_CHANGED_DEVICE_TYPE ; 
 int CFG_CHANGED_P2P_INTRA_BSS ; 
 int CFG_CHANGED_P2P_LISTEN_CHANNEL ; 
 int CFG_CHANGED_P2P_OPER_CHANNEL ; 
 int CFG_CHANGED_P2P_SSID_POSTFIX ; 
 int CFG_CHANGED_SEC_DEVICE_TYPE ; 
 int CFG_CHANGED_VENDOR_EXTENSION ; 
 int /*<<< orphan*/  DBUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  DBUS_ERROR_NO_MEMORY ; 
 scalar_t__ DBUS_TYPE_ARRAY ; 
 scalar_t__ DBUS_TYPE_BOOLEAN ; 
 scalar_t__ DBUS_TYPE_BYTE ; 
 scalar_t__ DBUS_TYPE_STRING ; 
 scalar_t__ DBUS_TYPE_UINT32 ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MAX_SEC_DEVICE_TYPES ; 
 unsigned int P2P_MAX_WPS_VENDOR_EXT ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WPAS_DBUS_TYPE_BINARRAY ; 
 scalar_t__ WPS_DEV_NAME_MAX_LEN ; 
 scalar_t__ WPS_DEV_TYPE_LEN ; 
 int /*<<< orphan*/  dbus_message_iter_recurse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_set_error_const (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ os_strcmp (int /*<<< orphan*/ ,char*) ; 
 char* os_strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ os_strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_dbus_dict_entry_clear (struct wpa_dbus_dict_entry*) ; 
 int /*<<< orphan*/  wpa_dbus_dict_get_entry (int /*<<< orphan*/ *,struct wpa_dbus_dict_entry*) ; 
 scalar_t__ wpa_dbus_dict_has_dict_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_open_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_p2p_check_enabled (struct wpa_supplicant*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_update_config (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_head (int /*<<< orphan*/ *) ; 
 scalar_t__ wpabuf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpas_dbus_validate_dbus_ipaddr (struct wpa_dbus_dict_entry) ; 

dbus_bool_t wpas_dbus_setter_p2p_device_config(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, DBusError *error, void *user_data)
{
	struct wpa_supplicant *wpa_s = user_data;
	DBusMessageIter variant_iter, iter_dict;
	struct wpa_dbus_dict_entry entry = {.type = DBUS_TYPE_STRING };
	unsigned int i;

	if (!wpa_dbus_p2p_check_enabled(wpa_s, NULL, NULL, error))
		return FALSE;

	wpa_s = wpa_s->global->p2p_init_wpa_s;

	dbus_message_iter_recurse(iter, &variant_iter);
	if (!wpa_dbus_dict_open_read(&variant_iter, &iter_dict, error))
		return FALSE;

	while (wpa_dbus_dict_has_dict_entry(&iter_dict)) {
		if (!wpa_dbus_dict_get_entry(&iter_dict, &entry)) {
			dbus_set_error_const(error, DBUS_ERROR_INVALID_ARGS,
					     "invalid message format");
			return FALSE;
		}

		if (os_strcmp(entry.key, "DeviceName") == 0) {
			char *devname;

			if (entry.type != DBUS_TYPE_STRING ||
			    os_strlen(entry.str_value) > WPS_DEV_NAME_MAX_LEN)
				goto error;

			devname = os_strdup(entry.str_value);
			if (devname == NULL)
				goto err_no_mem_clear;

			os_free(wpa_s->conf->device_name);
			wpa_s->conf->device_name = devname;

			wpa_s->conf->changed_parameters |=
				CFG_CHANGED_DEVICE_NAME;
		} else if (os_strcmp(entry.key, "PrimaryDeviceType") == 0) {
			if (entry.type != DBUS_TYPE_ARRAY ||
			    entry.array_type != DBUS_TYPE_BYTE ||
			    entry.array_len != WPS_DEV_TYPE_LEN)
				goto error;

			os_memcpy(wpa_s->conf->device_type,
				  entry.bytearray_value,
				  WPS_DEV_TYPE_LEN);
			wpa_s->conf->changed_parameters |=
				CFG_CHANGED_DEVICE_TYPE;
		} else if (os_strcmp(entry.key, "SecondaryDeviceTypes") == 0) {
			if (entry.type != DBUS_TYPE_ARRAY ||
			    entry.array_type != WPAS_DBUS_TYPE_BINARRAY ||
			    entry.array_len > MAX_SEC_DEVICE_TYPES)
				goto error;

			for (i = 0; i < entry.array_len; i++)
				if (wpabuf_len(entry.binarray_value[i]) !=
				    WPS_DEV_TYPE_LEN)
					goto err_no_mem_clear;
			for (i = 0; i < entry.array_len; i++)
				os_memcpy(wpa_s->conf->sec_device_type[i],
					  wpabuf_head(entry.binarray_value[i]),
					  WPS_DEV_TYPE_LEN);
			wpa_s->conf->num_sec_device_types = entry.array_len;
			wpa_s->conf->changed_parameters |=
					CFG_CHANGED_SEC_DEVICE_TYPE;
		} else if (os_strcmp(entry.key, "VendorExtension") == 0) {
			if (entry.type != DBUS_TYPE_ARRAY ||
			    entry.array_type != WPAS_DBUS_TYPE_BINARRAY ||
			    (entry.array_len > P2P_MAX_WPS_VENDOR_EXT))
				goto error;

			wpa_s->conf->changed_parameters |=
				CFG_CHANGED_VENDOR_EXTENSION;

			for (i = 0; i < P2P_MAX_WPS_VENDOR_EXT; i++) {
				wpabuf_free(wpa_s->conf->wps_vendor_ext[i]);
				if (i < entry.array_len) {
					wpa_s->conf->wps_vendor_ext[i] =
						entry.binarray_value[i];
					entry.binarray_value[i] = NULL;
				} else
					wpa_s->conf->wps_vendor_ext[i] = NULL;
			}
		} else if (os_strcmp(entry.key, "GOIntent") == 0 &&
			   entry.type == DBUS_TYPE_UINT32 &&
			   (entry.uint32_value <= 15))
			wpa_s->conf->p2p_go_intent = entry.uint32_value;
		else if (os_strcmp(entry.key, "PersistentReconnect") == 0 &&
			 entry.type == DBUS_TYPE_BOOLEAN)
			wpa_s->conf->persistent_reconnect = entry.bool_value;
		else if (os_strcmp(entry.key, "ListenRegClass") == 0 &&
			 entry.type == DBUS_TYPE_UINT32) {
			wpa_s->conf->p2p_listen_reg_class = entry.uint32_value;
			wpa_s->conf->changed_parameters |=
				CFG_CHANGED_P2P_LISTEN_CHANNEL;
		} else if (os_strcmp(entry.key, "ListenChannel") == 0 &&
			   entry.type == DBUS_TYPE_UINT32) {
			wpa_s->conf->p2p_listen_channel = entry.uint32_value;
			wpa_s->conf->changed_parameters |=
				CFG_CHANGED_P2P_LISTEN_CHANNEL;
		} else if (os_strcmp(entry.key, "OperRegClass") == 0 &&
			   entry.type == DBUS_TYPE_UINT32) {
			wpa_s->conf->p2p_oper_reg_class = entry.uint32_value;
			wpa_s->conf->changed_parameters |=
				CFG_CHANGED_P2P_OPER_CHANNEL;
		} else if (os_strcmp(entry.key, "OperChannel") == 0 &&
			   entry.type == DBUS_TYPE_UINT32) {
			wpa_s->conf->p2p_oper_channel = entry.uint32_value;
			wpa_s->conf->changed_parameters |=
				CFG_CHANGED_P2P_OPER_CHANNEL;
		} else if (os_strcmp(entry.key, "SsidPostfix") == 0) {
			char *postfix;

			if (entry.type != DBUS_TYPE_STRING)
				goto error;

			postfix = os_strdup(entry.str_value);
			if (!postfix)
				goto err_no_mem_clear;

			os_free(wpa_s->conf->p2p_ssid_postfix);
			wpa_s->conf->p2p_ssid_postfix = postfix;

			wpa_s->conf->changed_parameters |=
					CFG_CHANGED_P2P_SSID_POSTFIX;
		} else if (os_strcmp(entry.key, "IntraBss") == 0 &&
			   entry.type == DBUS_TYPE_BOOLEAN) {
			wpa_s->conf->p2p_intra_bss = entry.bool_value;
			wpa_s->conf->changed_parameters |=
				CFG_CHANGED_P2P_INTRA_BSS;
		} else if (os_strcmp(entry.key, "IpAddrGo") == 0) {
			if (!wpas_dbus_validate_dbus_ipaddr(entry))
				goto error;
			os_memcpy(wpa_s->conf->ip_addr_go,
				  entry.bytearray_value, 4);
		} else if (os_strcmp(entry.key, "IpAddrMask") == 0) {
			if (!wpas_dbus_validate_dbus_ipaddr(entry))
				goto error;
			os_memcpy(wpa_s->conf->ip_addr_mask,
				  entry.bytearray_value, 4);
		} else if (os_strcmp(entry.key, "IpAddrStart") == 0) {
			if (!wpas_dbus_validate_dbus_ipaddr(entry))
				goto error;
			os_memcpy(wpa_s->conf->ip_addr_start,
				  entry.bytearray_value, 4);
		} else if (os_strcmp(entry.key, "IpAddrEnd") == 0) {
			if (!wpas_dbus_validate_dbus_ipaddr(entry))
				goto error;
			os_memcpy(wpa_s->conf->ip_addr_end,
				  entry.bytearray_value, 4);
		} else if (os_strcmp(entry.key, "GroupIdle") == 0 &&
			   entry.type == DBUS_TYPE_UINT32)
			wpa_s->conf->p2p_group_idle = entry.uint32_value;
		else if (os_strcmp(entry.key, "disassoc_low_ack") == 0 &&
			 entry.type == DBUS_TYPE_UINT32)
			wpa_s->conf->disassoc_low_ack = entry.uint32_value;
		else if (os_strcmp(entry.key, "NoGroupIface") == 0 &&
			 entry.type == DBUS_TYPE_BOOLEAN)
			wpa_s->conf->p2p_no_group_iface = entry.bool_value;
		else if (os_strcmp(entry.key, "p2p_search_delay") == 0 &&
			 entry.type == DBUS_TYPE_UINT32)
			wpa_s->conf->p2p_search_delay = entry.uint32_value;
		else
			goto error;

		wpa_dbus_dict_entry_clear(&entry);
	}

	if (wpa_s->conf->changed_parameters) {
		/* Some changed parameters requires to update config*/
		wpa_supplicant_update_config(wpa_s);
	}

	return TRUE;

 error:
	dbus_set_error_const(error, DBUS_ERROR_INVALID_ARGS,
			     "invalid message format");
	wpa_dbus_dict_entry_clear(&entry);
	return FALSE;

 err_no_mem_clear:
	dbus_set_error_const(error, DBUS_ERROR_NO_MEMORY, "no memory");
	wpa_dbus_dict_entry_clear(&entry);
	return FALSE;
}