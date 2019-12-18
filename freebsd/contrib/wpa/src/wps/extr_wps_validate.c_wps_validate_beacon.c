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
struct wps_parse_attr {scalar_t__* selected_registrar; int /*<<< orphan*/  authorized_macs_len; int /*<<< orphan*/  authorized_macs; int /*<<< orphan*/ * version2; int /*<<< orphan*/  rf_bands; int /*<<< orphan*/  uuid_e; int /*<<< orphan*/  sel_reg_config_methods; int /*<<< orphan*/  dev_password_id; int /*<<< orphan*/  ap_setup_locked; int /*<<< orphan*/  wps_state; int /*<<< orphan*/  version; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wps_parse_msg (struct wpabuf const*,struct wps_parse_attr*) ; 
 scalar_t__ wps_validate_ap_setup_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_validate_authorized_macs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_validate_dev_password_id (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_rf_bands (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_validate_sel_reg_config_methods (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ wps_validate_selected_registrar (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_validate_uuid_e (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_validate_version (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wps_validate_version2 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ wps_validate_wps_state (int /*<<< orphan*/ ,int) ; 

int wps_validate_beacon(const struct wpabuf *wps_ie)
{
	struct wps_parse_attr attr;
	int wps2, sel_reg;

	if (wps_ie == NULL) {
		wpa_printf(MSG_INFO, "WPS-STRICT: No WPS IE in Beacon frame");
		return -1;
	}
	if (wps_parse_msg(wps_ie, &attr) < 0) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Failed to parse WPS IE in "
			   "Beacon frame");
		return -1;
	}

	wps2 = attr.version2 != NULL;
	sel_reg = attr.selected_registrar != NULL &&
		*attr.selected_registrar != 0;
	if (wps_validate_version(attr.version, 1) ||
	    wps_validate_wps_state(attr.wps_state, 1) ||
	    wps_validate_ap_setup_locked(attr.ap_setup_locked, 0) ||
	    wps_validate_selected_registrar(attr.selected_registrar, 0) ||
	    wps_validate_dev_password_id(attr.dev_password_id, sel_reg) ||
	    wps_validate_sel_reg_config_methods(attr.sel_reg_config_methods,
						wps2, sel_reg) ||
	    wps_validate_uuid_e(attr.uuid_e, 0) ||
	    wps_validate_rf_bands(attr.rf_bands, 0) ||
	    wps_validate_version2(attr.version2, wps2) ||
	    wps_validate_authorized_macs(attr.authorized_macs,
					 attr.authorized_macs_len, 0)) {
		wpa_printf(MSG_INFO, "WPS-STRICT: Invalid Beacon frame");
		return -1;
	}

	return 0;
}