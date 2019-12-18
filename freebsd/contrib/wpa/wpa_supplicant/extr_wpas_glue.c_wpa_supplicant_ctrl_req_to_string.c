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
typedef  enum wpa_ctrl_req_type { ____Placeholder_wpa_ctrl_req_type } wpa_ctrl_req_type ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_WARNING ; 
#define  WPA_CTRL_REQ_EAP_IDENTITY 136 
#define  WPA_CTRL_REQ_EAP_NEW_PASSWORD 135 
#define  WPA_CTRL_REQ_EAP_OTP 134 
#define  WPA_CTRL_REQ_EAP_PASSPHRASE 133 
#define  WPA_CTRL_REQ_EAP_PASSWORD 132 
#define  WPA_CTRL_REQ_EAP_PIN 131 
#define  WPA_CTRL_REQ_EXT_CERT_CHECK 130 
#define  WPA_CTRL_REQ_PSK_PASSPHRASE 129 
#define  WPA_CTRL_REQ_SIM 128 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

const char * wpa_supplicant_ctrl_req_to_string(enum wpa_ctrl_req_type field,
					       const char *default_txt,
					       const char **txt)
{
	const char *ret = NULL;

	*txt = default_txt;

	switch (field) {
	case WPA_CTRL_REQ_EAP_IDENTITY:
		*txt = "Identity";
		ret = "IDENTITY";
		break;
	case WPA_CTRL_REQ_EAP_PASSWORD:
		*txt = "Password";
		ret = "PASSWORD";
		break;
	case WPA_CTRL_REQ_EAP_NEW_PASSWORD:
		*txt = "New Password";
		ret = "NEW_PASSWORD";
		break;
	case WPA_CTRL_REQ_EAP_PIN:
		*txt = "PIN";
		ret = "PIN";
		break;
	case WPA_CTRL_REQ_EAP_OTP:
		ret = "OTP";
		break;
	case WPA_CTRL_REQ_EAP_PASSPHRASE:
		*txt = "Private key passphrase";
		ret = "PASSPHRASE";
		break;
	case WPA_CTRL_REQ_SIM:
		ret = "SIM";
		break;
	case WPA_CTRL_REQ_PSK_PASSPHRASE:
		*txt = "PSK or passphrase";
		ret = "PSK_PASSPHRASE";
		break;
	case WPA_CTRL_REQ_EXT_CERT_CHECK:
		*txt = "External server certificate validation";
		ret = "EXT_CERT_CHECK";
		break;
	default:
		break;
	}

	/* txt needs to be something */
	if (*txt == NULL) {
		wpa_printf(MSG_WARNING, "No message for request %d", field);
		ret = NULL;
	}

	return ret;
}