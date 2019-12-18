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
struct wpa_supplicant {TYPE_1__* conf; } ;
struct wpa_driver_capa {int enc; int key_mgmt; int auth; int flags; int /*<<< orphan*/  max_scan_ssids; } ;
struct wpa_dbus_property_desc {int dummy; } ;
typedef  int /*<<< orphan*/  dbus_int32_t ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
struct TYPE_2__ {int /*<<< orphan*/  p2p_disabled; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  DBUS_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  DBUS_TYPE_VARIANT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int WPA_DRIVER_AUTH_LEAP ; 
 int WPA_DRIVER_AUTH_OPEN ; 
 int WPA_DRIVER_AUTH_SHARED ; 
 int WPA_DRIVER_CAPA_ENC_BIP ; 
 int WPA_DRIVER_CAPA_ENC_BIP_CMAC_256 ; 
 int WPA_DRIVER_CAPA_ENC_BIP_GMAC_128 ; 
 int WPA_DRIVER_CAPA_ENC_BIP_GMAC_256 ; 
 int WPA_DRIVER_CAPA_ENC_CCMP ; 
 int WPA_DRIVER_CAPA_ENC_CCMP_256 ; 
 int WPA_DRIVER_CAPA_ENC_GCMP ; 
 int WPA_DRIVER_CAPA_ENC_GCMP_256 ; 
 int WPA_DRIVER_CAPA_ENC_TKIP ; 
 int WPA_DRIVER_CAPA_ENC_WEP104 ; 
 int WPA_DRIVER_CAPA_ENC_WEP40 ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_FT ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_FT_PSK ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_WPA ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_WPA2 ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_WPA2_PSK ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_WPA_NONE ; 
 int WPA_DRIVER_CAPA_KEY_MGMT_WPA_PSK ; 
 int WPA_DRIVER_FLAGS_AP ; 
 int WPA_DRIVER_FLAGS_IBSS ; 
 int WPA_DRIVER_FLAGS_MESH ; 
 int WPA_DRIVER_FLAGS_P2P_CAPABLE ; 
 int /*<<< orphan*/  dbus_message_iter_close_container (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_open_container (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_set_error_const (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_dbus_dict_append_int32 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_dbus_dict_append_string_array (int /*<<< orphan*/ *,char*,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_dbus_dict_begin_string_array (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_close_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_end_string_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_open_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_string_array_add_element (int /*<<< orphan*/ *,char*) ; 
 int wpa_drv_get_capa (struct wpa_supplicant*,struct wpa_driver_capa*) ; 

dbus_bool_t wpas_dbus_getter_capabilities(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, DBusError *error, void *user_data)
{
	struct wpa_supplicant *wpa_s = user_data;
	struct wpa_driver_capa capa;
	int res;
	DBusMessageIter iter_dict, iter_dict_entry, iter_dict_val, iter_array,
		variant_iter;
	const char *scans[] = { "active", "passive", "ssid" };

	if (!dbus_message_iter_open_container(iter, DBUS_TYPE_VARIANT,
					      "a{sv}", &variant_iter) ||
	    !wpa_dbus_dict_open_write(&variant_iter, &iter_dict))
		goto nomem;

	res = wpa_drv_get_capa(wpa_s, &capa);

	/***** pairwise cipher */
	if (res < 0) {
		const char *args[] = {"ccmp", "tkip", "none"};

		if (!wpa_dbus_dict_append_string_array(
			    &iter_dict, "Pairwise", args,
			    ARRAY_SIZE(args)))
			goto nomem;
	} else {
		if (!wpa_dbus_dict_begin_string_array(&iter_dict, "Pairwise",
						      &iter_dict_entry,
						      &iter_dict_val,
						      &iter_array) ||
		    ((capa.enc & WPA_DRIVER_CAPA_ENC_CCMP_256) &&
		     !wpa_dbus_dict_string_array_add_element(
			     &iter_array, "ccmp-256")) ||
		    ((capa.enc & WPA_DRIVER_CAPA_ENC_GCMP_256) &&
		     !wpa_dbus_dict_string_array_add_element(
			     &iter_array, "gcmp-256")) ||
		    ((capa.enc & WPA_DRIVER_CAPA_ENC_CCMP) &&
		     !wpa_dbus_dict_string_array_add_element(
			     &iter_array, "ccmp")) ||
		    ((capa.enc & WPA_DRIVER_CAPA_ENC_GCMP) &&
		     !wpa_dbus_dict_string_array_add_element(
			     &iter_array, "gcmp")) ||
		    ((capa.enc & WPA_DRIVER_CAPA_ENC_TKIP) &&
		     !wpa_dbus_dict_string_array_add_element(
			     &iter_array, "tkip")) ||
		    ((capa.key_mgmt & WPA_DRIVER_CAPA_KEY_MGMT_WPA_NONE) &&
		     !wpa_dbus_dict_string_array_add_element(
			     &iter_array, "none")) ||
		    !wpa_dbus_dict_end_string_array(&iter_dict,
						    &iter_dict_entry,
						    &iter_dict_val,
						    &iter_array))
			goto nomem;
	}

	/***** group cipher */
	if (res < 0) {
		const char *args[] = {
			"ccmp", "tkip", "wep104", "wep40"
		};

		if (!wpa_dbus_dict_append_string_array(
			    &iter_dict, "Group", args,
			    ARRAY_SIZE(args)))
			goto nomem;
	} else {
		if (!wpa_dbus_dict_begin_string_array(&iter_dict, "Group",
						      &iter_dict_entry,
						      &iter_dict_val,
						      &iter_array) ||
		    ((capa.enc & WPA_DRIVER_CAPA_ENC_CCMP_256) &&
		     !wpa_dbus_dict_string_array_add_element(
			     &iter_array, "ccmp-256")) ||
		    ((capa.enc & WPA_DRIVER_CAPA_ENC_GCMP_256) &&
		     !wpa_dbus_dict_string_array_add_element(
			     &iter_array, "gcmp-256")) ||
		    ((capa.enc & WPA_DRIVER_CAPA_ENC_CCMP) &&
		     !wpa_dbus_dict_string_array_add_element(
			     &iter_array, "ccmp")) ||
		    ((capa.enc & WPA_DRIVER_CAPA_ENC_GCMP) &&
		     !wpa_dbus_dict_string_array_add_element(
			     &iter_array, "gcmp")) ||
		    ((capa.enc & WPA_DRIVER_CAPA_ENC_TKIP) &&
		     !wpa_dbus_dict_string_array_add_element(
			     &iter_array, "tkip")) ||
		    ((capa.enc & WPA_DRIVER_CAPA_ENC_WEP104) &&
		     !wpa_dbus_dict_string_array_add_element(
			     &iter_array, "wep104")) ||
		    ((capa.enc & WPA_DRIVER_CAPA_ENC_WEP40) &&
		     !wpa_dbus_dict_string_array_add_element(
			     &iter_array, "wep40")) ||
		    !wpa_dbus_dict_end_string_array(&iter_dict,
						    &iter_dict_entry,
						    &iter_dict_val,
						    &iter_array))
			goto nomem;
	}

	if (!wpa_dbus_dict_begin_string_array(&iter_dict, "GroupMgmt",
					      &iter_dict_entry,
					      &iter_dict_val,
					      &iter_array) ||
	    (res == 0 && (capa.enc & WPA_DRIVER_CAPA_ENC_BIP) &&
	     !wpa_dbus_dict_string_array_add_element(
		     &iter_array, "aes-128-cmac")) ||
	    (res == 0 && (capa.enc & WPA_DRIVER_CAPA_ENC_BIP_GMAC_128) &&
	     !wpa_dbus_dict_string_array_add_element(
		     &iter_array, "bip-gmac-128")) ||
	    (res == 0 && (capa.enc & WPA_DRIVER_CAPA_ENC_BIP_GMAC_256) &&
	     !wpa_dbus_dict_string_array_add_element(
		     &iter_array, "bip-gmac-256")) ||
	    (res == 0 && (capa.enc & WPA_DRIVER_CAPA_ENC_BIP_CMAC_256) &&
	     !wpa_dbus_dict_string_array_add_element(
		     &iter_array, "bip-cmac-256")) ||
	    !wpa_dbus_dict_end_string_array(&iter_dict,
					    &iter_dict_entry,
					    &iter_dict_val,
					    &iter_array))
		goto nomem;

	/***** key management */
	if (res < 0) {
		const char *args[] = {
			"wpa-psk", "wpa-eap", "ieee8021x", "wpa-none",
#ifdef CONFIG_WPS
			"wps",
#endif /* CONFIG_WPS */
			"none"
		};
		if (!wpa_dbus_dict_append_string_array(
			    &iter_dict, "KeyMgmt", args,
			    ARRAY_SIZE(args)))
			goto nomem;
	} else {
		if (!wpa_dbus_dict_begin_string_array(&iter_dict, "KeyMgmt",
						      &iter_dict_entry,
						      &iter_dict_val,
						      &iter_array) ||
		    !wpa_dbus_dict_string_array_add_element(&iter_array,
							    "none") ||
		    !wpa_dbus_dict_string_array_add_element(&iter_array,
							    "ieee8021x"))
			goto nomem;

		if (capa.key_mgmt & (WPA_DRIVER_CAPA_KEY_MGMT_WPA |
				     WPA_DRIVER_CAPA_KEY_MGMT_WPA2)) {
			if (!wpa_dbus_dict_string_array_add_element(
				    &iter_array, "wpa-eap") ||
			    ((capa.key_mgmt & WPA_DRIVER_CAPA_KEY_MGMT_FT) &&
			     !wpa_dbus_dict_string_array_add_element(
				     &iter_array, "wpa-ft-eap")))
				goto nomem;

/* TODO: Ensure that driver actually supports sha256 encryption. */
#ifdef CONFIG_IEEE80211W
			if (!wpa_dbus_dict_string_array_add_element(
				    &iter_array, "wpa-eap-sha256"))
				goto nomem;
#endif /* CONFIG_IEEE80211W */
		}

		if (capa.key_mgmt & (WPA_DRIVER_CAPA_KEY_MGMT_WPA_PSK |
				     WPA_DRIVER_CAPA_KEY_MGMT_WPA2_PSK)) {
			if (!wpa_dbus_dict_string_array_add_element(
				    &iter_array, "wpa-psk") ||
			    ((capa.key_mgmt &
			      WPA_DRIVER_CAPA_KEY_MGMT_FT_PSK) &&
			     !wpa_dbus_dict_string_array_add_element(
				     &iter_array, "wpa-ft-psk")))
				goto nomem;

/* TODO: Ensure that driver actually supports sha256 encryption. */
#ifdef CONFIG_IEEE80211W
			if (!wpa_dbus_dict_string_array_add_element(
				    &iter_array, "wpa-psk-sha256"))
				goto nomem;
#endif /* CONFIG_IEEE80211W */
		}

		if ((capa.key_mgmt & WPA_DRIVER_CAPA_KEY_MGMT_WPA_NONE) &&
		    !wpa_dbus_dict_string_array_add_element(&iter_array,
							    "wpa-none"))
			goto nomem;


#ifdef CONFIG_WPS
		if (!wpa_dbus_dict_string_array_add_element(&iter_array,
							    "wps"))
			goto nomem;
#endif /* CONFIG_WPS */

		if (!wpa_dbus_dict_end_string_array(&iter_dict,
						    &iter_dict_entry,
						    &iter_dict_val,
						    &iter_array))
			goto nomem;
	}

	/***** WPA protocol */
	if (res < 0) {
		const char *args[] = { "rsn", "wpa" };

		if (!wpa_dbus_dict_append_string_array(
			    &iter_dict, "Protocol", args,
			    ARRAY_SIZE(args)))
			goto nomem;
	} else {
		if (!wpa_dbus_dict_begin_string_array(&iter_dict, "Protocol",
						      &iter_dict_entry,
						      &iter_dict_val,
						      &iter_array) ||
		    ((capa.key_mgmt & (WPA_DRIVER_CAPA_KEY_MGMT_WPA2 |
				       WPA_DRIVER_CAPA_KEY_MGMT_WPA2_PSK)) &&
		     !wpa_dbus_dict_string_array_add_element(
			     &iter_array, "rsn")) ||
		    ((capa.key_mgmt & (WPA_DRIVER_CAPA_KEY_MGMT_WPA |
				       WPA_DRIVER_CAPA_KEY_MGMT_WPA_PSK)) &&
		     !wpa_dbus_dict_string_array_add_element(
			     &iter_array, "wpa")) ||
		    !wpa_dbus_dict_end_string_array(&iter_dict,
						    &iter_dict_entry,
						    &iter_dict_val,
						    &iter_array))
			goto nomem;
	}

	/***** auth alg */
	if (res < 0) {
		const char *args[] = { "open", "shared", "leap" };

		if (!wpa_dbus_dict_append_string_array(
			    &iter_dict, "AuthAlg", args,
			    ARRAY_SIZE(args)))
			goto nomem;
	} else {
		if (!wpa_dbus_dict_begin_string_array(&iter_dict, "AuthAlg",
						      &iter_dict_entry,
						      &iter_dict_val,
						      &iter_array))
			goto nomem;

		if (((capa.auth & WPA_DRIVER_AUTH_OPEN) &&
		     !wpa_dbus_dict_string_array_add_element(
			     &iter_array, "open")) ||
		    ((capa.auth & WPA_DRIVER_AUTH_SHARED) &&
		     !wpa_dbus_dict_string_array_add_element(
			     &iter_array, "shared")) ||
		    ((capa.auth & WPA_DRIVER_AUTH_LEAP) &&
		     !wpa_dbus_dict_string_array_add_element(
			     &iter_array, "leap")) ||
		    !wpa_dbus_dict_end_string_array(&iter_dict,
						    &iter_dict_entry,
						    &iter_dict_val,
						    &iter_array))
			goto nomem;
	}

	/***** Scan */
	if (!wpa_dbus_dict_append_string_array(&iter_dict, "Scan", scans,
					       ARRAY_SIZE(scans)))
		goto nomem;

	/***** Modes */
	if (!wpa_dbus_dict_begin_string_array(&iter_dict, "Modes",
					      &iter_dict_entry,
					      &iter_dict_val,
					      &iter_array) ||
	    !wpa_dbus_dict_string_array_add_element(
		    &iter_array, "infrastructure") ||
	    (res >= 0 && (capa.flags & WPA_DRIVER_FLAGS_IBSS) &&
	     !wpa_dbus_dict_string_array_add_element(
		     &iter_array, "ad-hoc")) ||
	    (res >= 0 && (capa.flags & WPA_DRIVER_FLAGS_AP) &&
	     !wpa_dbus_dict_string_array_add_element(
		     &iter_array, "ap")) ||
	    (res >= 0 && (capa.flags & WPA_DRIVER_FLAGS_P2P_CAPABLE) &&
	     !wpa_s->conf->p2p_disabled &&
	     !wpa_dbus_dict_string_array_add_element(
		     &iter_array, "p2p")) ||
#ifdef CONFIG_MESH
	    (res >= 0 && (capa.flags & WPA_DRIVER_FLAGS_MESH) &&
	     !wpa_dbus_dict_string_array_add_element(
		     &iter_array, "mesh")) ||
#endif /* CONFIG_MESH */
	    !wpa_dbus_dict_end_string_array(&iter_dict,
					    &iter_dict_entry,
					    &iter_dict_val,
					    &iter_array))
		goto nomem;
	/***** Modes end */

	if (res >= 0) {
		dbus_int32_t max_scan_ssid = capa.max_scan_ssids;

		if (!wpa_dbus_dict_append_int32(&iter_dict, "MaxScanSSID",
						max_scan_ssid))
			goto nomem;
	}

	if (!wpa_dbus_dict_close_write(&variant_iter, &iter_dict) ||
	    !dbus_message_iter_close_container(iter, &variant_iter))
		goto nomem;

	return TRUE;

nomem:
	dbus_set_error_const(error, DBUS_ERROR_NO_MEMORY, "no memory");
	return FALSE;
}