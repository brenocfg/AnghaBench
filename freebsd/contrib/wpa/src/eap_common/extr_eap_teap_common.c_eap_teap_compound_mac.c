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
typedef  int /*<<< orphan*/  u16 ;
struct wpabuf {int dummy; } ;
struct teap_tlv_hdr {int dummy; } ;
struct teap_tlv_crypto_binding {int /*<<< orphan*/  msk_compound_mac; int /*<<< orphan*/  emsk_compound_mac; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_TEAP_CMK_LEN ; 
 int /*<<< orphan*/  EAP_TEAP_COMPOUND_MAC_LEN ; 
 int /*<<< orphan*/  EAP_TYPE_TEAP ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int be_to_host16 (int /*<<< orphan*/ ) ; 
 int eap_teap_tls_mac (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,struct teap_tlv_crypto_binding const*,size_t) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct teap_tlv_crypto_binding const* wpabuf_head (struct wpabuf const*) ; 
 size_t wpabuf_len (struct wpabuf const*) ; 

int eap_teap_compound_mac(u16 tls_cs, const struct teap_tlv_crypto_binding *cb,
			  const struct wpabuf *server_outer_tlvs,
			  const struct wpabuf *peer_outer_tlvs,
			  const u8 *cmk, u8 *compound_mac)
{
	u8 *pos, *buffer;
	size_t bind_len, buffer_len;
	struct teap_tlv_crypto_binding *tmp_cb;
	int res;

	/* RFC 7170, Section 5.3 */
	bind_len = sizeof(struct teap_tlv_hdr) + be_to_host16(cb->length);
	buffer_len = bind_len + 1;
	if (server_outer_tlvs)
		buffer_len += wpabuf_len(server_outer_tlvs);
	if (peer_outer_tlvs)
		buffer_len += wpabuf_len(peer_outer_tlvs);
	buffer = os_malloc(buffer_len);
	if (!buffer)
		return -1;

	pos = buffer;
	/* 1. The entire Crypto-Binding TLV attribute with both the EMSK and MSK
	 * Compound MAC fields zeroed out. */
	os_memcpy(pos, cb, bind_len);
	pos += bind_len;
	tmp_cb = (struct teap_tlv_crypto_binding *) buffer;
	os_memset(tmp_cb->emsk_compound_mac, 0, EAP_TEAP_COMPOUND_MAC_LEN);
	os_memset(tmp_cb->msk_compound_mac, 0, EAP_TEAP_COMPOUND_MAC_LEN);

	/* 2. The EAP Type sent by the other party in the first TEAP message. */
	/* This is supposed to be the EAP Type sent by the other party in the
	 * first TEAP message, but since we cannot get here without having
	 * successfully negotiated use of TEAP, this can only be the fixed EAP
	 * Type of TEAP. */
	*pos++ = EAP_TYPE_TEAP;

	/* 3. All the Outer TLVs from the first TEAP message sent by EAP server
	 * to peer. */
	if (server_outer_tlvs) {
		os_memcpy(pos, wpabuf_head(server_outer_tlvs),
			  wpabuf_len(server_outer_tlvs));
		pos += wpabuf_len(server_outer_tlvs);
	}

	/* 4. All the Outer TLVs from the first TEAP message sent by the peer to
	 * the EAP server. */
	if (peer_outer_tlvs) {
		os_memcpy(pos, wpabuf_head(peer_outer_tlvs),
			  wpabuf_len(peer_outer_tlvs));
		pos += wpabuf_len(peer_outer_tlvs);
	}

	buffer_len = pos - buffer;

	wpa_hexdump_key(MSG_MSGDUMP,
			"EAP-TEAP: CMK for Compound MAC calculation",
			cmk, EAP_TEAP_CMK_LEN);
	wpa_hexdump(MSG_MSGDUMP,
		    "EAP-TEAP: BUFFER for Compound MAC calculation",
		    buffer, buffer_len);
	res = eap_teap_tls_mac(tls_cs, cmk, EAP_TEAP_CMK_LEN,
			       buffer, buffer_len,
			       compound_mac, EAP_TEAP_COMPOUND_MAC_LEN);
	os_free(buffer);

	return res;
}