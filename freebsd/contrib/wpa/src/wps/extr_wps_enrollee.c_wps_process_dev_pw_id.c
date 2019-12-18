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
typedef  scalar_t__ u16 ;
struct wps_data {scalar_t__ dev_pw_id; scalar_t__ alt_dev_pw_id; scalar_t__ alt_dev_password_len; int /*<<< orphan*/ * alt_dev_password; scalar_t__ dev_password_len; int /*<<< orphan*/ * dev_password; } ;

/* Variables and functions */
 scalar_t__ DEV_PW_DEFAULT ; 
 scalar_t__ DEV_PW_PUSHBUTTON ; 
 scalar_t__ DEV_PW_REGISTRAR_SPECIFIED ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  bin_clear_free (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wps_process_dev_pw_id(struct wps_data *wps, const u8 *dev_pw_id)
{
	u16 id;

	if (dev_pw_id == NULL) {
		wpa_printf(MSG_DEBUG, "WPS: Device Password ID");
		return -1;
	}

	id = WPA_GET_BE16(dev_pw_id);
	if (wps->dev_pw_id == id) {
		wpa_printf(MSG_DEBUG, "WPS: Device Password ID %u", id);
		return 0;
	}

#ifdef CONFIG_P2P
	if ((id == DEV_PW_DEFAULT &&
	     wps->dev_pw_id == DEV_PW_REGISTRAR_SPECIFIED) ||
	    (id == DEV_PW_REGISTRAR_SPECIFIED &&
	     wps->dev_pw_id == DEV_PW_DEFAULT)) {
		/*
		 * Common P2P use cases indicate whether the PIN is from the
		 * client or GO using Device Password Id in M1/M2 in a way that
		 * does not look fully compliant with WSC specification. Anyway,
		 * this is deployed and needs to be allowed, so ignore changes
		 * between Registrar-Specified and Default PIN.
		 */
		wpa_printf(MSG_DEBUG, "WPS: Allow PIN Device Password ID "
			   "change");
		return 0;
	}
#endif /* CONFIG_P2P */

	wpa_printf(MSG_DEBUG, "WPS: Registrar trying to change Device Password "
		   "ID from %u to %u", wps->dev_pw_id, id);

	if (wps->dev_pw_id == DEV_PW_PUSHBUTTON && id == DEV_PW_DEFAULT) {
		wpa_printf(MSG_DEBUG,
			   "WPS: Workaround - ignore PBC-to-PIN change");
		return 0;
	}

	if (wps->alt_dev_password && wps->alt_dev_pw_id == id) {
		wpa_printf(MSG_DEBUG, "WPS: Found a matching Device Password");
		bin_clear_free(wps->dev_password, wps->dev_password_len);
		wps->dev_pw_id = wps->alt_dev_pw_id;
		wps->dev_password = wps->alt_dev_password;
		wps->dev_password_len = wps->alt_dev_password_len;
		wps->alt_dev_password = NULL;
		wps->alt_dev_password_len = 0;
		return 0;
	}

	return -1;
}