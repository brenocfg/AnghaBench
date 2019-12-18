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
typedef  int u8 ;
struct wpa_supplicant {int drv_flags; TYPE_3__* conf; TYPE_2__* wps; TYPE_1__* global; } ;
struct p2p_data {int dummy; } ;
typedef  int /*<<< orphan*/  r ;
struct TYPE_6__ {int changed_parameters; char* country; int p2p_listen_reg_class; int p2p_listen_channel; int p2p_oper_reg_class; int p2p_oper_channel; int /*<<< orphan*/  p2p_passphrase_len; int /*<<< orphan*/  p2p_no_go_freq; int /*<<< orphan*/  p2p_pref_chan; int /*<<< orphan*/  num_p2p_pref_chan; int /*<<< orphan*/  p2p_intra_bss; scalar_t__ p2p_ssid_postfix; int /*<<< orphan*/ ** wps_vendor_ext; int /*<<< orphan*/  num_sec_device_types; scalar_t__ sec_device_type; int /*<<< orphan*/  serial_number; int /*<<< orphan*/  model_number; int /*<<< orphan*/  model_name; int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  device_type; int /*<<< orphan*/  device_name; } ;
struct TYPE_5__ {int /*<<< orphan*/  uuid; int /*<<< orphan*/  config_methods; } ;
struct TYPE_4__ {struct p2p_data* p2p; } ;

/* Variables and functions */
 int CFG_CHANGED_CONFIG_METHODS ; 
 int CFG_CHANGED_COUNTRY ; 
 int CFG_CHANGED_DEVICE_NAME ; 
 int CFG_CHANGED_DEVICE_TYPE ; 
 int CFG_CHANGED_P2P_INTRA_BSS ; 
 int CFG_CHANGED_P2P_LISTEN_CHANNEL ; 
 int CFG_CHANGED_P2P_OPER_CHANNEL ; 
 int CFG_CHANGED_P2P_PASSPHRASE_LEN ; 
 int CFG_CHANGED_P2P_PREF_CHAN ; 
 int CFG_CHANGED_P2P_SSID_POSTFIX ; 
 int CFG_CHANGED_SEC_DEVICE_TYPE ; 
 int CFG_CHANGED_UUID ; 
 int CFG_CHANGED_VENDOR_EXTENSION ; 
 int CFG_CHANGED_WPS_STRING ; 
 int MAX_WPS_VENDOR_EXT ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int WPA_DRIVER_FLAGS_P2P_CAPABLE ; 
 scalar_t__ os_get_random (int*,int) ; 
 int /*<<< orphan*/  os_strlen (scalar_t__) ; 
 int /*<<< orphan*/  p2p_add_wps_vendor_extension (struct p2p_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2p_remove_wps_vendor_extensions (struct p2p_data*) ; 
 int /*<<< orphan*/  p2p_set_config_methods (struct p2p_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_set_country (struct p2p_data*,char*) ; 
 int /*<<< orphan*/  p2p_set_dev_name (struct p2p_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_set_intra_bss_dist (struct p2p_data*,int /*<<< orphan*/ ) ; 
 int p2p_set_listen_channel (struct p2p_data*,int,int,int) ; 
 int /*<<< orphan*/  p2p_set_manufacturer (struct p2p_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_set_model_name (struct p2p_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_set_model_number (struct p2p_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ p2p_set_no_go_freq (struct p2p_data*,int /*<<< orphan*/ *) ; 
 int p2p_set_oper_channel (struct p2p_data*,int,int,int) ; 
 int /*<<< orphan*/  p2p_set_passphrase_len (struct p2p_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ p2p_set_pref_chan (struct p2p_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_set_pri_dev_type (struct p2p_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_set_sec_dev_types (struct p2p_data*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_set_serial_number (struct p2p_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_set_ssid_postfix (struct p2p_data*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_set_uuid (struct p2p_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

void wpas_p2p_update_config(struct wpa_supplicant *wpa_s)
{
	struct p2p_data *p2p = wpa_s->global->p2p;

	if (p2p == NULL)
		return;

	if (!(wpa_s->drv_flags & WPA_DRIVER_FLAGS_P2P_CAPABLE))
		return;

	if (wpa_s->conf->changed_parameters & CFG_CHANGED_DEVICE_NAME)
		p2p_set_dev_name(p2p, wpa_s->conf->device_name);

	if (wpa_s->conf->changed_parameters & CFG_CHANGED_DEVICE_TYPE)
		p2p_set_pri_dev_type(p2p, wpa_s->conf->device_type);

	if (wpa_s->wps &&
	    (wpa_s->conf->changed_parameters & CFG_CHANGED_CONFIG_METHODS))
		p2p_set_config_methods(p2p, wpa_s->wps->config_methods);

	if (wpa_s->wps && (wpa_s->conf->changed_parameters & CFG_CHANGED_UUID))
		p2p_set_uuid(p2p, wpa_s->wps->uuid);

	if (wpa_s->conf->changed_parameters & CFG_CHANGED_WPS_STRING) {
		p2p_set_manufacturer(p2p, wpa_s->conf->manufacturer);
		p2p_set_model_name(p2p, wpa_s->conf->model_name);
		p2p_set_model_number(p2p, wpa_s->conf->model_number);
		p2p_set_serial_number(p2p, wpa_s->conf->serial_number);
	}

	if (wpa_s->conf->changed_parameters & CFG_CHANGED_SEC_DEVICE_TYPE)
		p2p_set_sec_dev_types(p2p,
				      (void *) wpa_s->conf->sec_device_type,
				      wpa_s->conf->num_sec_device_types);

	if (wpa_s->conf->changed_parameters & CFG_CHANGED_VENDOR_EXTENSION) {
		int i;
		p2p_remove_wps_vendor_extensions(p2p);
		for (i = 0; i < MAX_WPS_VENDOR_EXT; i++) {
			if (wpa_s->conf->wps_vendor_ext[i] == NULL)
				continue;
			p2p_add_wps_vendor_extension(
				p2p, wpa_s->conf->wps_vendor_ext[i]);
		}
	}

	if ((wpa_s->conf->changed_parameters & CFG_CHANGED_COUNTRY) &&
	    wpa_s->conf->country[0] && wpa_s->conf->country[1]) {
		char country[3];
		country[0] = wpa_s->conf->country[0];
		country[1] = wpa_s->conf->country[1];
		country[2] = 0x04;
		p2p_set_country(p2p, country);
	}

	if (wpa_s->conf->changed_parameters & CFG_CHANGED_P2P_SSID_POSTFIX) {
		p2p_set_ssid_postfix(p2p, (u8 *) wpa_s->conf->p2p_ssid_postfix,
				     wpa_s->conf->p2p_ssid_postfix ?
				     os_strlen(wpa_s->conf->p2p_ssid_postfix) :
				     0);
	}

	if (wpa_s->conf->changed_parameters & CFG_CHANGED_P2P_INTRA_BSS)
		p2p_set_intra_bss_dist(p2p, wpa_s->conf->p2p_intra_bss);

	if (wpa_s->conf->changed_parameters & CFG_CHANGED_P2P_LISTEN_CHANNEL) {
		u8 reg_class, channel;
		int ret;
		unsigned int r;
		u8 channel_forced;

		if (wpa_s->conf->p2p_listen_reg_class &&
		    wpa_s->conf->p2p_listen_channel) {
			reg_class = wpa_s->conf->p2p_listen_reg_class;
			channel = wpa_s->conf->p2p_listen_channel;
			channel_forced = 1;
		} else {
			reg_class = 81;
			/*
			 * Pick one of the social channels randomly as the
			 * listen channel.
			 */
			if (os_get_random((u8 *) &r, sizeof(r)) < 0)
				channel = 1;
			else
				channel = 1 + (r % 3) * 5;
			channel_forced = 0;
		}
		ret = p2p_set_listen_channel(p2p, reg_class, channel,
					     channel_forced);
		if (ret)
			wpa_printf(MSG_ERROR, "P2P: Own listen channel update "
				   "failed: %d", ret);
	}
	if (wpa_s->conf->changed_parameters & CFG_CHANGED_P2P_OPER_CHANNEL) {
		u8 op_reg_class, op_channel, cfg_op_channel;
		int ret = 0;
		unsigned int r;
		if (wpa_s->conf->p2p_oper_reg_class &&
		    wpa_s->conf->p2p_oper_channel) {
			op_reg_class = wpa_s->conf->p2p_oper_reg_class;
			op_channel = wpa_s->conf->p2p_oper_channel;
			cfg_op_channel = 1;
		} else {
			op_reg_class = 81;
			/*
			 * Use random operation channel from (1, 6, 11)
			 *if no other preference is indicated.
			 */
			if (os_get_random((u8 *) &r, sizeof(r)) < 0)
				op_channel = 1;
			else
				op_channel = 1 + (r % 3) * 5;
			cfg_op_channel = 0;
		}
		ret = p2p_set_oper_channel(p2p, op_reg_class, op_channel,
					   cfg_op_channel);
		if (ret)
			wpa_printf(MSG_ERROR, "P2P: Own oper channel update "
				   "failed: %d", ret);
	}

	if (wpa_s->conf->changed_parameters & CFG_CHANGED_P2P_PREF_CHAN) {
		if (p2p_set_pref_chan(p2p, wpa_s->conf->num_p2p_pref_chan,
				      wpa_s->conf->p2p_pref_chan) < 0) {
			wpa_printf(MSG_ERROR, "P2P: Preferred channel list "
				   "update failed");
		}

		if (p2p_set_no_go_freq(p2p, &wpa_s->conf->p2p_no_go_freq) < 0) {
			wpa_printf(MSG_ERROR, "P2P: No GO channel list "
				   "update failed");
		}
	}

	if (wpa_s->conf->changed_parameters & CFG_CHANGED_P2P_PASSPHRASE_LEN)
		p2p_set_passphrase_len(p2p, wpa_s->conf->p2p_passphrase_len);
}