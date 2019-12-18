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
struct pac_tlv_hdr {int /*<<< orphan*/  len; int /*<<< orphan*/  type; } ;
struct eap_fast_pac {size_t pac_info_len; int /*<<< orphan*/ * a_id_info; int /*<<< orphan*/ * a_id; int /*<<< orphan*/ * pac_info; int /*<<< orphan*/  pac_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  PAC_TYPE_TUNNEL_PAC ; 
 void* be_to_host16 (int /*<<< orphan*/ ) ; 
 scalar_t__ eap_fast_parse_pac_info (struct eap_fast_pac*,int,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int eap_fast_process_pac_info(struct eap_fast_pac *entry)
{
	struct pac_tlv_hdr *hdr;
	u8 *pos;
	size_t left, len;
	int type;

	/* RFC 5422, Section 4.2.4 */

	/* PAC-Type defaults to Tunnel PAC (Type 1) */
	entry->pac_type = PAC_TYPE_TUNNEL_PAC;

	pos = entry->pac_info;
	left = entry->pac_info_len;
	while (left > sizeof(*hdr)) {
		hdr = (struct pac_tlv_hdr *) pos;
		type = be_to_host16(hdr->type);
		len = be_to_host16(hdr->len);
		pos += sizeof(*hdr);
		left -= sizeof(*hdr);
		if (len > left) {
			wpa_printf(MSG_DEBUG, "EAP-FAST: PAC-Info overrun "
				   "(type=%d len=%lu left=%lu)",
				   type, (unsigned long) len,
				   (unsigned long) left);
			return -1;
		}

		if (eap_fast_parse_pac_info(entry, type, pos, len) < 0)
			return -1;

		pos += len;
		left -= len;
	}

	if (entry->a_id == NULL || entry->a_id_info == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-FAST: PAC-Info does not include "
			   "all the required fields");
		return -1;
	}

	return 0;
}