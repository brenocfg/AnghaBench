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
struct wps_registrar {int dummy; } ;
struct wps_parse_attr {scalar_t__* selected_registrar; int authorized_macs_len; int /*<<< orphan*/  version2; scalar_t__ authorized_macs; scalar_t__ sel_reg_config_methods; scalar_t__ dev_password_id; } ;
struct wpabuf {int dummy; } ;
struct subscription {int selected_registrar; int dev_password_id; int config_methods; int /*<<< orphan*/  authorized_macs; struct wps_registrar* reg; } ;

/* Variables and functions */
 int DEV_PW_DEFAULT ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int WPA_GET_BE16 (scalar_t__) ; 
 int WPS_MAX_AUTHORIZED_MACS ; 
 int /*<<< orphan*/  WPS_PBC_WALK_TIME ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct subscription*,struct wps_registrar*) ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct subscription*,struct wps_registrar*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  upnp_er_set_selected_timeout ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wps_parse_msg (struct wpabuf const*,struct wps_parse_attr*) ; 
 int /*<<< orphan*/  wps_registrar_selected_registrar_changed (struct wps_registrar*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_validate_upnp_set_selected_registrar (struct wpabuf const*) ; 

int upnp_er_set_selected_registrar(struct wps_registrar *reg,
				   struct subscription *s,
				   const struct wpabuf *msg)
{
	struct wps_parse_attr attr;

	wpa_hexdump_buf(MSG_MSGDUMP, "WPS: SetSelectedRegistrar attributes",
			msg);
	if (wps_validate_upnp_set_selected_registrar(msg) < 0 ||
	    wps_parse_msg(msg, &attr) < 0)
		return -1;

	s->reg = reg;
	eloop_cancel_timeout(upnp_er_set_selected_timeout, s, reg);

	os_memset(s->authorized_macs, 0, sizeof(s->authorized_macs));
	if (attr.selected_registrar == NULL || *attr.selected_registrar == 0) {
		wpa_printf(MSG_DEBUG, "WPS: SetSelectedRegistrar: Disable "
			   "Selected Registrar");
		s->selected_registrar = 0;
	} else {
		s->selected_registrar = 1;
		s->dev_password_id = attr.dev_password_id ?
			WPA_GET_BE16(attr.dev_password_id) : DEV_PW_DEFAULT;
		s->config_methods = attr.sel_reg_config_methods ?
			WPA_GET_BE16(attr.sel_reg_config_methods) : -1;
		if (attr.authorized_macs) {
			int count = attr.authorized_macs_len / ETH_ALEN;
			if (count > WPS_MAX_AUTHORIZED_MACS)
				count = WPS_MAX_AUTHORIZED_MACS;
			os_memcpy(s->authorized_macs, attr.authorized_macs,
				  count * ETH_ALEN);
		} else if (!attr.version2) {
			wpa_printf(MSG_DEBUG, "WPS: Add broadcast "
				   "AuthorizedMACs for WPS 1.0 ER");
			os_memset(s->authorized_macs, 0xff, ETH_ALEN);
		}
		eloop_register_timeout(WPS_PBC_WALK_TIME, 0,
				       upnp_er_set_selected_timeout, s, reg);
	}

	wps_registrar_selected_registrar_changed(reg, 0);

	return 0;
}