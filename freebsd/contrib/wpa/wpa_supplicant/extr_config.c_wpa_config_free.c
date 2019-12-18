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
struct wpa_ssid {struct wpa_ssid* next; } ;
struct wpa_cred {struct wpa_cred* next; } ;
struct TYPE_2__ {struct wpa_config* range; } ;
struct wpa_config {struct wpa_config* non_pref_chan; struct wpa_config* sched_scan_plans; struct wpa_config* fst_group_id; struct wpa_config* wowlan_triggers; struct wpa_config* bgscan; struct wpa_config* osu_dir; int /*<<< orphan*/  ap_vendor_elements; struct wpa_config* sae_groups; struct wpa_config* ext_password_backend; int /*<<< orphan*/  wps_nfc_dev_pw; int /*<<< orphan*/  wps_nfc_dh_privkey; int /*<<< orphan*/  wps_nfc_dh_pubkey; struct wpa_config* freq_list; struct wpa_config* autoscan; TYPE_1__ p2p_no_go_freq; struct wpa_config* p2p_pref_chan; struct wpa_config* pssid; struct wpa_config* p2p_ssid_postfix; struct wpa_config* config_methods; struct wpa_config* serial_number; struct wpa_config* model_number; struct wpa_config* model_name; struct wpa_config* manufacturer; struct wpa_config* device_name; struct wpa_config* driver_param; int /*<<< orphan*/  pcsc_pin; struct wpa_config* pcsc_reader; struct wpa_config* openssl_ciphers; struct wpa_config* pkcs11_module_path; struct wpa_config* pkcs11_engine_path; struct wpa_config* opensc_engine_path; struct wpa_config* ctrl_interface_group; struct wpa_config* ctrl_interface; int /*<<< orphan*/ * wps_vendor_ext; int /*<<< orphan*/  wps_vendor_ext_m1; struct wpa_cred* cred; struct wpa_ssid* ssid; } ;

/* Variables and functions */
 int MAX_WPS_VENDOR_EXT ; 
 int /*<<< orphan*/  os_free (struct wpa_config*) ; 
 int /*<<< orphan*/  str_clear_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_config_flush_blobs (struct wpa_config*) ; 
 int /*<<< orphan*/  wpa_config_free_cred (struct wpa_cred*) ; 
 int /*<<< orphan*/  wpa_config_free_ssid (struct wpa_ssid*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

void wpa_config_free(struct wpa_config *config)
{
	struct wpa_ssid *ssid, *prev = NULL;
	struct wpa_cred *cred, *cprev;
	int i;

	ssid = config->ssid;
	while (ssid) {
		prev = ssid;
		ssid = ssid->next;
		wpa_config_free_ssid(prev);
	}

	cred = config->cred;
	while (cred) {
		cprev = cred;
		cred = cred->next;
		wpa_config_free_cred(cprev);
	}

	wpa_config_flush_blobs(config);

	wpabuf_free(config->wps_vendor_ext_m1);
	for (i = 0; i < MAX_WPS_VENDOR_EXT; i++)
		wpabuf_free(config->wps_vendor_ext[i]);
	os_free(config->ctrl_interface);
	os_free(config->ctrl_interface_group);
	os_free(config->opensc_engine_path);
	os_free(config->pkcs11_engine_path);
	os_free(config->pkcs11_module_path);
	os_free(config->openssl_ciphers);
	os_free(config->pcsc_reader);
	str_clear_free(config->pcsc_pin);
	os_free(config->driver_param);
	os_free(config->device_name);
	os_free(config->manufacturer);
	os_free(config->model_name);
	os_free(config->model_number);
	os_free(config->serial_number);
	os_free(config->config_methods);
	os_free(config->p2p_ssid_postfix);
	os_free(config->pssid);
	os_free(config->p2p_pref_chan);
	os_free(config->p2p_no_go_freq.range);
	os_free(config->autoscan);
	os_free(config->freq_list);
	wpabuf_free(config->wps_nfc_dh_pubkey);
	wpabuf_free(config->wps_nfc_dh_privkey);
	wpabuf_free(config->wps_nfc_dev_pw);
	os_free(config->ext_password_backend);
	os_free(config->sae_groups);
	wpabuf_free(config->ap_vendor_elements);
	os_free(config->osu_dir);
	os_free(config->bgscan);
	os_free(config->wowlan_triggers);
	os_free(config->fst_group_id);
	os_free(config->sched_scan_plans);
#ifdef CONFIG_MBO
	os_free(config->non_pref_chan);
#endif /* CONFIG_MBO */

	os_free(config);
}