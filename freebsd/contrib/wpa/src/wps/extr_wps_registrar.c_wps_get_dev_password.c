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
typedef  int /*<<< orphan*/  u8 ;
struct wps_data {size_t dev_password_len; int dev_pw_id; int /*<<< orphan*/ * dev_password; int /*<<< orphan*/  peer_dev; int /*<<< orphan*/  uuid_e; TYPE_2__* wps; TYPE_1__* nfc_pw_token; scalar_t__ pbc; } ;
struct TYPE_4__ {int ap_nfc_dev_pw_id; int /*<<< orphan*/  registrar; scalar_t__ ap_nfc_dev_pw; } ;
struct TYPE_3__ {scalar_t__ pw_id; size_t dev_pw_len; int /*<<< orphan*/ * dev_pw; } ;

/* Variables and functions */
 int DEV_PW_DEFAULT ; 
 scalar_t__ DEV_PW_NFC_CONNECTION_HANDOVER ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  bin_clear_free (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * os_memdup (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * wpabuf_head (scalar_t__) ; 
 size_t wpabuf_len (scalar_t__) ; 
 int /*<<< orphan*/  wps_cb_pin_needed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wps_registrar_get_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int wps_get_dev_password(struct wps_data *wps)
{
	const u8 *pin;
	size_t pin_len = 0;

	bin_clear_free(wps->dev_password, wps->dev_password_len);
	wps->dev_password = NULL;

	if (wps->pbc) {
		wpa_printf(MSG_DEBUG, "WPS: Use default PIN for PBC");
		pin = (const u8 *) "00000000";
		pin_len = 8;
#ifdef CONFIG_WPS_NFC
	} else if (wps->nfc_pw_token) {
		if (wps->nfc_pw_token->pw_id == DEV_PW_NFC_CONNECTION_HANDOVER)
		{
			wpa_printf(MSG_DEBUG, "WPS: Using NFC connection "
				   "handover and abbreviated WPS handshake "
				   "without Device Password");
			return 0;
		}
		wpa_printf(MSG_DEBUG, "WPS: Use OOB Device Password from NFC "
			   "Password Token");
		pin = wps->nfc_pw_token->dev_pw;
		pin_len = wps->nfc_pw_token->dev_pw_len;
	} else if (wps->dev_pw_id >= 0x10 &&
		   wps->wps->ap_nfc_dev_pw_id == wps->dev_pw_id &&
		   wps->wps->ap_nfc_dev_pw) {
		wpa_printf(MSG_DEBUG, "WPS: Use OOB Device Password from own NFC Password Token");
		pin = wpabuf_head(wps->wps->ap_nfc_dev_pw);
		pin_len = wpabuf_len(wps->wps->ap_nfc_dev_pw);
#endif /* CONFIG_WPS_NFC */
	} else {
		pin = wps_registrar_get_pin(wps->wps->registrar, wps->uuid_e,
					    &pin_len);
		if (pin && wps->dev_pw_id >= 0x10) {
			wpa_printf(MSG_DEBUG, "WPS: No match for OOB Device "
				   "Password ID, but PIN found");
			/*
			 * See whether Enrollee is willing to use PIN instead.
			 */
			wps->dev_pw_id = DEV_PW_DEFAULT;
		}
	}
	if (pin == NULL) {
		wpa_printf(MSG_DEBUG, "WPS: No Device Password available for "
			   "the Enrollee (context %p registrar %p)",
			   wps->wps, wps->wps->registrar);
		wps_cb_pin_needed(wps->wps->registrar, wps->uuid_e,
				  &wps->peer_dev);
		return -1;
	}

	wps->dev_password = os_memdup(pin, pin_len);
	if (wps->dev_password == NULL)
		return -1;
	wps->dev_password_len = pin_len;

	return 0;
}