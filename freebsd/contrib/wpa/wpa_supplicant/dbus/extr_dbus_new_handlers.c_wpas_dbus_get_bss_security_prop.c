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
struct wpa_ie_data {int key_mgmt; int group_cipher; int const pairwise_cipher; scalar_t__ proto; int mgmt_group_cipher; } ;
struct wpa_dbus_property_desc {int dummy; } ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  DBUS_TYPE_VARIANT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
#define  WPA_CIPHER_AES_128_CMAC 135 
#define  WPA_CIPHER_CCMP 134 
#define  WPA_CIPHER_CCMP_256 133 
#define  WPA_CIPHER_GCMP 132 
#define  WPA_CIPHER_GCMP_256 131 
#define  WPA_CIPHER_TKIP 130 
#define  WPA_CIPHER_WEP104 129 
#define  WPA_CIPHER_WEP40 128 
 int WPA_KEY_MGMT_FILS_SHA256 ; 
 int WPA_KEY_MGMT_FILS_SHA384 ; 
 int WPA_KEY_MGMT_FT_FILS_SHA256 ; 
 int WPA_KEY_MGMT_FT_FILS_SHA384 ; 
 int WPA_KEY_MGMT_FT_IEEE8021X ; 
 int WPA_KEY_MGMT_FT_PSK ; 
 int WPA_KEY_MGMT_FT_SAE ; 
 int WPA_KEY_MGMT_IEEE8021X ; 
 int WPA_KEY_MGMT_IEEE8021X_SHA256 ; 
 int WPA_KEY_MGMT_IEEE8021X_SUITE_B ; 
 int WPA_KEY_MGMT_IEEE8021X_SUITE_B_192 ; 
 int WPA_KEY_MGMT_NONE ; 
 int WPA_KEY_MGMT_PSK ; 
 int WPA_KEY_MGMT_PSK_SHA256 ; 
 int WPA_KEY_MGMT_SAE ; 
 scalar_t__ WPA_PROTO_RSN ; 
 int /*<<< orphan*/  dbus_message_iter_close_container (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_open_container (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_set_error_const (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_dbus_dict_append_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  wpa_dbus_dict_append_string_array (int /*<<< orphan*/ *,char*,char const**,int) ; 
 int /*<<< orphan*/  wpa_dbus_dict_close_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_dbus_dict_open_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static dbus_bool_t wpas_dbus_get_bss_security_prop(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, struct wpa_ie_data *ie_data, DBusError *error)
{
	DBusMessageIter iter_dict, variant_iter;
	const char *group;
	const char *pairwise[5]; /* max 5 pairwise ciphers is supported */
	const char *key_mgmt[15]; /* max 15 key managements may be supported */
	int n;

	if (!dbus_message_iter_open_container(iter, DBUS_TYPE_VARIANT,
					      "a{sv}", &variant_iter))
		goto nomem;

	if (!wpa_dbus_dict_open_write(&variant_iter, &iter_dict))
		goto nomem;

	/*
	 * KeyMgmt
	 *
	 * When adding a new entry here, please take care to extend key_mgmt[]
	 * and keep documentation in doc/dbus.doxygen up to date.
	 */
	n = 0;
	if (ie_data->key_mgmt & WPA_KEY_MGMT_PSK)
		key_mgmt[n++] = "wpa-psk";
	if (ie_data->key_mgmt & WPA_KEY_MGMT_FT_PSK)
		key_mgmt[n++] = "wpa-ft-psk";
	if (ie_data->key_mgmt & WPA_KEY_MGMT_PSK_SHA256)
		key_mgmt[n++] = "wpa-psk-sha256";
	if (ie_data->key_mgmt & WPA_KEY_MGMT_IEEE8021X)
		key_mgmt[n++] = "wpa-eap";
	if (ie_data->key_mgmt & WPA_KEY_MGMT_FT_IEEE8021X)
		key_mgmt[n++] = "wpa-ft-eap";
	if (ie_data->key_mgmt & WPA_KEY_MGMT_IEEE8021X_SHA256)
		key_mgmt[n++] = "wpa-eap-sha256";
#ifdef CONFIG_SUITEB
	if (ie_data->key_mgmt & WPA_KEY_MGMT_IEEE8021X_SUITE_B)
		key_mgmt[n++] = "wpa-eap-suite-b";
#endif /* CONFIG_SUITEB */
#ifdef CONFIG_SUITEB192
	if (ie_data->key_mgmt & WPA_KEY_MGMT_IEEE8021X_SUITE_B_192)
		key_mgmt[n++] = "wpa-eap-suite-b-192";
#endif /* CONFIG_SUITEB192 */
#ifdef CONFIG_FILS
	if (ie_data->key_mgmt & WPA_KEY_MGMT_FILS_SHA256)
		key_mgmt[n++] = "wpa-fils-sha256";
	if (ie_data->key_mgmt & WPA_KEY_MGMT_FILS_SHA384)
		key_mgmt[n++] = "wpa-fils-sha384";
	if (ie_data->key_mgmt & WPA_KEY_MGMT_FT_FILS_SHA256)
		key_mgmt[n++] = "wpa-ft-fils-sha256";
	if (ie_data->key_mgmt & WPA_KEY_MGMT_FT_FILS_SHA384)
		key_mgmt[n++] = "wpa-ft-fils-sha384";
#endif /* CONFIG_FILS */
#ifdef CONFIG_SAE
	if (ie_data->key_mgmt & WPA_KEY_MGMT_SAE)
		key_mgmt[n++] = "sae";
	if (ie_data->key_mgmt & WPA_KEY_MGMT_FT_SAE)
		key_mgmt[n++] = "ft-sae";
#endif /* CONFIG_SAE */
	if (ie_data->key_mgmt & WPA_KEY_MGMT_NONE)
		key_mgmt[n++] = "wpa-none";

	if (!wpa_dbus_dict_append_string_array(&iter_dict, "KeyMgmt",
					       key_mgmt, n))
		goto nomem;

	/* Group */
	switch (ie_data->group_cipher) {
	case WPA_CIPHER_WEP40:
		group = "wep40";
		break;
	case WPA_CIPHER_TKIP:
		group = "tkip";
		break;
	case WPA_CIPHER_CCMP:
		group = "ccmp";
		break;
	case WPA_CIPHER_GCMP:
		group = "gcmp";
		break;
	case WPA_CIPHER_WEP104:
		group = "wep104";
		break;
	case WPA_CIPHER_CCMP_256:
		group = "ccmp-256";
		break;
	case WPA_CIPHER_GCMP_256:
		group = "gcmp-256";
		break;
	default:
		group = "";
		break;
	}

	if (!wpa_dbus_dict_append_string(&iter_dict, "Group", group))
		goto nomem;

	/* Pairwise */
	n = 0;
	if (ie_data->pairwise_cipher & WPA_CIPHER_TKIP)
		pairwise[n++] = "tkip";
	if (ie_data->pairwise_cipher & WPA_CIPHER_CCMP)
		pairwise[n++] = "ccmp";
	if (ie_data->pairwise_cipher & WPA_CIPHER_GCMP)
		pairwise[n++] = "gcmp";
	if (ie_data->pairwise_cipher & WPA_CIPHER_CCMP_256)
		pairwise[n++] = "ccmp-256";
	if (ie_data->pairwise_cipher & WPA_CIPHER_GCMP_256)
		pairwise[n++] = "gcmp-256";

	if (!wpa_dbus_dict_append_string_array(&iter_dict, "Pairwise",
					       pairwise, n))
		goto nomem;

	/* Management group (RSN only) */
	if (ie_data->proto == WPA_PROTO_RSN) {
		switch (ie_data->mgmt_group_cipher) {
#ifdef CONFIG_IEEE80211W
		case WPA_CIPHER_AES_128_CMAC:
			group = "aes128cmac";
			break;
#endif /* CONFIG_IEEE80211W */
		default:
			group = "";
			break;
		}

		if (!wpa_dbus_dict_append_string(&iter_dict, "MgmtGroup",
						 group))
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