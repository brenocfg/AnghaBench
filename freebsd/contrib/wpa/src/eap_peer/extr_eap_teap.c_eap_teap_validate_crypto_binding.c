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
struct teap_tlv_crypto_binding {int subtype; scalar_t__ version; scalar_t__ received_version; int* nonce; int* emsk_compound_mac; int* msk_compound_mac; } ;
struct eap_teap_data {scalar_t__ received_version; } ;

/* Variables and functions */
 int EAP_TEAP_NONCE_LEN ; 
 scalar_t__ EAP_TEAP_VERSION ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int TEAP_CRYPTO_BINDING_SUBTYPE_REQUEST ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
eap_teap_validate_crypto_binding(struct eap_teap_data *data,
				 const struct teap_tlv_crypto_binding *cb)
{
	u8 flags, subtype;

	subtype = cb->subtype & 0x0f;
	flags = cb->subtype >> 4;

	wpa_printf(MSG_DEBUG,
		   "EAP-TEAP: Crypto-Binding TLV: Version %u Received Version %u Flags %u Sub-Type %u",
		   cb->version, cb->received_version, flags, subtype);
	wpa_hexdump(MSG_MSGDUMP, "EAP-TEAP: Nonce",
		    cb->nonce, sizeof(cb->nonce));
	wpa_hexdump(MSG_MSGDUMP, "EAP-TEAP: EMSK Compound MAC",
		    cb->emsk_compound_mac, sizeof(cb->emsk_compound_mac));
	wpa_hexdump(MSG_MSGDUMP, "EAP-TEAP: MSK Compound MAC",
		    cb->msk_compound_mac, sizeof(cb->msk_compound_mac));

	if (cb->version != EAP_TEAP_VERSION ||
	    cb->received_version != data->received_version ||
	    subtype != TEAP_CRYPTO_BINDING_SUBTYPE_REQUEST ||
	    flags < 1 || flags > 3) {
		wpa_printf(MSG_INFO,
			   "EAP-TEAP: Invalid Version/Flags/Sub-Type in Crypto-Binding TLV: Version %u Received Version %u Flags %u Sub-Type %u",
			   cb->version, cb->received_version, flags, subtype);
		return -1;
	}

	if (cb->nonce[EAP_TEAP_NONCE_LEN - 1] & 0x01) {
		wpa_printf(MSG_INFO,
			   "EAP-TEAP: Invalid Crypto-Binding TLV Nonce in request");
		return -1;
	}

	return 0;
}