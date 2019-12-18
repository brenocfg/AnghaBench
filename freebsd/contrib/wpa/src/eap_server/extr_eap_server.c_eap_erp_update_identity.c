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
typedef  scalar_t__ u8 ;
struct erp_tlvs {int /*<<< orphan*/  keyname_len; int /*<<< orphan*/  keyname; } ;
struct eap_sm {int /*<<< orphan*/  identity_len; int /*<<< orphan*/  identity; } ;
struct eap_hdr {scalar_t__ code; } ;

/* Variables and functions */
 scalar_t__ EAP_CODE_INITIATE ; 
 scalar_t__ const EAP_ERP_TYPE_REAUTH ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ erp_parse_tlvs (scalar_t__ const*,scalar_t__ const*,struct erp_tlvs*,int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void eap_erp_update_identity(struct eap_sm *sm, const u8 *eap, size_t len)
{
#ifdef CONFIG_ERP
	const struct eap_hdr *hdr;
	const u8 *pos, *end;
	struct erp_tlvs parse;

	if (len < sizeof(*hdr) + 1)
		return;
	hdr = (const struct eap_hdr *) eap;
	end = eap + len;
	pos = (const u8 *) (hdr + 1);
	if (hdr->code != EAP_CODE_INITIATE || *pos != EAP_ERP_TYPE_REAUTH)
		return;
	pos++;
	if (pos + 3 > end)
		return;

	/* Skip Flags and SEQ */
	pos += 3;

	if (erp_parse_tlvs(pos, end, &parse, 1) < 0 || !parse.keyname)
		return;
	wpa_hexdump_ascii(MSG_DEBUG,
			  "EAP: Update identity based on EAP-Initiate/Re-auth keyName-NAI",
			  parse.keyname, parse.keyname_len);
	os_free(sm->identity);
	sm->identity = os_malloc(parse.keyname_len);
	if (sm->identity) {
		os_memcpy(sm->identity, parse.keyname, parse.keyname_len);
		sm->identity_len = parse.keyname_len;
	} else {
		sm->identity_len = 0;
	}
#endif /* CONFIG_ERP */
}