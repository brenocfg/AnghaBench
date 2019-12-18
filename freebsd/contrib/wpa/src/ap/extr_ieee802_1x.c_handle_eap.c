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
typedef  int u16 ;
struct sta_info {int dummy; } ;
struct hostapd_data {int dummy; } ;
struct eap_hdr {int code; int /*<<< orphan*/  identifier; int /*<<< orphan*/  length; } ;

/* Variables and functions */
#define  EAP_CODE_FAILURE 133 
#define  EAP_CODE_FINISH 132 
#define  EAP_CODE_INITIATE 131 
#define  EAP_CODE_REQUEST 130 
#define  EAP_CODE_RESPONSE 129 
#define  EAP_CODE_SUCCESS 128 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int be_to_host16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_eap_initiate (struct hostapd_data*,struct sta_info*,struct eap_hdr*,int) ; 
 int /*<<< orphan*/  handle_eap_response (struct hostapd_data*,struct sta_info*,struct eap_hdr*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void handle_eap(struct hostapd_data *hapd, struct sta_info *sta,
		       u8 *buf, size_t len)
{
	struct eap_hdr *eap;
	u16 eap_len;

	if (len < sizeof(*eap)) {
		wpa_printf(MSG_INFO, "   too short EAP packet");
		return;
	}

	eap = (struct eap_hdr *) buf;

	eap_len = be_to_host16(eap->length);
	wpa_printf(MSG_DEBUG, "EAP: code=%d identifier=%d length=%d",
		   eap->code, eap->identifier, eap_len);
	if (eap_len < sizeof(*eap)) {
		wpa_printf(MSG_DEBUG, "   Invalid EAP length");
		return;
	} else if (eap_len > len) {
		wpa_printf(MSG_DEBUG, "   Too short frame to contain this EAP "
			   "packet");
		return;
	} else if (eap_len < len) {
		wpa_printf(MSG_DEBUG, "   Ignoring %lu extra bytes after EAP "
			   "packet", (unsigned long) len - eap_len);
	}

	switch (eap->code) {
	case EAP_CODE_REQUEST:
		wpa_printf(MSG_DEBUG, " (request)");
		return;
	case EAP_CODE_RESPONSE:
		wpa_printf(MSG_DEBUG, " (response)");
		handle_eap_response(hapd, sta, eap, eap_len);
		break;
	case EAP_CODE_SUCCESS:
		wpa_printf(MSG_DEBUG, " (success)");
		return;
	case EAP_CODE_FAILURE:
		wpa_printf(MSG_DEBUG, " (failure)");
		return;
	case EAP_CODE_INITIATE:
		wpa_printf(MSG_DEBUG, " (initiate)");
		handle_eap_initiate(hapd, sta, eap, eap_len);
		break;
	case EAP_CODE_FINISH:
		wpa_printf(MSG_DEBUG, " (finish)");
		break;
	default:
		wpa_printf(MSG_DEBUG, " (unknown code)");
		return;
	}
}