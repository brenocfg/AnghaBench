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
typedef  int u8 ;
struct wps_parse_attr {int const* version2; int const* authorized_macs; int authorized_macs_len; int const* network_key_shareable; int const* request_to_enroll; int const* settings_delay_time; int const* registrar_configuration_methods; int multi_ap_ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_EXCESSIVE ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
#define  WFA_ELEM_AUTHORIZEDMACS 134 
#define  WFA_ELEM_MULTI_AP 133 
#define  WFA_ELEM_NETWORK_KEY_SHAREABLE 132 
#define  WFA_ELEM_REGISTRAR_CONFIGURATION_METHODS 131 
#define  WFA_ELEM_REQUEST_TO_ENROLL 130 
#define  WFA_ELEM_SETTINGS_DELAY_TIME 129 
#define  WFA_ELEM_VERSION2 128 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int wps_set_vendor_ext_wfa_subelem(struct wps_parse_attr *attr,
					  u8 id, u8 len, const u8 *pos)
{
	wpa_printf(MSG_EXCESSIVE, "WPS: WFA subelement id=%u len=%u",
		   id, len);
	switch (id) {
	case WFA_ELEM_VERSION2:
		if (len != 1) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Version2 length "
				   "%u", len);
			return -1;
		}
		attr->version2 = pos;
		break;
	case WFA_ELEM_AUTHORIZEDMACS:
		attr->authorized_macs = pos;
		attr->authorized_macs_len = len;
		break;
	case WFA_ELEM_NETWORK_KEY_SHAREABLE:
		if (len != 1) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Network Key "
				   "Shareable length %u", len);
			return -1;
		}
		attr->network_key_shareable = pos;
		break;
	case WFA_ELEM_REQUEST_TO_ENROLL:
		if (len != 1) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Request to Enroll "
				   "length %u", len);
			return -1;
		}
		attr->request_to_enroll = pos;
		break;
	case WFA_ELEM_SETTINGS_DELAY_TIME:
		if (len != 1) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Settings Delay "
				   "Time length %u", len);
			return -1;
		}
		attr->settings_delay_time = pos;
		break;
	case WFA_ELEM_REGISTRAR_CONFIGURATION_METHODS:
		if (len != 2) {
			wpa_printf(MSG_DEBUG, "WPS: Invalid Registrar Configuration Methods length %u",
				   len);
			return -1;
		}
		attr->registrar_configuration_methods = pos;
		break;
	case WFA_ELEM_MULTI_AP:
		if (len != 1) {
			wpa_printf(MSG_DEBUG,
				   "WPS: Invalid Multi-AP Extension length %u",
				   len);
			return -1;
		}
		attr->multi_ap_ext = *pos;
		wpa_printf(MSG_DEBUG, "WPS: Multi-AP Extension 0x%02x",
			   attr->multi_ap_ext);
		break;
	default:
		wpa_printf(MSG_MSGDUMP, "WPS: Skipped unknown WFA Vendor "
			   "Extension subelement %u", id);
		break;
	}

	return 0;
}