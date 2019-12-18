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
typedef  int u32 ;
struct ttls_parse_avp {int* mschapv2; int mschapv2_error; } ;
struct ttls_avp {int /*<<< orphan*/  avp_length; int /*<<< orphan*/  avp_code; } ;

/* Variables and functions */
 int AVP_FLAGS_MANDATORY ; 
 int AVP_FLAGS_VENDOR ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int RADIUS_ATTR_EAP_MESSAGE ; 
 int RADIUS_ATTR_MS_CHAP2_SUCCESS ; 
 int RADIUS_ATTR_MS_CHAP_ERROR ; 
 int RADIUS_ATTR_REPLY_MESSAGE ; 
 int RADIUS_VENDOR_ID_MICROSOFT ; 
 int WPA_GET_BE32 (int*) ; 
 int be_to_host32 (int /*<<< orphan*/ ) ; 
 scalar_t__ eap_ttls_parse_attr_eap (int*,size_t,struct ttls_parse_avp*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int eap_ttls_parse_avp(u8 *pos, size_t left,
			      struct ttls_parse_avp *parse)
{
	struct ttls_avp *avp;
	u32 avp_code, avp_length, vendor_id = 0;
	u8 avp_flags, *dpos;
	size_t dlen;

	avp = (struct ttls_avp *) pos;
	avp_code = be_to_host32(avp->avp_code);
	avp_length = be_to_host32(avp->avp_length);
	avp_flags = (avp_length >> 24) & 0xff;
	avp_length &= 0xffffff;
	wpa_printf(MSG_DEBUG, "EAP-TTLS: AVP: code=%d flags=0x%02x "
		   "length=%d", (int) avp_code, avp_flags,
		   (int) avp_length);

	if (avp_length > left) {
		wpa_printf(MSG_WARNING, "EAP-TTLS: AVP overflow "
			   "(len=%d, left=%lu) - dropped",
			   (int) avp_length, (unsigned long) left);
		return -1;
	}

	if (avp_length < sizeof(*avp)) {
		wpa_printf(MSG_WARNING, "EAP-TTLS: Invalid AVP length %d",
			   avp_length);
		return -1;
	}

	dpos = (u8 *) (avp + 1);
	dlen = avp_length - sizeof(*avp);
	if (avp_flags & AVP_FLAGS_VENDOR) {
		if (dlen < 4) {
			wpa_printf(MSG_WARNING, "EAP-TTLS: Vendor AVP "
				   "underflow");
			return -1;
		}
		vendor_id = WPA_GET_BE32(dpos);
		wpa_printf(MSG_DEBUG, "EAP-TTLS: AVP vendor_id %d",
			   (int) vendor_id);
		dpos += 4;
		dlen -= 4;
	}

	wpa_hexdump(MSG_DEBUG, "EAP-TTLS: AVP data", dpos, dlen);

	if (vendor_id == 0 && avp_code == RADIUS_ATTR_EAP_MESSAGE) {
		if (eap_ttls_parse_attr_eap(dpos, dlen, parse) < 0)
			return -1;
	} else if (vendor_id == 0 && avp_code == RADIUS_ATTR_REPLY_MESSAGE) {
		/* This is an optional message that can be displayed to
		 * the user. */
		wpa_hexdump_ascii(MSG_DEBUG, "EAP-TTLS: AVP - Reply-Message",
				  dpos, dlen);
	} else if (vendor_id == RADIUS_VENDOR_ID_MICROSOFT &&
		   avp_code == RADIUS_ATTR_MS_CHAP2_SUCCESS) {
		wpa_hexdump_ascii(MSG_DEBUG, "EAP-TTLS: MS-CHAP2-Success",
				  dpos, dlen);
		if (dlen != 43) {
			wpa_printf(MSG_WARNING, "EAP-TTLS: Unexpected "
				   "MS-CHAP2-Success length "
				   "(len=%lu, expected 43)",
				   (unsigned long) dlen);
			return -1;
		}
		parse->mschapv2 = dpos;
	} else if (vendor_id == RADIUS_VENDOR_ID_MICROSOFT &&
		   avp_code == RADIUS_ATTR_MS_CHAP_ERROR) {
		wpa_hexdump_ascii(MSG_DEBUG, "EAP-TTLS: MS-CHAP-Error",
				  dpos, dlen);
		parse->mschapv2_error = 1;
	} else if (avp_flags & AVP_FLAGS_MANDATORY) {
		wpa_printf(MSG_WARNING, "EAP-TTLS: Unsupported mandatory AVP "
			   "code %d vendor_id %d - dropped",
			   (int) avp_code, (int) vendor_id);
		return -1;
	} else {
		wpa_printf(MSG_DEBUG, "EAP-TTLS: Ignoring unsupported AVP "
			   "code %d vendor_id %d",
			   (int) avp_code, (int) vendor_id);
	}

	return avp_length;
}