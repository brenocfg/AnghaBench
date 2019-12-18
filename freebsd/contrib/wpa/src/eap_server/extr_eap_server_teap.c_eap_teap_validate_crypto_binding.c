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
struct eap_teap_data {scalar_t__ peer_version; int* crypto_binding_nonce; scalar_t__ cmk_emsk_available; int /*<<< orphan*/  cmk_emsk; int /*<<< orphan*/  peer_outer_tlvs; int /*<<< orphan*/  server_outer_tlvs; int /*<<< orphan*/  tls_cs; int /*<<< orphan*/  cmk_msk; } ;

/* Variables and functions */
 int EAP_TEAP_COMPOUND_MAC_LEN ; 
 int EAP_TEAP_NONCE_LEN ; 
 scalar_t__ EAP_TEAP_VERSION ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int TEAP_CRYPTO_BINDING_EMSK_AND_MSK_CMAC ; 
 int TEAP_CRYPTO_BINDING_EMSK_CMAC ; 
 int TEAP_CRYPTO_BINDING_MSK_CMAC ; 
 int TEAP_CRYPTO_BINDING_SUBTYPE_RESPONSE ; 
 scalar_t__ eap_teap_compound_mac (int /*<<< orphan*/ ,struct teap_tlv_crypto_binding const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ os_memcmp_const (int*,int*,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int eap_teap_validate_crypto_binding(
	struct eap_teap_data *data, const struct teap_tlv_crypto_binding *cb,
	size_t bind_len)
{
	u8 flags, subtype;

	subtype = cb->subtype & 0x0f;
	flags = cb->subtype >> 4;

	wpa_printf(MSG_DEBUG,
		   "EAP-TEAP: Reply Crypto-Binding TLV: Version %u Received Version %u Flags %u Sub-Type %u",
		   cb->version, cb->received_version, flags, subtype);
	wpa_hexdump(MSG_MSGDUMP, "EAP-TEAP: Nonce",
		    cb->nonce, sizeof(cb->nonce));
	wpa_hexdump(MSG_MSGDUMP, "EAP-TEAP: EMSK Compound MAC",
		    cb->emsk_compound_mac, sizeof(cb->emsk_compound_mac));
	wpa_hexdump(MSG_MSGDUMP, "EAP-TEAP: MSK Compound MAC",
		    cb->msk_compound_mac, sizeof(cb->msk_compound_mac));

	if (cb->version != EAP_TEAP_VERSION ||
	    cb->received_version != data->peer_version) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: Unexpected version in Crypto-Binding: Version %u Received Version %u",
			   cb->version, cb->received_version);
		return -1;
	}

	if (flags < 1 || flags > 3) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: Unexpected Flags in Crypto-Binding: %u",
			   flags);
		return -1;
	}

	if (subtype != TEAP_CRYPTO_BINDING_SUBTYPE_RESPONSE) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: Unexpected Sub-Type in Crypto-Binding: %u",
			   subtype);
		return -1;
	}

	if (os_memcmp_const(data->crypto_binding_nonce, cb->nonce,
			    EAP_TEAP_NONCE_LEN - 1) != 0 ||
	    (data->crypto_binding_nonce[EAP_TEAP_NONCE_LEN - 1] | 1) !=
	    cb->nonce[EAP_TEAP_NONCE_LEN - 1]) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: Invalid Nonce in Crypto-Binding");
		return -1;
	}

	if (flags == TEAP_CRYPTO_BINDING_MSK_CMAC ||
	    flags == TEAP_CRYPTO_BINDING_EMSK_AND_MSK_CMAC) {
		u8 msk_compound_mac[EAP_TEAP_COMPOUND_MAC_LEN];

		if (eap_teap_compound_mac(data->tls_cs, cb,
					  data->server_outer_tlvs,
					  data->peer_outer_tlvs, data->cmk_msk,
					  msk_compound_mac) < 0)
			return -1;
		if (os_memcmp_const(msk_compound_mac, cb->msk_compound_mac,
				    EAP_TEAP_COMPOUND_MAC_LEN) != 0) {
			wpa_hexdump(MSG_DEBUG,
				    "EAP-TEAP: Calculated MSK Compound MAC",
				    msk_compound_mac,
				    EAP_TEAP_COMPOUND_MAC_LEN);
			wpa_printf(MSG_INFO,
				   "EAP-TEAP: MSK Compound MAC did not match");
			return -1;
		}
	}

	if ((flags == TEAP_CRYPTO_BINDING_EMSK_CMAC ||
	     flags == TEAP_CRYPTO_BINDING_EMSK_AND_MSK_CMAC) &&
	    data->cmk_emsk_available) {
		u8 emsk_compound_mac[EAP_TEAP_COMPOUND_MAC_LEN];

		if (eap_teap_compound_mac(data->tls_cs, cb,
					  data->server_outer_tlvs,
					  data->peer_outer_tlvs, data->cmk_emsk,
					  emsk_compound_mac) < 0)
			return -1;
		if (os_memcmp_const(emsk_compound_mac, cb->emsk_compound_mac,
				    EAP_TEAP_COMPOUND_MAC_LEN) != 0) {
			wpa_hexdump(MSG_DEBUG,
				    "EAP-TEAP: Calculated EMSK Compound MAC",
				    emsk_compound_mac,
				    EAP_TEAP_COMPOUND_MAC_LEN);
			wpa_printf(MSG_INFO,
				   "EAP-TEAP: EMSK Compound MAC did not match");
			return -1;
		}
	}

	if (flags == TEAP_CRYPTO_BINDING_EMSK_CMAC &&
	    !data->cmk_emsk_available) {
		wpa_printf(MSG_INFO,
			   "EAP-TEAP: Peer included only EMSK Compound MAC, but no locally generated inner EAP EMSK to validate this");
		return -1;
	}

	return 0;
}