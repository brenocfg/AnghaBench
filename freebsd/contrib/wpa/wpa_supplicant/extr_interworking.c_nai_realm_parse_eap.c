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
struct nai_realm_eap {int inner_non_eap; int inner_method; int cred_type; int tunneled_cred_type; int /*<<< orphan*/  method; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_TYPE_TTLS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
#define  NAI_REALM_EAP_AUTH_CRED_TYPE 135 
#define  NAI_REALM_EAP_AUTH_INNER_AUTH_EAP_METHOD 134 
#define  NAI_REALM_EAP_AUTH_NON_EAP_INNER_AUTH 133 
#define  NAI_REALM_EAP_AUTH_TUNNELED_CRED_TYPE 132 
#define  NAI_REALM_INNER_NON_EAP_CHAP 131 
#define  NAI_REALM_INNER_NON_EAP_MSCHAP 130 
#define  NAI_REALM_INNER_NON_EAP_MSCHAPV2 129 
#define  NAI_REALM_INNER_NON_EAP_PAP 128 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static const u8 * nai_realm_parse_eap(struct nai_realm_eap *e, const u8 *pos,
				      const u8 *end)
{
	u8 elen, auth_count, a;
	const u8 *e_end;

	if (end - pos < 3) {
		wpa_printf(MSG_DEBUG, "No room for EAP Method fixed fields");
		return NULL;
	}

	elen = *pos++;
	if (elen > end - pos || elen < 2) {
		wpa_printf(MSG_DEBUG, "No room for EAP Method subfield");
		return NULL;
	}
	e_end = pos + elen;
	e->method = *pos++;
	auth_count = *pos++;
	wpa_printf(MSG_DEBUG, "EAP Method: len=%u method=%u auth_count=%u",
		   elen, e->method, auth_count);

	for (a = 0; a < auth_count; a++) {
		u8 id, len;

		if (end - pos < 2) {
			wpa_printf(MSG_DEBUG,
				   "No room for Authentication Parameter subfield header");
			return NULL;
		}

		id = *pos++;
		len = *pos++;
		if (len > end - pos) {
			wpa_printf(MSG_DEBUG,
				   "No room for Authentication Parameter subfield");
			return NULL;
		}

		switch (id) {
		case NAI_REALM_EAP_AUTH_NON_EAP_INNER_AUTH:
			if (len < 1)
				break;
			e->inner_non_eap = *pos;
			if (e->method != EAP_TYPE_TTLS)
				break;
			switch (*pos) {
			case NAI_REALM_INNER_NON_EAP_PAP:
				wpa_printf(MSG_DEBUG, "EAP-TTLS/PAP");
				break;
			case NAI_REALM_INNER_NON_EAP_CHAP:
				wpa_printf(MSG_DEBUG, "EAP-TTLS/CHAP");
				break;
			case NAI_REALM_INNER_NON_EAP_MSCHAP:
				wpa_printf(MSG_DEBUG, "EAP-TTLS/MSCHAP");
				break;
			case NAI_REALM_INNER_NON_EAP_MSCHAPV2:
				wpa_printf(MSG_DEBUG, "EAP-TTLS/MSCHAPV2");
				break;
			}
			break;
		case NAI_REALM_EAP_AUTH_INNER_AUTH_EAP_METHOD:
			if (len < 1)
				break;
			e->inner_method = *pos;
			wpa_printf(MSG_DEBUG, "Inner EAP method: %u",
				   e->inner_method);
			break;
		case NAI_REALM_EAP_AUTH_CRED_TYPE:
			if (len < 1)
				break;
			e->cred_type = *pos;
			wpa_printf(MSG_DEBUG, "Credential Type: %u",
				   e->cred_type);
			break;
		case NAI_REALM_EAP_AUTH_TUNNELED_CRED_TYPE:
			if (len < 1)
				break;
			e->tunneled_cred_type = *pos;
			wpa_printf(MSG_DEBUG, "Tunneled EAP Method Credential "
				   "Type: %u", e->tunneled_cred_type);
			break;
		default:
			wpa_printf(MSG_DEBUG, "Unsupported Authentication "
				   "Parameter: id=%u len=%u", id, len);
			wpa_hexdump(MSG_DEBUG, "Authentication Parameter "
				    "Value", pos, len);
			break;
		}

		pos += len;
	}

	return e_end;
}