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
struct wps_data {int dev_pw_id; struct wpabuf* dh_pubkey_e; struct wpabuf* dh_pubkey_r; scalar_t__ registrar; int /*<<< orphan*/ * dh_privkey; int /*<<< orphan*/ * dh_ctx; TYPE_1__* wps; } ;
struct wpabuf {int dummy; } ;
struct TYPE_2__ {int ap_nfc_dev_pw_id; int /*<<< orphan*/ * ap_nfc_dh_pubkey; int /*<<< orphan*/ * ap_nfc_dh_privkey; scalar_t__ ap; int /*<<< orphan*/ * dh_pubkey; int /*<<< orphan*/ * dh_ctx; int /*<<< orphan*/ * dh_privkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_PUBLIC_KEY ; 
 int DEV_PW_DEFAULT ; 
 int DEV_PW_NFC_CONNECTION_HANDOVER ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  dh5_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dh5_init (int /*<<< orphan*/ **,struct wpabuf**) ; 
 int /*<<< orphan*/ * dh5_init_fixed (int /*<<< orphan*/ *,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_hexdump_buf_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_clear_free (int /*<<< orphan*/ *) ; 
 void* wpabuf_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf*) ; 
 struct wpabuf* wpabuf_zeropad (struct wpabuf*,int) ; 

int wps_build_public_key(struct wps_data *wps, struct wpabuf *msg)
{
	struct wpabuf *pubkey = NULL;

	wpa_printf(MSG_DEBUG, "WPS:  * Public Key");
	wpabuf_clear_free(wps->dh_privkey);
	wps->dh_privkey = NULL;
	if (wps->dev_pw_id != DEV_PW_DEFAULT && wps->wps->dh_privkey &&
	    wps->wps->dh_ctx) {
		wpa_printf(MSG_DEBUG, "WPS: Using pre-configured DH keys");
		if (wps->wps->dh_pubkey == NULL) {
			wpa_printf(MSG_DEBUG,
				   "WPS: wps->wps->dh_pubkey == NULL");
			return -1;
		}
		wps->dh_privkey = wpabuf_dup(wps->wps->dh_privkey);
		wps->dh_ctx = wps->wps->dh_ctx;
		wps->wps->dh_ctx = NULL;
		pubkey = wpabuf_dup(wps->wps->dh_pubkey);
#ifdef CONFIG_WPS_NFC
	} else if ((wps->dev_pw_id >= 0x10 ||
		    wps->dev_pw_id == DEV_PW_NFC_CONNECTION_HANDOVER) &&
		   (wps->wps->ap ||
		    (wps->wps->ap_nfc_dh_pubkey &&
		     wps->wps->ap_nfc_dev_pw_id ==
		     DEV_PW_NFC_CONNECTION_HANDOVER &&
		     wps->dev_pw_id == DEV_PW_NFC_CONNECTION_HANDOVER)) &&
		   (wps->dev_pw_id == wps->wps->ap_nfc_dev_pw_id ||
		    wps->wps->ap_nfc_dh_pubkey)) {
		wpa_printf(MSG_DEBUG, "WPS: Using NFC password token DH keys");
		if (wps->wps->ap_nfc_dh_privkey == NULL) {
			wpa_printf(MSG_DEBUG,
				   "WPS: wps->wps->ap_nfc_dh_privkey == NULL");
			return -1;
		}
		if (wps->wps->ap_nfc_dh_pubkey == NULL) {
			wpa_printf(MSG_DEBUG,
				   "WPS: wps->wps->ap_nfc_dh_pubkey == NULL");
			return -1;
		}
		wps->dh_privkey = wpabuf_dup(wps->wps->ap_nfc_dh_privkey);
		pubkey = wpabuf_dup(wps->wps->ap_nfc_dh_pubkey);
		if (wps->dh_privkey && pubkey)
			wps->dh_ctx = dh5_init_fixed(wps->dh_privkey, pubkey);
#endif /* CONFIG_WPS_NFC */
	} else {
		wpa_printf(MSG_DEBUG, "WPS: Generate new DH keys");
		dh5_free(wps->dh_ctx);
		wps->dh_ctx = dh5_init(&wps->dh_privkey, &pubkey);
		pubkey = wpabuf_zeropad(pubkey, 192);
	}
	if (wps->dh_ctx == NULL || wps->dh_privkey == NULL || pubkey == NULL) {
		wpa_printf(MSG_DEBUG, "WPS: Failed to initialize "
			   "Diffie-Hellman handshake");
		wpabuf_free(pubkey);
		return -1;
	}
	wpa_hexdump_buf_key(MSG_DEBUG, "WPS: DH Private Key", wps->dh_privkey);
	wpa_hexdump_buf(MSG_DEBUG, "WPS: DH own Public Key", pubkey);

	wpabuf_put_be16(msg, ATTR_PUBLIC_KEY);
	wpabuf_put_be16(msg, wpabuf_len(pubkey));
	wpabuf_put_buf(msg, pubkey);

	if (wps->registrar) {
		wpabuf_free(wps->dh_pubkey_r);
		wps->dh_pubkey_r = pubkey;
	} else {
		wpabuf_free(wps->dh_pubkey_e);
		wps->dh_pubkey_e = pubkey;
	}

	return 0;
}