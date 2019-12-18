#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wps_parse_attr {int /*<<< orphan*/ * request_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  mac_addr; } ;
struct wps_data {scalar_t__ dev_pw_id; int dev_password_len; scalar_t__ alt_dev_pw_id; int alt_dev_password_len; int peer_pubkey_hash_set; int /*<<< orphan*/  multi_ap_backhaul_sta; int /*<<< orphan*/  peer_pubkey_hash; int /*<<< orphan*/  pbc_in_m1; int /*<<< orphan*/  use_psk_key; int /*<<< orphan*/  p2p_dev_addr; TYPE_3__ peer_dev; int /*<<< orphan*/ * dev_password; int /*<<< orphan*/ * new_ap_settings; int /*<<< orphan*/  request_type; scalar_t__ registrar; int /*<<< orphan*/  state; scalar_t__ pbc; int /*<<< orphan*/ * alt_dev_password; int /*<<< orphan*/  uuid_e; int /*<<< orphan*/  mac_addr_e; int /*<<< orphan*/  uuid_r; TYPE_2__* wps; } ;
struct wps_config {scalar_t__ dev_pw_id; int pin_len; int /*<<< orphan*/  multi_ap_backhaul_sta; int /*<<< orphan*/  peer_pubkey_hash; int /*<<< orphan*/  pbc_in_m1; int /*<<< orphan*/  use_psk_key; int /*<<< orphan*/  p2p_dev_addr; int /*<<< orphan*/  peer_addr; int /*<<< orphan*/ * new_ap_settings; scalar_t__ assoc_wps_ie; scalar_t__ pbc; TYPE_2__* wps; scalar_t__ registrar; int /*<<< orphan*/ * pin; } ;
struct TYPE_4__ {int /*<<< orphan*/  mac_addr; } ;
struct TYPE_5__ {scalar_t__ ap_nfc_dev_pw_id; int /*<<< orphan*/  ap_nfc_dev_pw; scalar_t__ ap; int /*<<< orphan*/  uuid; TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ DEV_PW_NFC_CONNECTION_HANDOVER ; 
 scalar_t__ DEV_PW_PUSHBUTTON ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  RECV_M1 ; 
 int /*<<< orphan*/  SEND_M1 ; 
 int /*<<< orphan*/  WPS_OOB_PUBKEY_HASH_LEN ; 
 int /*<<< orphan*/  WPS_UUID_LEN ; 
 int /*<<< orphan*/  bin_clear_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_free (struct wps_data*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* os_memdup (int /*<<< orphan*/ *,int) ; 
 scalar_t__ os_strdup (char*) ; 
 struct wps_data* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * wpabuf_head (int /*<<< orphan*/ ) ; 
 int wpabuf_len (int /*<<< orphan*/ ) ; 
 scalar_t__ wps_parse_msg (scalar_t__,struct wps_parse_attr*) ; 

struct wps_data * wps_init(const struct wps_config *cfg)
{
	struct wps_data *data = os_zalloc(sizeof(*data));
	if (data == NULL)
		return NULL;
	data->wps = cfg->wps;
	data->registrar = cfg->registrar;
	if (cfg->registrar) {
		os_memcpy(data->uuid_r, cfg->wps->uuid, WPS_UUID_LEN);
	} else {
		os_memcpy(data->mac_addr_e, cfg->wps->dev.mac_addr, ETH_ALEN);
		os_memcpy(data->uuid_e, cfg->wps->uuid, WPS_UUID_LEN);
	}
	if (cfg->pin) {
		data->dev_pw_id = cfg->dev_pw_id;
		data->dev_password = os_memdup(cfg->pin, cfg->pin_len);
		if (data->dev_password == NULL) {
			os_free(data);
			return NULL;
		}
		data->dev_password_len = cfg->pin_len;
		wpa_hexdump_key(MSG_DEBUG, "WPS: AP PIN dev_password",
				data->dev_password, data->dev_password_len);
	}

#ifdef CONFIG_WPS_NFC
	if (cfg->pin == NULL &&
	    cfg->dev_pw_id == DEV_PW_NFC_CONNECTION_HANDOVER)
		data->dev_pw_id = cfg->dev_pw_id;

	if (cfg->wps->ap && !cfg->registrar && cfg->wps->ap_nfc_dev_pw_id) {
		/* Keep AP PIN as alternative Device Password */
		data->alt_dev_pw_id = data->dev_pw_id;
		data->alt_dev_password = data->dev_password;
		data->alt_dev_password_len = data->dev_password_len;

		data->dev_pw_id = cfg->wps->ap_nfc_dev_pw_id;
		data->dev_password =
			os_memdup(wpabuf_head(cfg->wps->ap_nfc_dev_pw),
				  wpabuf_len(cfg->wps->ap_nfc_dev_pw));
		if (data->dev_password == NULL) {
			os_free(data);
			return NULL;
		}
		data->dev_password_len = wpabuf_len(cfg->wps->ap_nfc_dev_pw);
		wpa_hexdump_key(MSG_DEBUG, "WPS: NFC dev_password",
			    data->dev_password, data->dev_password_len);
	}
#endif /* CONFIG_WPS_NFC */

	data->pbc = cfg->pbc;
	if (cfg->pbc) {
		/* Use special PIN '00000000' for PBC */
		data->dev_pw_id = DEV_PW_PUSHBUTTON;
		bin_clear_free(data->dev_password, data->dev_password_len);
		data->dev_password = (u8 *) os_strdup("00000000");
		if (data->dev_password == NULL) {
			os_free(data);
			return NULL;
		}
		data->dev_password_len = 8;
	}

	data->state = data->registrar ? RECV_M1 : SEND_M1;

	if (cfg->assoc_wps_ie) {
		struct wps_parse_attr attr;
		wpa_hexdump_buf(MSG_DEBUG, "WPS: WPS IE from (Re)AssocReq",
				cfg->assoc_wps_ie);
		if (wps_parse_msg(cfg->assoc_wps_ie, &attr) < 0) {
			wpa_printf(MSG_DEBUG, "WPS: Failed to parse WPS IE "
				   "from (Re)AssocReq");
		} else if (attr.request_type == NULL) {
			wpa_printf(MSG_DEBUG, "WPS: No Request Type attribute "
				   "in (Re)AssocReq WPS IE");
		} else {
			wpa_printf(MSG_DEBUG, "WPS: Request Type (from WPS IE "
				   "in (Re)AssocReq WPS IE): %d",
				   *attr.request_type);
			data->request_type = *attr.request_type;
		}
	}

	if (cfg->new_ap_settings) {
		data->new_ap_settings =
			os_memdup(cfg->new_ap_settings,
				  sizeof(*data->new_ap_settings));
		if (data->new_ap_settings == NULL) {
			bin_clear_free(data->dev_password,
				       data->dev_password_len);
			os_free(data);
			return NULL;
		}
	}

	if (cfg->peer_addr)
		os_memcpy(data->peer_dev.mac_addr, cfg->peer_addr, ETH_ALEN);
	if (cfg->p2p_dev_addr)
		os_memcpy(data->p2p_dev_addr, cfg->p2p_dev_addr, ETH_ALEN);

	data->use_psk_key = cfg->use_psk_key;
	data->pbc_in_m1 = cfg->pbc_in_m1;

	if (cfg->peer_pubkey_hash) {
		os_memcpy(data->peer_pubkey_hash, cfg->peer_pubkey_hash,
			  WPS_OOB_PUBKEY_HASH_LEN);
		data->peer_pubkey_hash_set = 1;
	}

	data->multi_ap_backhaul_sta = cfg->multi_ap_backhaul_sta;

	return data;
}