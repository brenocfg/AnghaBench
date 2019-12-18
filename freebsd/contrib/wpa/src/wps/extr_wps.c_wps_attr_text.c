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
struct wps_parse_attr {scalar_t__* wps_state; char* dev_name; int dev_name_len; scalar_t__ config_methods; scalar_t__ primary_dev_type; scalar_t__ sel_reg_config_methods; scalar_t__ dev_password_id; scalar_t__* selected_registrar; scalar_t__* ap_setup_locked; } ;
struct wpabuf {int dummy; } ;
typedef  int /*<<< orphan*/  devtype ;

/* Variables and functions */
 char* WPA_GET_BE16 (scalar_t__) ; 
 int WPS_DEV_TYPE_BUFSIZE ; 
 scalar_t__ WPS_STATE_CONFIGURED ; 
 scalar_t__ WPS_STATE_NOT_CONFIGURED ; 
 scalar_t__ is_ctrl_char (char) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (int) ; 
 int os_snprintf (char*,int,char*,...) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 char* wps_dev_type_bin2str (scalar_t__,char*,int) ; 
 scalar_t__ wps_parse_msg (struct wpabuf*,struct wps_parse_attr*) ; 

int wps_attr_text(struct wpabuf *data, char *buf, char *end)
{
	struct wps_parse_attr attr;
	char *pos = buf;
	int ret;

	if (wps_parse_msg(data, &attr) < 0)
		return -1;

	if (attr.wps_state) {
		if (*attr.wps_state == WPS_STATE_NOT_CONFIGURED)
			ret = os_snprintf(pos, end - pos,
					  "wps_state=unconfigured\n");
		else if (*attr.wps_state == WPS_STATE_CONFIGURED)
			ret = os_snprintf(pos, end - pos,
					  "wps_state=configured\n");
		else
			ret = 0;
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}

	if (attr.ap_setup_locked && *attr.ap_setup_locked) {
		ret = os_snprintf(pos, end - pos,
				  "wps_ap_setup_locked=1\n");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}

	if (attr.selected_registrar && *attr.selected_registrar) {
		ret = os_snprintf(pos, end - pos,
				  "wps_selected_registrar=1\n");
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}

	if (attr.dev_password_id) {
		ret = os_snprintf(pos, end - pos,
				  "wps_device_password_id=%u\n",
				  WPA_GET_BE16(attr.dev_password_id));
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}

	if (attr.sel_reg_config_methods) {
		ret = os_snprintf(pos, end - pos,
				  "wps_selected_registrar_config_methods="
				  "0x%04x\n",
				  WPA_GET_BE16(attr.sel_reg_config_methods));
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}

	if (attr.primary_dev_type) {
		char devtype[WPS_DEV_TYPE_BUFSIZE];
		ret = os_snprintf(pos, end - pos,
				  "wps_primary_device_type=%s\n",
				  wps_dev_type_bin2str(attr.primary_dev_type,
						       devtype,
						       sizeof(devtype)));
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}

	if (attr.dev_name) {
		char *str = os_malloc(attr.dev_name_len + 1);
		size_t i;
		if (str == NULL)
			return pos - buf;
		for (i = 0; i < attr.dev_name_len; i++) {
			if (attr.dev_name[i] == 0 ||
			    is_ctrl_char(attr.dev_name[i]))
				str[i] = '_';
			else
				str[i] = attr.dev_name[i];
		}
		str[i] = '\0';
		ret = os_snprintf(pos, end - pos, "wps_device_name=%s\n", str);
		os_free(str);
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}

	if (attr.config_methods) {
		ret = os_snprintf(pos, end - pos,
				  "wps_config_methods=0x%04x\n",
				  WPA_GET_BE16(attr.config_methods));
		if (os_snprintf_error(end - pos, ret))
			return pos - buf;
		pos += ret;
	}

	return pos - buf;
}