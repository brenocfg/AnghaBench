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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct wps_parse_attr {int oob_dev_password_len; int manufacturer_len; int model_name_len; int model_number_len; int serial_number_len; int dev_name_len; int public_key_len; int encr_settings_len; size_t num_cred; int* cred_len; int ssid_len; int network_key_len; size_t num_req_dev_type; int sec_dev_type_list_len; int /*<<< orphan*/  const* ap_channel; int /*<<< orphan*/  const* sec_dev_type_list; int /*<<< orphan*/  const** req_dev_type; int /*<<< orphan*/  const* ap_setup_locked; int /*<<< orphan*/  const* network_key; int /*<<< orphan*/  const* ssid; int /*<<< orphan*/  const** cred; int /*<<< orphan*/  const* encr_settings; int /*<<< orphan*/  const* public_key; int /*<<< orphan*/  const* dev_name; int /*<<< orphan*/  const* serial_number; int /*<<< orphan*/  const* model_number; int /*<<< orphan*/  const* model_name; int /*<<< orphan*/  const* manufacturer; int /*<<< orphan*/  const* response_type; int /*<<< orphan*/  const* request_type; int /*<<< orphan*/  const* selected_registrar; int /*<<< orphan*/  const* mac_addr; int /*<<< orphan*/  const* network_key_idx; int /*<<< orphan*/  const* network_idx; int /*<<< orphan*/  const* encr_type; int /*<<< orphan*/  const* auth_type; int /*<<< orphan*/  const* key_wrap_auth; int /*<<< orphan*/  const* e_snonce2; int /*<<< orphan*/  const* e_snonce1; int /*<<< orphan*/  const* r_snonce2; int /*<<< orphan*/  const* r_snonce1; int /*<<< orphan*/  const* e_hash2; int /*<<< orphan*/  const* e_hash1; int /*<<< orphan*/  const* r_hash2; int /*<<< orphan*/  const* r_hash1; int /*<<< orphan*/  const* authenticator; int /*<<< orphan*/  const* wps_state; int /*<<< orphan*/  const* os_version; int /*<<< orphan*/  const* oob_dev_password; int /*<<< orphan*/  const* dev_password_id; int /*<<< orphan*/  const* config_error; int /*<<< orphan*/  const* assoc_state; int /*<<< orphan*/  const* rf_bands; int /*<<< orphan*/  const* primary_dev_type; int /*<<< orphan*/  const* sel_reg_config_methods; int /*<<< orphan*/  const* config_methods; int /*<<< orphan*/  const* conn_type_flags; int /*<<< orphan*/  const* encr_type_flags; int /*<<< orphan*/  const* auth_type_flags; int /*<<< orphan*/  const* uuid_r; int /*<<< orphan*/  const* uuid_e; int /*<<< orphan*/  const* registrar_nonce; int /*<<< orphan*/  const* enrollee_nonce; int /*<<< orphan*/  const* msg_type; int /*<<< orphan*/  const* version; } ;

/* Variables and functions */
#define  ATTR_AP_CHANNEL 179 
#define  ATTR_AP_SETUP_LOCKED 178 
#define  ATTR_ASSOC_STATE 177 
#define  ATTR_AUTHENTICATOR 176 
#define  ATTR_AUTH_TYPE 175 
#define  ATTR_AUTH_TYPE_FLAGS 174 
#define  ATTR_CONFIG_ERROR 173 
#define  ATTR_CONFIG_METHODS 172 
#define  ATTR_CONN_TYPE_FLAGS 171 
#define  ATTR_CRED 170 
#define  ATTR_DEV_NAME 169 
#define  ATTR_DEV_PASSWORD_ID 168 
#define  ATTR_ENCR_SETTINGS 167 
#define  ATTR_ENCR_TYPE 166 
#define  ATTR_ENCR_TYPE_FLAGS 165 
#define  ATTR_ENROLLEE_NONCE 164 
#define  ATTR_E_HASH1 163 
#define  ATTR_E_HASH2 162 
#define  ATTR_E_SNONCE1 161 
#define  ATTR_E_SNONCE2 160 
#define  ATTR_KEY_WRAP_AUTH 159 
#define  ATTR_MAC_ADDR 158 
#define  ATTR_MANUFACTURER 157 
#define  ATTR_MODEL_NAME 156 
#define  ATTR_MODEL_NUMBER 155 
#define  ATTR_MSG_TYPE 154 
#define  ATTR_NETWORK_INDEX 153 
#define  ATTR_NETWORK_KEY 152 
#define  ATTR_NETWORK_KEY_INDEX 151 
#define  ATTR_OOB_DEVICE_PASSWORD 150 
#define  ATTR_OS_VERSION 149 
#define  ATTR_PRIMARY_DEV_TYPE 148 
#define  ATTR_PUBLIC_KEY 147 
#define  ATTR_REGISTRAR_NONCE 146 
#define  ATTR_REQUESTED_DEV_TYPE 145 
#define  ATTR_REQUEST_TYPE 144 
#define  ATTR_RESPONSE_TYPE 143 
#define  ATTR_RF_BANDS 142 
#define  ATTR_R_HASH1 141 
#define  ATTR_R_HASH2 140 
#define  ATTR_R_SNONCE1 139 
#define  ATTR_R_SNONCE2 138 
#define  ATTR_SECONDARY_DEV_TYPE_LIST 137 
#define  ATTR_SELECTED_REGISTRAR 136 
#define  ATTR_SELECTED_REGISTRAR_CONFIG_METHODS 135 
#define  ATTR_SERIAL_NUMBER 134 
#define  ATTR_SSID 133 
#define  ATTR_UUID_E 132 
#define  ATTR_UUID_R 131 
#define  ATTR_VENDOR_EXT 130 
#define  ATTR_VERSION 129 
#define  ATTR_WPS_STATE 128 
 int /*<<< orphan*/  DEV_PW_NFC_CONNECTION_HANDOVER ; 
 int ETH_ALEN ; 
 size_t MAX_CRED_COUNT ; 
 size_t MAX_REQ_DEV_TYPE_COUNT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int SSID_MAX_LEN ; 
 int /*<<< orphan*/  WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 int WPS_AUTHENTICATOR_LEN ; 
 int WPS_DEV_NAME_MAX_LEN ; 
 int WPS_DEV_TYPE_LEN ; 
 int WPS_HASH_LEN ; 
 int WPS_KWA_LEN ; 
 int WPS_MANUFACTURER_MAX_LEN ; 
 int WPS_MODEL_NAME_MAX_LEN ; 
 int WPS_MODEL_NUMBER_MAX_LEN ; 
 int WPS_NONCE_LEN ; 
 int WPS_OOB_DEVICE_PASSWORD_LEN ; 
 int WPS_OOB_DEVICE_PASSWORD_MIN_LEN ; 
 int /*<<< orphan*/  WPS_OOB_PUBKEY_HASH_LEN ; 
 int WPS_SECRET_NONCE_LEN ; 
 int WPS_SEC_DEV_TYPE_MAX_LEN ; 
 int WPS_SERIAL_NUMBER_MAX_LEN ; 
 int WPS_UUID_LEN ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  wps_parse_vendor_ext (struct wps_parse_attr*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int wps_set_attr(struct wps_parse_attr *attr, u16 type,
			const u8 *pos, u16 len)
{
	switch (type) {
	case ATTR_VERSION:
		if (len != 1) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Version length %u",
				   len);
			return -1;
		}
		attr->version = pos;
		break;
	case ATTR_MSG_TYPE:
		if (len != 1) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Message Type "
				   "length %u", len);
			return -1;
		}
		attr->msg_type = pos;
		break;
	case ATTR_ENROLLEE_NONCE:
		if (len != WPS_NONCE_LEN) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Enrollee Nonce "
				   "length %u", len);
			return -1;
		}
		attr->enrollee_nonce = pos;
		break;
	case ATTR_REGISTRAR_NONCE:
		if (len != WPS_NONCE_LEN) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Registrar Nonce "
				   "length %u", len);
			return -1;
		}
		attr->registrar_nonce = pos;
		break;
	case ATTR_UUID_E:
		if (len != WPS_UUID_LEN) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid UUID-E length %u",
				   len);
			return -1;
		}
		attr->uuid_e = pos;
		break;
	case ATTR_UUID_R:
		if (len != WPS_UUID_LEN) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid UUID-R length %u",
				   len);
			return -1;
		}
		attr->uuid_r = pos;
		break;
	case ATTR_AUTH_TYPE_FLAGS:
		if (len != 2) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Authentication "
				   "Type Flags length %u", len);
			return -1;
		}
		attr->auth_type_flags = pos;
		break;
	case ATTR_ENCR_TYPE_FLAGS:
		if (len != 2) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Encryption Type "
				   "Flags length %u", len);
			return -1;
		}
		attr->encr_type_flags = pos;
		break;
	case ATTR_CONN_TYPE_FLAGS:
		if (len != 1) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Connection Type "
				   "Flags length %u", len);
			return -1;
		}
		attr->conn_type_flags = pos;
		break;
	case ATTR_CONFIG_METHODS:
		if (len != 2) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Config Methods "
				   "length %u", len);
			return -1;
		}
		attr->config_methods = pos;
		break;
	case ATTR_SELECTED_REGISTRAR_CONFIG_METHODS:
		if (len != 2) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Selected "
				   "Registrar Config Methods length %u", len);
			return -1;
		}
		attr->sel_reg_config_methods = pos;
		break;
	case ATTR_PRIMARY_DEV_TYPE:
		if (len != WPS_DEV_TYPE_LEN) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Primary Device "
				   "Type length %u", len);
			return -1;
		}
		attr->primary_dev_type = pos;
		break;
	case ATTR_RF_BANDS:
		if (len != 1) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid RF Bands length "
				   "%u", len);
			return -1;
		}
		attr->rf_bands = pos;
		break;
	case ATTR_ASSOC_STATE:
		if (len != 2) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Association State "
				   "length %u", len);
			return -1;
		}
		attr->assoc_state = pos;
		break;
	case ATTR_CONFIG_ERROR:
		if (len != 2) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Configuration "
				   "Error length %u", len);
			return -1;
		}
		attr->config_error = pos;
		break;
	case ATTR_DEV_PASSWORD_ID:
		if (len != 2) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Device Password "
				   "ID length %u", len);
			return -1;
		}
		attr->dev_password_id = pos;
		break;
	case ATTR_OOB_DEVICE_PASSWORD:
		if (len < WPS_OOB_PUBKEY_HASH_LEN + 2 ||
		    len > WPS_OOB_PUBKEY_HASH_LEN + 2 +
		    WPS_OOB_DEVICE_PASSWORD_LEN ||
		    (len < WPS_OOB_PUBKEY_HASH_LEN + 2 +
		     WPS_OOB_DEVICE_PASSWORD_MIN_LEN &&
		     WPA_GET_BE16(pos + WPS_OOB_PUBKEY_HASH_LEN) !=
		     DEV_PW_NFC_CONNECTION_HANDOVER)) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid OOB Device "
				   "Password length %u", len);
			return -1;
		}
		attr->oob_dev_password = pos;
		attr->oob_dev_password_len = len;
		break;
	case ATTR_OS_VERSION:
		if (len != 4) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid OS Version length "
				   "%u", len);
			return -1;
		}
		attr->os_version = pos;
		break;
	case ATTR_WPS_STATE:
		if (len != 1) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Wi-Fi Protected "
				   "Setup State length %u", len);
			return -1;
		}
		attr->wps_state = pos;
		break;
	case ATTR_AUTHENTICATOR:
		if (len != WPS_AUTHENTICATOR_LEN) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Authenticator "
				   "length %u", len);
			return -1;
		}
		attr->authenticator = pos;
		break;
	case ATTR_R_HASH1:
		if (len != WPS_HASH_LEN) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid R-Hash1 length %u",
				   len);
			return -1;
		}
		attr->r_hash1 = pos;
		break;
	case ATTR_R_HASH2:
		if (len != WPS_HASH_LEN) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid R-Hash2 length %u",
				   len);
			return -1;
		}
		attr->r_hash2 = pos;
		break;
	case ATTR_E_HASH1:
		if (len != WPS_HASH_LEN) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid E-Hash1 length %u",
				   len);
			return -1;
		}
		attr->e_hash1 = pos;
		break;
	case ATTR_E_HASH2:
		if (len != WPS_HASH_LEN) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid E-Hash2 length %u",
				   len);
			return -1;
		}
		attr->e_hash2 = pos;
		break;
	case ATTR_R_SNONCE1:
		if (len != WPS_SECRET_NONCE_LEN) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid R-SNonce1 length "
				   "%u", len);
			return -1;
		}
		attr->r_snonce1 = pos;
		break;
	case ATTR_R_SNONCE2:
		if (len != WPS_SECRET_NONCE_LEN) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid R-SNonce2 length "
				   "%u", len);
			return -1;
		}
		attr->r_snonce2 = pos;
		break;
	case ATTR_E_SNONCE1:
		if (len != WPS_SECRET_NONCE_LEN) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid E-SNonce1 length "
				   "%u", len);
			return -1;
		}
		attr->e_snonce1 = pos;
		break;
	case ATTR_E_SNONCE2:
		if (len != WPS_SECRET_NONCE_LEN) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid E-SNonce2 length "
				   "%u", len);
			return -1;
		}
		attr->e_snonce2 = pos;
		break;
	case ATTR_KEY_WRAP_AUTH:
		if (len != WPS_KWA_LEN) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Key Wrap "
				   "Authenticator length %u", len);
			return -1;
		}
		attr->key_wrap_auth = pos;
		break;
	case ATTR_AUTH_TYPE:
		if (len != 2) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Authentication "
				   "Type length %u", len);
			return -1;
		}
		attr->auth_type = pos;
		break;
	case ATTR_ENCR_TYPE:
		if (len != 2) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Encryption "
				   "Type length %u", len);
			return -1;
		}
		attr->encr_type = pos;
		break;
	case ATTR_NETWORK_INDEX:
		if (len != 1) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Network Index "
				   "length %u", len);
			return -1;
		}
		attr->network_idx = pos;
		break;
	case ATTR_NETWORK_KEY_INDEX:
		if (len != 1) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Network Key Index "
				   "length %u", len);
			return -1;
		}
		attr->network_key_idx = pos;
		break;
	case ATTR_MAC_ADDR:
		if (len != ETH_ALEN) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid MAC Address "
				   "length %u", len);
			return -1;
		}
		attr->mac_addr = pos;
		break;
	case ATTR_SELECTED_REGISTRAR:
		if (len != 1) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Selected Registrar"
				   " length %u", len);
			return -1;
		}
		attr->selected_registrar = pos;
		break;
	case ATTR_REQUEST_TYPE:
		if (len != 1) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Request Type "
				   "length %u", len);
			return -1;
		}
		attr->request_type = pos;
		break;
	case ATTR_RESPONSE_TYPE:
		if (len != 1) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Response Type "
				   "length %u", len);
			return -1;
		}
		attr->response_type = pos;
		break;
	case ATTR_MANUFACTURER:
		attr->manufacturer = pos;
		if (len > WPS_MANUFACTURER_MAX_LEN)
			attr->manufacturer_len = WPS_MANUFACTURER_MAX_LEN;
		else
			attr->manufacturer_len = len;
		break;
	case ATTR_MODEL_NAME:
		attr->model_name = pos;
		if (len > WPS_MODEL_NAME_MAX_LEN)
			attr->model_name_len = WPS_MODEL_NAME_MAX_LEN;
		else
			attr->model_name_len = len;
		break;
	case ATTR_MODEL_NUMBER:
		attr->model_number = pos;
		if (len > WPS_MODEL_NUMBER_MAX_LEN)
			attr->model_number_len = WPS_MODEL_NUMBER_MAX_LEN;
		else
			attr->model_number_len = len;
		break;
	case ATTR_SERIAL_NUMBER:
		attr->serial_number = pos;
		if (len > WPS_SERIAL_NUMBER_MAX_LEN)
			attr->serial_number_len = WPS_SERIAL_NUMBER_MAX_LEN;
		else
			attr->serial_number_len = len;
		break;
	case ATTR_DEV_NAME:
		if (len > WPS_DEV_NAME_MAX_LEN) {
			wpa_printf(MSG_DEBUG,
				   "WPS: Ignore too long Device Name (len=%u)",
				   len);
			break;
		}
		attr->dev_name = pos;
		attr->dev_name_len = len;
		break;
	case ATTR_PUBLIC_KEY:
		/*
		 * The Public Key attribute is supposed to be exactly 192 bytes
		 * in length. Allow couple of bytes shorter one to try to
		 * interoperate with implementations that do not use proper
		 * zero-padding.
		 */
		if (len < 190 || len > 192) {
			wpa_printf(MSG_DEBUG,
				   "WPS: Ignore Public Key with unexpected length %u",
				   len);
			break;
		}
		attr->public_key = pos;
		attr->public_key_len = len;
		break;
	case ATTR_ENCR_SETTINGS:
		attr->encr_settings = pos;
		attr->encr_settings_len = len;
		break;
	case ATTR_CRED:
		if (attr->num_cred >= MAX_CRED_COUNT) {
			wpa_printf(MSG_DEBUG, "WPS: Skipped Credential "
				   "attribute (max %d credentials)",
				   MAX_CRED_COUNT);
			break;
		}
		attr->cred[attr->num_cred] = pos;
		attr->cred_len[attr->num_cred] = len;
		attr->num_cred++;
		break;
	case ATTR_SSID:
		if (len > SSID_MAX_LEN) {
			wpa_printf(MSG_DEBUG,
				   "WPS: Ignore too long SSID (len=%u)", len);
			break;
		}
		attr->ssid = pos;
		attr->ssid_len = len;
		break;
	case ATTR_NETWORK_KEY:
		attr->network_key = pos;
		attr->network_key_len = len;
		break;
	case ATTR_AP_SETUP_LOCKED:
		if (len != 1) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid AP Setup Locked "
				   "length %u", len);
			return -1;
		}
		attr->ap_setup_locked = pos;
		break;
	case ATTR_REQUESTED_DEV_TYPE:
		if (len != WPS_DEV_TYPE_LEN) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Requested Device "
				   "Type length %u", len);
			return -1;
		}
		if (attr->num_req_dev_type >= MAX_REQ_DEV_TYPE_COUNT) {
			wpa_printf(MSG_DEBUG, "WPS: Skipped Requested Device "
				   "Type attribute (max %u types)",
				   MAX_REQ_DEV_TYPE_COUNT);
			break;
		}
		attr->req_dev_type[attr->num_req_dev_type] = pos;
		attr->num_req_dev_type++;
		break;
	case ATTR_SECONDARY_DEV_TYPE_LIST:
		if (len > WPS_SEC_DEV_TYPE_MAX_LEN ||
		    (len % WPS_DEV_TYPE_LEN) > 0) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Secondary Device "
				   "Type length %u", len);
			return -1;
		}
		attr->sec_dev_type_list = pos;
		attr->sec_dev_type_list_len = len;
		break;
	case ATTR_VENDOR_EXT:
		if (wps_parse_vendor_ext(attr, pos, len) < 0)
			return -1;
		break;
	case ATTR_AP_CHANNEL:
		if (len != 2) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid AP Channel "
				   "length %u", len);
			return -1;
		}
		attr->ap_channel = pos;
		break;
	default:
		wpa_printf(MSG_DEBUG, "WPS: Unsupported attribute type 0x%x "
			   "len=%u", type, len);
		break;
	}

	return 0;
}