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
struct eap_tlv_hdr {int dummy; } ;
struct eap_tlv_crypto_binding_tlv {int /*<<< orphan*/  compound_mac; int /*<<< orphan*/  nonce; int /*<<< orphan*/  subtype; int /*<<< orphan*/  received_version; int /*<<< orphan*/  version; void* length; void* tlv_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_FAST_CMK_LEN ; 
 int /*<<< orphan*/  EAP_FAST_VERSION ; 
 int /*<<< orphan*/  EAP_TLV_CRYPTO_BINDING_SUBTYPE_RESPONSE ; 
 int EAP_TLV_CRYPTO_BINDING_TLV ; 
 int EAP_TLV_TYPE_MANDATORY ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  hmac_sha1 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* host_to_be16 (int) ; 
 int /*<<< orphan*/  inc_byte_array (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_fast_write_crypto_binding(
	struct eap_tlv_crypto_binding_tlv *rbind,
	struct eap_tlv_crypto_binding_tlv *_bind, const u8 *cmk)
{
	rbind->tlv_type = host_to_be16(EAP_TLV_TYPE_MANDATORY |
				       EAP_TLV_CRYPTO_BINDING_TLV);
	rbind->length = host_to_be16(sizeof(*rbind) -
				     sizeof(struct eap_tlv_hdr));
	rbind->version = EAP_FAST_VERSION;
	rbind->received_version = _bind->version;
	rbind->subtype = EAP_TLV_CRYPTO_BINDING_SUBTYPE_RESPONSE;
	os_memcpy(rbind->nonce, _bind->nonce, sizeof(_bind->nonce));
	inc_byte_array(rbind->nonce, sizeof(rbind->nonce));
	hmac_sha1(cmk, EAP_FAST_CMK_LEN, (u8 *) rbind, sizeof(*rbind),
		  rbind->compound_mac);

	wpa_printf(MSG_DEBUG, "EAP-FAST: Reply Crypto-Binding TLV: Version %d "
		   "Received Version %d SubType %d",
		   rbind->version, rbind->received_version, rbind->subtype);
	wpa_hexdump(MSG_MSGDUMP, "EAP-FAST: NONCE",
		    rbind->nonce, sizeof(rbind->nonce));
	wpa_hexdump(MSG_MSGDUMP, "EAP-FAST: Compound MAC",
		    rbind->compound_mac, sizeof(rbind->compound_mac));
}