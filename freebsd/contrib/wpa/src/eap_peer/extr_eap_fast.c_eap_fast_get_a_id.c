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
struct pac_tlv_hdr {int /*<<< orphan*/  type; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int PAC_TYPE_A_ID ; 
 int be_to_host16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static const u8 * eap_fast_get_a_id(const u8 *buf, size_t len, size_t *id_len)
{
	const u8 *a_id;
	const struct pac_tlv_hdr *hdr;

	/*
	 * Parse authority identity (A-ID) from the EAP-FAST/Start. This
	 * supports both raw A-ID and one inside an A-ID TLV.
	 */
	a_id = buf;
	*id_len = len;
	if (len > sizeof(*hdr)) {
		int tlen;
		hdr = (const struct pac_tlv_hdr *) buf;
		tlen = be_to_host16(hdr->len);
		if (be_to_host16(hdr->type) == PAC_TYPE_A_ID &&
		    sizeof(*hdr) + tlen <= len) {
			wpa_printf(MSG_DEBUG, "EAP-FAST: A-ID was in TLV "
				   "(Start)");
			a_id = (const u8 *) (hdr + 1);
			*id_len = tlen;
		}
	}
	wpa_hexdump_ascii(MSG_DEBUG, "EAP-FAST: A-ID", a_id, *id_len);

	return a_id;
}