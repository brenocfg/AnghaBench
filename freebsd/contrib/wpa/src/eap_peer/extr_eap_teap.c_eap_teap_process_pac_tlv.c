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
struct pac_attr_hdr {int /*<<< orphan*/  len; int /*<<< orphan*/  type; } ;
struct eap_teap_pac {int /*<<< orphan*/  pac_info; int /*<<< orphan*/  pac_opaque; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 void* be_to_host16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_teap_parse_pac_tlv (struct eap_teap_pac*,int,int /*<<< orphan*/ *,size_t,int*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int eap_teap_process_pac_tlv(struct eap_teap_pac *entry,
				    u8 *pac, size_t pac_len)
{
	struct pac_attr_hdr *hdr;
	u8 *pos;
	size_t left, len;
	int type, pac_key_found = 0;

	pos = pac;
	left = pac_len;

	while (left > sizeof(*hdr)) {
		hdr = (struct pac_attr_hdr *) pos;
		type = be_to_host16(hdr->type);
		len = be_to_host16(hdr->len);
		pos += sizeof(*hdr);
		left -= sizeof(*hdr);
		if (len > left) {
			wpa_printf(MSG_DEBUG,
				   "EAP-TEAP: PAC TLV overrun (type=%d len=%lu left=%lu)",
				   type, (unsigned long) len,
				   (unsigned long) left);
			return -1;
		}

		eap_teap_parse_pac_tlv(entry, type, pos, len, &pac_key_found);

		pos += len;
		left -= len;
	}

	if (!pac_key_found || !entry->pac_opaque || !entry->pac_info) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: PAC TLV does not include all the required fields");
		return -1;
	}

	return 0;
}