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
struct wpabuf {int dummy; } ;
struct eap_fast_tlv_parse {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int WPA_GET_BE16 (int*) ; 
 int eap_fast_parse_tlv (struct eap_fast_tlv_parse*,int,int*,size_t) ; 
 struct wpabuf* eap_fast_tlv_nak (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_memset (struct eap_fast_tlv_parse*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int wpabuf_len (struct wpabuf*) ; 
 int* wpabuf_mhead (struct wpabuf*) ; 

__attribute__((used)) static int eap_fast_parse_decrypted(struct wpabuf *decrypted,
				    struct eap_fast_tlv_parse *tlv,
				    struct wpabuf **resp)
{
	int mandatory, tlv_type, res;
	size_t len;
	u8 *pos, *end;

	os_memset(tlv, 0, sizeof(*tlv));

	/* Parse TLVs from the decrypted Phase 2 data */
	pos = wpabuf_mhead(decrypted);
	end = pos + wpabuf_len(decrypted);
	while (end - pos > 4) {
		mandatory = pos[0] & 0x80;
		tlv_type = WPA_GET_BE16(pos) & 0x3fff;
		pos += 2;
		len = WPA_GET_BE16(pos);
		pos += 2;
		if (len > (size_t) (end - pos)) {
			wpa_printf(MSG_INFO, "EAP-FAST: TLV overflow");
			return -1;
		}
		wpa_printf(MSG_DEBUG, "EAP-FAST: Received Phase 2: "
			   "TLV type %d length %u%s",
			   tlv_type, (unsigned int) len,
			   mandatory ? " (mandatory)" : "");

		res = eap_fast_parse_tlv(tlv, tlv_type, pos, len);
		if (res == -2)
			break;
		if (res < 0) {
			if (mandatory) {
				wpa_printf(MSG_DEBUG, "EAP-FAST: Nak unknown "
					   "mandatory TLV type %d", tlv_type);
				*resp = eap_fast_tlv_nak(0, tlv_type);
				break;
			} else {
				wpa_printf(MSG_DEBUG, "EAP-FAST: ignored "
					   "unknown optional TLV type %d",
					   tlv_type);
			}
		}

		pos += len;
	}

	return 0;
}