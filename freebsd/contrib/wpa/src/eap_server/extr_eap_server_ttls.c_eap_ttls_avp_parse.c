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
struct wpabuf {int dummy; } ;
struct ttls_avp {int /*<<< orphan*/  avp_length; int /*<<< orphan*/  avp_code; } ;
struct eap_ttls_avp {int* eap; size_t eap_len; int* user_name; size_t user_name_len; int* user_password; size_t user_password_len; int* chap_challenge; size_t chap_challenge_len; int* chap_password; size_t chap_password_len; int* mschap_challenge; size_t mschap_challenge_len; int* mschap_response; size_t mschap_response_len; int* mschap2_response; size_t mschap2_response_len; } ;
typedef  int /*<<< orphan*/  be32 ;

/* Variables and functions */
 int AVP_FLAGS_MANDATORY ; 
 int AVP_FLAGS_VENDOR ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int RADIUS_ATTR_CHAP_CHALLENGE ; 
 int RADIUS_ATTR_CHAP_PASSWORD ; 
 int RADIUS_ATTR_EAP_MESSAGE ; 
 int RADIUS_ATTR_MS_CHAP2_RESPONSE ; 
 int RADIUS_ATTR_MS_CHAP_CHALLENGE ; 
 int RADIUS_ATTR_MS_CHAP_RESPONSE ; 
 int RADIUS_ATTR_USER_NAME ; 
 int RADIUS_ATTR_USER_PASSWORD ; 
 int RADIUS_VENDOR_ID_MICROSOFT ; 
 int be_to_host32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (int*) ; 
 int /*<<< orphan*/  os_memcpy (int*,int*,size_t) ; 
 int* os_memdup (int*,size_t) ; 
 int /*<<< orphan*/  os_memset (struct eap_ttls_avp*,int /*<<< orphan*/ ,int) ; 
 int* os_realloc (int*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii_key (int /*<<< orphan*/ ,char*,int*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int wpabuf_len (struct wpabuf*) ; 
 int* wpabuf_mhead (struct wpabuf*) ; 

__attribute__((used)) static int eap_ttls_avp_parse(struct wpabuf *buf, struct eap_ttls_avp *parse)
{
	struct ttls_avp *avp;
	u8 *pos;
	int left;

	pos = wpabuf_mhead(buf);
	left = wpabuf_len(buf);
	os_memset(parse, 0, sizeof(*parse));

	while (left > 0) {
		u32 avp_code, avp_length, vendor_id = 0;
		u8 avp_flags, *dpos;
		size_t pad, dlen;
		avp = (struct ttls_avp *) pos;
		avp_code = be_to_host32(avp->avp_code);
		avp_length = be_to_host32(avp->avp_length);
		avp_flags = (avp_length >> 24) & 0xff;
		avp_length &= 0xffffff;
		wpa_printf(MSG_DEBUG, "EAP-TTLS: AVP: code=%d flags=0x%02x "
			   "length=%d", (int) avp_code, avp_flags,
			   (int) avp_length);
		if ((int) avp_length > left) {
			wpa_printf(MSG_WARNING, "EAP-TTLS: AVP overflow "
				   "(len=%d, left=%d) - dropped",
				   (int) avp_length, left);
			goto fail;
		}
		if (avp_length < sizeof(*avp)) {
			wpa_printf(MSG_WARNING, "EAP-TTLS: Invalid AVP length "
				   "%d", avp_length);
			goto fail;
		}
		dpos = (u8 *) (avp + 1);
		dlen = avp_length - sizeof(*avp);
		if (avp_flags & AVP_FLAGS_VENDOR) {
			if (dlen < 4) {
				wpa_printf(MSG_WARNING, "EAP-TTLS: vendor AVP "
					   "underflow");
				goto fail;
			}
			vendor_id = be_to_host32(* (be32 *) dpos);
			wpa_printf(MSG_DEBUG, "EAP-TTLS: AVP vendor_id %d",
				   (int) vendor_id);
			dpos += 4;
			dlen -= 4;
		}

		wpa_hexdump(MSG_DEBUG, "EAP-TTLS: AVP data", dpos, dlen);

		if (vendor_id == 0 && avp_code == RADIUS_ATTR_EAP_MESSAGE) {
			wpa_printf(MSG_DEBUG, "EAP-TTLS: AVP - EAP Message");
			if (parse->eap == NULL) {
				parse->eap = os_memdup(dpos, dlen);
				if (parse->eap == NULL) {
					wpa_printf(MSG_WARNING, "EAP-TTLS: "
						   "failed to allocate memory "
						   "for Phase 2 EAP data");
					goto fail;
				}
				parse->eap_len = dlen;
			} else {
				u8 *neweap = os_realloc(parse->eap,
							parse->eap_len + dlen);
				if (neweap == NULL) {
					wpa_printf(MSG_WARNING, "EAP-TTLS: "
						   "failed to allocate memory "
						   "for Phase 2 EAP data");
					goto fail;
				}
				os_memcpy(neweap + parse->eap_len, dpos, dlen);
				parse->eap = neweap;
				parse->eap_len += dlen;
			}
		} else if (vendor_id == 0 &&
			   avp_code == RADIUS_ATTR_USER_NAME) {
			wpa_hexdump_ascii(MSG_DEBUG, "EAP-TTLS: User-Name",
					  dpos, dlen);
			parse->user_name = dpos;
			parse->user_name_len = dlen;
		} else if (vendor_id == 0 &&
			   avp_code == RADIUS_ATTR_USER_PASSWORD) {
			u8 *password = dpos;
			size_t password_len = dlen;
			while (password_len > 0 &&
			       password[password_len - 1] == '\0') {
				password_len--;
			}
			wpa_hexdump_ascii_key(MSG_DEBUG, "EAP-TTLS: "
					      "User-Password (PAP)",
					      password, password_len);
			parse->user_password = password;
			parse->user_password_len = password_len;
		} else if (vendor_id == 0 &&
			   avp_code == RADIUS_ATTR_CHAP_CHALLENGE) {
			wpa_hexdump(MSG_DEBUG,
				    "EAP-TTLS: CHAP-Challenge (CHAP)",
				    dpos, dlen);
			parse->chap_challenge = dpos;
			parse->chap_challenge_len = dlen;
		} else if (vendor_id == 0 &&
			   avp_code == RADIUS_ATTR_CHAP_PASSWORD) {
			wpa_hexdump(MSG_DEBUG,
				    "EAP-TTLS: CHAP-Password (CHAP)",
				    dpos, dlen);
			parse->chap_password = dpos;
			parse->chap_password_len = dlen;
		} else if (vendor_id == RADIUS_VENDOR_ID_MICROSOFT &&
			   avp_code == RADIUS_ATTR_MS_CHAP_CHALLENGE) {
			wpa_hexdump(MSG_DEBUG,
				    "EAP-TTLS: MS-CHAP-Challenge",
				    dpos, dlen);
			parse->mschap_challenge = dpos;
			parse->mschap_challenge_len = dlen;
		} else if (vendor_id == RADIUS_VENDOR_ID_MICROSOFT &&
			   avp_code == RADIUS_ATTR_MS_CHAP_RESPONSE) {
			wpa_hexdump(MSG_DEBUG,
				    "EAP-TTLS: MS-CHAP-Response (MSCHAP)",
				    dpos, dlen);
			parse->mschap_response = dpos;
			parse->mschap_response_len = dlen;
		} else if (vendor_id == RADIUS_VENDOR_ID_MICROSOFT &&
			   avp_code == RADIUS_ATTR_MS_CHAP2_RESPONSE) {
			wpa_hexdump(MSG_DEBUG,
				    "EAP-TTLS: MS-CHAP2-Response (MSCHAPV2)",
				    dpos, dlen);
			parse->mschap2_response = dpos;
			parse->mschap2_response_len = dlen;
		} else if (avp_flags & AVP_FLAGS_MANDATORY) {
			wpa_printf(MSG_WARNING, "EAP-TTLS: Unsupported "
				   "mandatory AVP code %d vendor_id %d - "
				   "dropped", (int) avp_code, (int) vendor_id);
			goto fail;
		} else {
			wpa_printf(MSG_DEBUG, "EAP-TTLS: Ignoring unsupported "
				   "AVP code %d vendor_id %d",
				   (int) avp_code, (int) vendor_id);
		}

		pad = (4 - (avp_length & 3)) & 3;
		pos += avp_length + pad;
		left -= avp_length + pad;
	}

	return 0;

fail:
	os_free(parse->eap);
	parse->eap = NULL;
	return -1;
}