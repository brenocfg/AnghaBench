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
struct teap_tlv_hdr {int dummy; } ;
struct teap_tlv_crypto_binding {int subtype; int /*<<< orphan*/  msk_compound_mac; int /*<<< orphan*/  emsk_compound_mac; int /*<<< orphan*/  nonce; int /*<<< orphan*/  received_version; int /*<<< orphan*/  version; void* length; void* tlv_type; } ;
struct eap_teap_data {int /*<<< orphan*/  peer_outer_tlvs; int /*<<< orphan*/  server_outer_tlvs; int /*<<< orphan*/  tls_cs; int /*<<< orphan*/  received_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_TEAP_COMPOUND_MAC_LEN ; 
 int /*<<< orphan*/  EAP_TEAP_VERSION ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int TEAP_CRYPTO_BINDING_EMSK_AND_MSK_CMAC ; 
 int TEAP_CRYPTO_BINDING_MSK_CMAC ; 
 int TEAP_CRYPTO_BINDING_SUBTYPE_RESPONSE ; 
 int TEAP_TLV_CRYPTO_BINDING ; 
 int TEAP_TLV_MANDATORY ; 
 scalar_t__ eap_teap_compound_mac (int /*<<< orphan*/ ,struct teap_tlv_crypto_binding*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*,int /*<<< orphan*/ ) ; 
 void* host_to_be16 (int) ; 
 int /*<<< orphan*/  inc_byte_array (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int eap_teap_write_crypto_binding(
	struct eap_teap_data *data,
	struct teap_tlv_crypto_binding *rbind,
	const struct teap_tlv_crypto_binding *cb,
	const u8 *cmk_msk, const u8 *cmk_emsk)
{
	u8 subtype, flags;

	rbind->tlv_type = host_to_be16(TEAP_TLV_MANDATORY |
				       TEAP_TLV_CRYPTO_BINDING);
	rbind->length = host_to_be16(sizeof(*rbind) -
				     sizeof(struct teap_tlv_hdr));
	rbind->version = EAP_TEAP_VERSION;
	rbind->received_version = data->received_version;
	/* FIX: RFC 7170 is not clear on which Flags value to use when
	 * Crypto-Binding TLV is used with Basic-Password-Auth */
	flags = cmk_emsk ? TEAP_CRYPTO_BINDING_EMSK_AND_MSK_CMAC :
		TEAP_CRYPTO_BINDING_MSK_CMAC;
	subtype = TEAP_CRYPTO_BINDING_SUBTYPE_RESPONSE;
	rbind->subtype = (flags << 4) | subtype;
	os_memcpy(rbind->nonce, cb->nonce, sizeof(cb->nonce));
	inc_byte_array(rbind->nonce, sizeof(rbind->nonce));
	os_memset(rbind->emsk_compound_mac, 0, EAP_TEAP_COMPOUND_MAC_LEN);
	os_memset(rbind->msk_compound_mac, 0, EAP_TEAP_COMPOUND_MAC_LEN);

	if (eap_teap_compound_mac(data->tls_cs, rbind, data->server_outer_tlvs,
				  data->peer_outer_tlvs, cmk_msk,
				  rbind->msk_compound_mac) < 0)
		return -1;
	if (cmk_emsk &&
	    eap_teap_compound_mac(data->tls_cs, rbind, data->server_outer_tlvs,
				  data->peer_outer_tlvs, cmk_emsk,
				  rbind->emsk_compound_mac) < 0)
		return -1;

	wpa_printf(MSG_DEBUG,
		   "EAP-TEAP: Reply Crypto-Binding TLV: Version %u Received Version %u Flags %u SubType %u",
		   rbind->version, rbind->received_version, flags, subtype);
	wpa_hexdump(MSG_MSGDUMP, "EAP-TEAP: Nonce",
		    rbind->nonce, sizeof(rbind->nonce));
	wpa_hexdump(MSG_MSGDUMP, "EAP-TEAP: EMSK Compound MAC",
		    rbind->emsk_compound_mac, sizeof(rbind->emsk_compound_mac));
	wpa_hexdump(MSG_MSGDUMP, "EAP-TEAP: MSK Compound MAC",
		    rbind->msk_compound_mac, sizeof(rbind->msk_compound_mac));

	return 0;
}