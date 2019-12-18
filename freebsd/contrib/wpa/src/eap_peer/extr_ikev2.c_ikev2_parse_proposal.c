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
struct ikev2_proposal_data {int proposal_num; } ;
struct ikev2_proposal {int proposal_num; int type; scalar_t__ protocol_id; int spi_size; scalar_t__ num_transforms; int /*<<< orphan*/  proposal_length; } ;

/* Variables and functions */
 scalar_t__ IKEV2_PROTOCOL_IKE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int WPA_GET_BE16 (int /*<<< orphan*/ ) ; 
 int ikev2_parse_transform (struct ikev2_proposal_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int ikev2_parse_proposal(struct ikev2_proposal_data *prop,
				const u8 *pos, const u8 *end)
{
	const u8 *pend, *ppos;
	int proposal_len, i;
	const struct ikev2_proposal *p;

	if (end - pos < (int) sizeof(*p)) {
		wpa_printf(MSG_INFO, "IKEV2: Too short proposal");
		return -1;
	}

	/* FIX: AND processing if multiple proposals use the same # */

	p = (const struct ikev2_proposal *) pos;
	proposal_len = WPA_GET_BE16(p->proposal_length);
	if (proposal_len < (int) sizeof(*p) || proposal_len > end - pos) {
		wpa_printf(MSG_INFO, "IKEV2: Invalid proposal length %d",
			   proposal_len);
		return -1;
	}
	wpa_printf(MSG_DEBUG, "IKEV2: SAi1 Proposal # %d",
		   p->proposal_num);
	wpa_printf(MSG_DEBUG, "IKEV2:   Type: %d  Proposal Length: %d "
		   " Protocol ID: %d",
		   p->type, proposal_len, p->protocol_id);
	wpa_printf(MSG_DEBUG, "IKEV2:   SPI Size: %d  Transforms: %d",
		   p->spi_size, p->num_transforms);

	if (p->type != 0 && p->type != 2) {
		wpa_printf(MSG_INFO, "IKEV2: Unexpected Proposal type");
		return -1;
	}

	if (p->protocol_id != IKEV2_PROTOCOL_IKE) {
		wpa_printf(MSG_DEBUG, "IKEV2: Unexpected Protocol ID "
			   "(only IKE allowed for EAP-IKEv2)");
		return -1;
	}

	if (p->proposal_num != prop->proposal_num) {
		if (p->proposal_num == prop->proposal_num + 1)
			prop->proposal_num = p->proposal_num;
		else {
			wpa_printf(MSG_INFO, "IKEV2: Unexpected Proposal #");
			return -1;
		}
	}

	ppos = (const u8 *) (p + 1);
	pend = pos + proposal_len;
	if (p->spi_size > pend - ppos) {
		wpa_printf(MSG_INFO, "IKEV2: Not enough room for SPI "
			   "in proposal");
		return -1;
	}
	if (p->spi_size) {
		wpa_hexdump(MSG_DEBUG, "IKEV2:    SPI",
			    ppos, p->spi_size);
		ppos += p->spi_size;
	}

	/*
	 * For initial IKE_SA negotiation, SPI Size MUST be zero; for
	 * subsequent negotiations, it must be 8 for IKE. We only support
	 * initial case for now.
	 */
	if (p->spi_size != 0) {
		wpa_printf(MSG_INFO, "IKEV2: Unexpected SPI Size");
		return -1;
	}

	if (p->num_transforms == 0) {
		wpa_printf(MSG_INFO, "IKEV2: At least one transform required");
		return -1;
	}

	for (i = 0; i < (int) p->num_transforms; i++) {
		int tlen = ikev2_parse_transform(prop, ppos, pend);
		if (tlen < 0)
			return -1;
		ppos += tlen;
	}

	if (ppos != pend) {
		wpa_printf(MSG_INFO, "IKEV2: Unexpected data after "
			   "transforms");
		return -1;
	}

	return proposal_len;
}