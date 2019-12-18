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
struct eap_sim_attrs {int notification; int counter; int selected_version; int client_error_code; int const* rand; size_t num_chal; int const* autn; int const* nonce_mt; int const* mac; int const* identity; size_t identity_len; int const* version_list; size_t version_list_len; int counter_too_small; int const* nonce_s; int const* iv; int const* encr_data; size_t encr_data_len; int const* next_pseudonym; size_t next_pseudonym_len; int const* next_reauth_id; size_t next_reauth_id_len; int const* res; size_t res_len; int const* auts; int const* checkcode; size_t checkcode_len; int result_ind; int const* kdf_input; size_t kdf_input_len; size_t kdf_count; int const* bidding; void** kdf; void* res_len_bits; int /*<<< orphan*/  id_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANY_ID ; 
 size_t EAP_AKA_AUTN_LEN ; 
 size_t EAP_AKA_AUTS_LEN ; 
 size_t EAP_AKA_CHECKCODE_LEN ; 
 size_t EAP_AKA_MAX_RES_LEN ; 
 size_t EAP_AKA_MIN_RES_LEN ; 
 size_t EAP_AKA_PRIME_CHECKCODE_LEN ; 
 size_t EAP_AKA_PRIME_KDF_MAX ; 
 size_t EAP_AKA_RAND_LEN ; 
#define  EAP_SIM_AT_ANY_ID_REQ 154 
#define  EAP_SIM_AT_AUTN 153 
#define  EAP_SIM_AT_AUTS 152 
#define  EAP_SIM_AT_BIDDING 151 
#define  EAP_SIM_AT_CHECKCODE 150 
#define  EAP_SIM_AT_CLIENT_ERROR_CODE 149 
#define  EAP_SIM_AT_COUNTER 148 
#define  EAP_SIM_AT_COUNTER_TOO_SMALL 147 
#define  EAP_SIM_AT_ENCR_DATA 146 
#define  EAP_SIM_AT_FULLAUTH_ID_REQ 145 
#define  EAP_SIM_AT_IDENTITY 144 
#define  EAP_SIM_AT_IV 143 
#define  EAP_SIM_AT_KDF 142 
#define  EAP_SIM_AT_KDF_INPUT 141 
#define  EAP_SIM_AT_MAC 140 
#define  EAP_SIM_AT_NEXT_PSEUDONYM 139 
#define  EAP_SIM_AT_NEXT_REAUTH_ID 138 
#define  EAP_SIM_AT_NONCE_MT 137 
#define  EAP_SIM_AT_NONCE_S 136 
#define  EAP_SIM_AT_NOTIFICATION 135 
#define  EAP_SIM_AT_PADDING 134 
#define  EAP_SIM_AT_PERMANENT_ID_REQ 133 
#define  EAP_SIM_AT_RAND 132 
#define  EAP_SIM_AT_RES 131 
#define  EAP_SIM_AT_RESULT_IND 130 
#define  EAP_SIM_AT_SELECTED_VERSION 129 
#define  EAP_SIM_AT_VERSION_LIST 128 
 int /*<<< orphan*/  EAP_SIM_MAC_LEN ; 
 int /*<<< orphan*/  EAP_SIM_NONCE_MT_LEN ; 
 int /*<<< orphan*/  EAP_SIM_NONCE_S_LEN ; 
 int /*<<< orphan*/  FULLAUTH_ID ; 
 size_t GSM_RAND_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  NO_ID_REQ ; 
 int /*<<< orphan*/  PERMANENT_ID ; 
 void* WPA_GET_BE16 (int const*) ; 
 int /*<<< orphan*/  os_memset (struct eap_sim_attrs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int eap_sim_parse_attr(const u8 *start, const u8 *end,
		       struct eap_sim_attrs *attr, int aka, int encr)
{
	const u8 *pos = start, *apos;
	size_t alen, plen, i, list_len;

	os_memset(attr, 0, sizeof(*attr));
	attr->id_req = NO_ID_REQ;
	attr->notification = -1;
	attr->counter = -1;
	attr->selected_version = -1;
	attr->client_error_code = -1;

	while (pos < end) {
		if (pos + 2 > end) {
			wpa_printf(MSG_INFO, "EAP-SIM: Attribute overflow(1)");
			return -1;
		}
		wpa_printf(MSG_MSGDUMP, "EAP-SIM: Attribute: Type=%d Len=%d",
			   pos[0], pos[1] * 4);
		if (pos + pos[1] * 4 > end) {
			wpa_printf(MSG_INFO, "EAP-SIM: Attribute overflow "
				   "(pos=%p len=%d end=%p)",
				   pos, pos[1] * 4, end);
			return -1;
		}
		if (pos[1] == 0) {
			wpa_printf(MSG_INFO, "EAP-SIM: Attribute underflow");
			return -1;
		}
		apos = pos + 2;
		alen = pos[1] * 4 - 2;
		wpa_hexdump(MSG_MSGDUMP, "EAP-SIM: Attribute data",
			    apos, alen);

		switch (pos[0]) {
		case EAP_SIM_AT_RAND:
			wpa_printf(MSG_DEBUG, "EAP-SIM: AT_RAND");
			apos += 2;
			alen -= 2;
			if ((!aka && (alen % GSM_RAND_LEN)) ||
			    (aka && alen != EAP_AKA_RAND_LEN)) {
				wpa_printf(MSG_INFO, "EAP-SIM: Invalid AT_RAND"
					   " (len %lu)",
					   (unsigned long) alen);
				return -1;
			}
			attr->rand = apos;
			attr->num_chal = alen / GSM_RAND_LEN;
			break;
		case EAP_SIM_AT_AUTN:
			wpa_printf(MSG_DEBUG, "EAP-AKA: AT_AUTN");
			if (!aka) {
				wpa_printf(MSG_DEBUG, "EAP-SIM: "
					   "Unexpected AT_AUTN");
				return -1;
			}
			apos += 2;
			alen -= 2;
			if (alen != EAP_AKA_AUTN_LEN) {
				wpa_printf(MSG_INFO, "EAP-AKA: Invalid AT_AUTN"
					   " (len %lu)",
					   (unsigned long) alen);
				return -1;
			}
			attr->autn = apos;
			break;
		case EAP_SIM_AT_PADDING:
			if (!encr) {
				wpa_printf(MSG_ERROR, "EAP-SIM: Unencrypted "
					   "AT_PADDING");
				return -1;
			}
			wpa_printf(MSG_DEBUG, "EAP-SIM: (encr) AT_PADDING");
			for (i = 2; i < alen; i++) {
				if (apos[i] != 0) {
					wpa_printf(MSG_INFO, "EAP-SIM: (encr) "
						   "AT_PADDING used a non-zero"
						   " padding byte");
					wpa_hexdump(MSG_DEBUG, "EAP-SIM: "
						    "(encr) padding bytes",
						    apos + 2, alen - 2);
					return -1;
				}
			}
			break;
		case EAP_SIM_AT_NONCE_MT:
			wpa_printf(MSG_DEBUG, "EAP-SIM: AT_NONCE_MT");
			if (alen != 2 + EAP_SIM_NONCE_MT_LEN) {
				wpa_printf(MSG_INFO, "EAP-SIM: Invalid "
					   "AT_NONCE_MT length");
				return -1;
			}
			attr->nonce_mt = apos + 2;
			break;
		case EAP_SIM_AT_PERMANENT_ID_REQ:
			wpa_printf(MSG_DEBUG, "EAP-SIM: AT_PERMANENT_ID_REQ");
			attr->id_req = PERMANENT_ID;
			break;
		case EAP_SIM_AT_MAC:
			wpa_printf(MSG_DEBUG, "EAP-SIM: AT_MAC");
			if (alen != 2 + EAP_SIM_MAC_LEN) {
				wpa_printf(MSG_INFO, "EAP-SIM: Invalid AT_MAC "
					   "length");
				return -1;
			}
			attr->mac = apos + 2;
			break;
		case EAP_SIM_AT_NOTIFICATION:
			if (alen != 2) {
				wpa_printf(MSG_INFO, "EAP-SIM: Invalid "
					   "AT_NOTIFICATION length %lu",
					   (unsigned long) alen);
				return -1;
			}
			attr->notification = apos[0] * 256 + apos[1];
			wpa_printf(MSG_DEBUG, "EAP-SIM: AT_NOTIFICATION %d",
				   attr->notification);
			break;
		case EAP_SIM_AT_ANY_ID_REQ:
			wpa_printf(MSG_DEBUG, "EAP-SIM: AT_ANY_ID_REQ");
			attr->id_req = ANY_ID;
			break;
		case EAP_SIM_AT_IDENTITY:
			wpa_printf(MSG_DEBUG, "EAP-SIM: AT_IDENTITY");
			plen = WPA_GET_BE16(apos);
			apos += 2;
			alen -= 2;
			if (plen > alen) {
				wpa_printf(MSG_INFO, "EAP-SIM: Invalid "
					   "AT_IDENTITY (Actual Length %lu, "
					   "remaining length %lu)",
					   (unsigned long) plen,
					   (unsigned long) alen);
				return -1;
			}

			attr->identity = apos;
			attr->identity_len = plen;
			break;
		case EAP_SIM_AT_VERSION_LIST:
			if (aka) {
				wpa_printf(MSG_DEBUG, "EAP-AKA: "
					   "Unexpected AT_VERSION_LIST");
				return -1;
			}
			list_len = apos[0] * 256 + apos[1];
			wpa_printf(MSG_DEBUG, "EAP-SIM: AT_VERSION_LIST");
			if (list_len < 2 || list_len > alen - 2) {
				wpa_printf(MSG_WARNING, "EAP-SIM: Invalid "
					   "AT_VERSION_LIST (list_len=%lu "
					   "attr_len=%lu)",
					   (unsigned long) list_len,
					   (unsigned long) alen);
				return -1;
			}
			attr->version_list = apos + 2;
			attr->version_list_len = list_len;
			break;
		case EAP_SIM_AT_SELECTED_VERSION:
			wpa_printf(MSG_DEBUG, "EAP-SIM: AT_SELECTED_VERSION");
			if (alen != 2) {
				wpa_printf(MSG_INFO, "EAP-SIM: Invalid "
					   "AT_SELECTED_VERSION length %lu",
					   (unsigned long) alen);
				return -1;
			}
			attr->selected_version = apos[0] * 256 + apos[1];
			wpa_printf(MSG_DEBUG, "EAP-SIM: AT_SELECTED_VERSION "
				   "%d", attr->selected_version);
			break;
		case EAP_SIM_AT_FULLAUTH_ID_REQ:
			wpa_printf(MSG_DEBUG, "EAP-SIM: AT_FULLAUTH_ID_REQ");
			attr->id_req = FULLAUTH_ID;
			break;
		case EAP_SIM_AT_COUNTER:
			if (!encr) {
				wpa_printf(MSG_ERROR, "EAP-SIM: Unencrypted "
					   "AT_COUNTER");
				return -1;
			}
			if (alen != 2) {
				wpa_printf(MSG_INFO, "EAP-SIM: (encr) Invalid "
					   "AT_COUNTER (alen=%lu)",
					   (unsigned long) alen);
				return -1;
			}
			attr->counter = apos[0] * 256 + apos[1];
			wpa_printf(MSG_DEBUG, "EAP-SIM: (encr) AT_COUNTER %d",
				   attr->counter);
			break;
		case EAP_SIM_AT_COUNTER_TOO_SMALL:
			if (!encr) {
				wpa_printf(MSG_ERROR, "EAP-SIM: Unencrypted "
					   "AT_COUNTER_TOO_SMALL");
				return -1;
			}
			if (alen != 2) {
				wpa_printf(MSG_INFO, "EAP-SIM: (encr) Invalid "
					   "AT_COUNTER_TOO_SMALL (alen=%lu)",
					   (unsigned long) alen);
				return -1;
			}
			wpa_printf(MSG_DEBUG, "EAP-SIM: (encr) "
				   "AT_COUNTER_TOO_SMALL");
			attr->counter_too_small = 1;
			break;
		case EAP_SIM_AT_NONCE_S:
			if (!encr) {
				wpa_printf(MSG_ERROR, "EAP-SIM: Unencrypted "
					   "AT_NONCE_S");
				return -1;
			}
			wpa_printf(MSG_DEBUG, "EAP-SIM: (encr) "
				   "AT_NONCE_S");
			if (alen != 2 + EAP_SIM_NONCE_S_LEN) {
				wpa_printf(MSG_INFO, "EAP-SIM: (encr) Invalid "
					   "AT_NONCE_S (alen=%lu)",
					   (unsigned long) alen);
				return -1;
			}
			attr->nonce_s = apos + 2;
			break;
		case EAP_SIM_AT_CLIENT_ERROR_CODE:
			if (alen != 2) {
				wpa_printf(MSG_INFO, "EAP-SIM: Invalid "
					   "AT_CLIENT_ERROR_CODE length %lu",
					   (unsigned long) alen);
				return -1;
			}
			attr->client_error_code = apos[0] * 256 + apos[1];
			wpa_printf(MSG_DEBUG, "EAP-SIM: AT_CLIENT_ERROR_CODE "
				   "%d", attr->client_error_code);
			break;
		case EAP_SIM_AT_IV:
			wpa_printf(MSG_DEBUG, "EAP-SIM: AT_IV");
			if (alen != 2 + EAP_SIM_MAC_LEN) {
				wpa_printf(MSG_INFO, "EAP-SIM: Invalid AT_IV "
					   "length %lu", (unsigned long) alen);
				return -1;
			}
			attr->iv = apos + 2;
			break;
		case EAP_SIM_AT_ENCR_DATA:
			wpa_printf(MSG_DEBUG, "EAP-SIM: AT_ENCR_DATA");
			attr->encr_data = apos + 2;
			attr->encr_data_len = alen - 2;
			if (attr->encr_data_len % 16) {
				wpa_printf(MSG_INFO, "EAP-SIM: Invalid "
					   "AT_ENCR_DATA length %lu",
					   (unsigned long)
					   attr->encr_data_len);
				return -1;
			}
			break;
		case EAP_SIM_AT_NEXT_PSEUDONYM:
			if (!encr) {
				wpa_printf(MSG_ERROR, "EAP-SIM: Unencrypted "
					   "AT_NEXT_PSEUDONYM");
				return -1;
			}
			wpa_printf(MSG_DEBUG, "EAP-SIM: (encr) "
				   "AT_NEXT_PSEUDONYM");
			plen = apos[0] * 256 + apos[1];
			if (plen > alen - 2) {
				wpa_printf(MSG_INFO, "EAP-SIM: (encr) Invalid"
					   " AT_NEXT_PSEUDONYM (actual"
					   " len %lu, attr len %lu)",
					   (unsigned long) plen,
					   (unsigned long) alen);
				return -1;
			}
			attr->next_pseudonym = pos + 4;
			attr->next_pseudonym_len = plen;
			break;
		case EAP_SIM_AT_NEXT_REAUTH_ID:
			if (!encr) {
				wpa_printf(MSG_ERROR, "EAP-SIM: Unencrypted "
					   "AT_NEXT_REAUTH_ID");
				return -1;
			}
			wpa_printf(MSG_DEBUG, "EAP-SIM: (encr) "
				   "AT_NEXT_REAUTH_ID");
			plen = apos[0] * 256 + apos[1];
			if (plen > alen - 2) {
				wpa_printf(MSG_INFO, "EAP-SIM: (encr) Invalid"
					   " AT_NEXT_REAUTH_ID (actual"
					   " len %lu, attr len %lu)",
					   (unsigned long) plen,
					   (unsigned long) alen);
				return -1;
			}
			attr->next_reauth_id = pos + 4;
			attr->next_reauth_id_len = plen;
			break;
		case EAP_SIM_AT_RES:
			wpa_printf(MSG_DEBUG, "EAP-SIM: AT_RES");
			attr->res_len_bits = WPA_GET_BE16(apos);
			apos += 2;
			alen -= 2;
			if (!aka || alen < EAP_AKA_MIN_RES_LEN ||
			    alen > EAP_AKA_MAX_RES_LEN) {
				wpa_printf(MSG_INFO, "EAP-SIM: Invalid AT_RES "
					   "(len %lu)",
					   (unsigned long) alen);
				return -1;
			}
			attr->res = apos;
			attr->res_len = alen;
			break;
		case EAP_SIM_AT_AUTS:
			wpa_printf(MSG_DEBUG, "EAP-AKA: AT_AUTS");
			if (!aka) {
				wpa_printf(MSG_DEBUG, "EAP-SIM: "
					   "Unexpected AT_AUTS");
				return -1;
			}
			if (alen != EAP_AKA_AUTS_LEN) {
				wpa_printf(MSG_INFO, "EAP-AKA: Invalid AT_AUTS"
					   " (len %lu)",
					   (unsigned long) alen);
				return -1;
			}
			attr->auts = apos;
			break;
		case EAP_SIM_AT_CHECKCODE:
			wpa_printf(MSG_DEBUG, "EAP-AKA: AT_CHECKCODE");
			if (!aka) {
				wpa_printf(MSG_DEBUG, "EAP-SIM: "
					   "Unexpected AT_CHECKCODE");
				return -1;
			}
			apos += 2;
			alen -= 2;
			if (alen != 0 && alen != EAP_AKA_CHECKCODE_LEN &&
			    alen != EAP_AKA_PRIME_CHECKCODE_LEN) {
				wpa_printf(MSG_INFO, "EAP-AKA: Invalid "
					   "AT_CHECKCODE (len %lu)",
					   (unsigned long) alen);
				return -1;
			}
			attr->checkcode = apos;
			attr->checkcode_len = alen;
			break;
		case EAP_SIM_AT_RESULT_IND:
			if (encr) {
				wpa_printf(MSG_ERROR, "EAP-SIM: Encrypted "
					   "AT_RESULT_IND");
				return -1;
			}
			if (alen != 2) {
				wpa_printf(MSG_INFO, "EAP-SIM: Invalid "
					   "AT_RESULT_IND (alen=%lu)",
					   (unsigned long) alen);
				return -1;
			}
			wpa_printf(MSG_DEBUG, "EAP-SIM: AT_RESULT_IND");
			attr->result_ind = 1;
			break;
#if defined(EAP_AKA_PRIME) || defined(EAP_SERVER_AKA_PRIME)
		case EAP_SIM_AT_KDF_INPUT:
			if (aka != 2) {
				wpa_printf(MSG_INFO, "EAP-AKA: Unexpected "
					   "AT_KDF_INPUT");
				return -1;
			}

			wpa_printf(MSG_DEBUG, "EAP-AKA: AT_KDF_INPUT");
			plen = WPA_GET_BE16(apos);
			apos += 2;
			alen -= 2;
			if (plen > alen) {
				wpa_printf(MSG_INFO, "EAP-AKA': Invalid "
					   "AT_KDF_INPUT (Actual Length %lu, "
					   "remaining length %lu)",
					   (unsigned long) plen,
					   (unsigned long) alen);
				return -1;
			}
			attr->kdf_input = apos;
			attr->kdf_input_len = plen;
			break;
		case EAP_SIM_AT_KDF:
			if (aka != 2) {
				wpa_printf(MSG_INFO, "EAP-AKA: Unexpected "
					   "AT_KDF");
				return -1;
			}

			wpa_printf(MSG_DEBUG, "EAP-AKA: AT_KDF");
			if (alen != 2) {
				wpa_printf(MSG_INFO, "EAP-AKA': Invalid "
					   "AT_KDF (len %lu)",
					   (unsigned long) alen);
				return -1;
			}
			if (attr->kdf_count == EAP_AKA_PRIME_KDF_MAX) {
				wpa_printf(MSG_DEBUG, "EAP-AKA': Too many "
					   "AT_KDF attributes - ignore this");
				break;
			}
			attr->kdf[attr->kdf_count] = WPA_GET_BE16(apos);
			attr->kdf_count++;
			break;
		case EAP_SIM_AT_BIDDING:
			wpa_printf(MSG_DEBUG, "EAP-AKA: AT_BIDDING");
			if (alen != 2) {
				wpa_printf(MSG_INFO, "EAP-AKA: Invalid "
					   "AT_BIDDING (len %lu)",
					   (unsigned long) alen);
				return -1;
			}
			attr->bidding = apos;
			break;
#endif /* EAP_AKA_PRIME || EAP_SERVER_AKA_PRIME */
		default:
			if (pos[0] < 128) {
				wpa_printf(MSG_INFO, "EAP-SIM: Unrecognized "
					   "non-skippable attribute %d",
					   pos[0]);
				return -1;
			}

			wpa_printf(MSG_DEBUG, "EAP-SIM: Unrecognized skippable"
				   " attribute %d ignored", pos[0]);
			break;
		}

		pos += pos[1] * 4;
	}

	wpa_printf(MSG_DEBUG, "EAP-SIM: Attributes parsed successfully "
		   "(aka=%d encr=%d)", aka, encr);

	return 0;
}