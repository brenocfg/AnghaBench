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
struct eap_tlv_crypto_binding_tlv {scalar_t__ version; scalar_t__ received_version; scalar_t__ subtype; int /*<<< orphan*/  compound_mac; int /*<<< orphan*/  nonce; } ;

/* Variables and functions */
 scalar_t__ EAP_FAST_VERSION ; 
 scalar_t__ EAP_TLV_CRYPTO_BINDING_SUBTYPE_REQUEST ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int eap_fast_validate_crypto_binding(
	struct eap_tlv_crypto_binding_tlv *_bind)
{
	wpa_printf(MSG_DEBUG, "EAP-FAST: Crypto-Binding TLV: Version %d "
		   "Received Version %d SubType %d",
		   _bind->version, _bind->received_version, _bind->subtype);
	wpa_hexdump(MSG_MSGDUMP, "EAP-FAST: NONCE",
		    _bind->nonce, sizeof(_bind->nonce));
	wpa_hexdump(MSG_MSGDUMP, "EAP-FAST: Compound MAC",
		    _bind->compound_mac, sizeof(_bind->compound_mac));

	if (_bind->version != EAP_FAST_VERSION ||
	    _bind->received_version != EAP_FAST_VERSION ||
	    _bind->subtype != EAP_TLV_CRYPTO_BINDING_SUBTYPE_REQUEST) {
		wpa_printf(MSG_INFO, "EAP-FAST: Invalid version/subtype in "
			   "Crypto-Binding TLV: Version %d "
			   "Received Version %d SubType %d",
			   _bind->version, _bind->received_version,
			   _bind->subtype);
		return -1;
	}

	return 0;
}