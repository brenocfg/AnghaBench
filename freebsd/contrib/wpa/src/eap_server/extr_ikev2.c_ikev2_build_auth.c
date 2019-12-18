#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct ikev2_prf_alg {int hash_len; } ;
struct ikev2_payload_hdr {int /*<<< orphan*/  payload_length; scalar_t__ flags; int /*<<< orphan*/  next_payload; } ;
struct TYPE_2__ {int /*<<< orphan*/  prf; } ;
struct ikev2_initiator_data {int /*<<< orphan*/ * i_sign_msg; int /*<<< orphan*/  key_pad_len; int /*<<< orphan*/  key_pad; int /*<<< orphan*/  r_nonce_len; int /*<<< orphan*/  r_nonce; int /*<<< orphan*/  shared_secret_len; int /*<<< orphan*/  shared_secret; int /*<<< orphan*/  keys; int /*<<< orphan*/  IDi_len; int /*<<< orphan*/  IDi; TYPE_1__ proposal; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTH_SHARED_KEY_MIC ; 
 int /*<<< orphan*/  ID_KEY_ID ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ ikev2_derive_auth_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ikev2_payload_hdr*) ; 
 struct ikev2_prf_alg* ikev2_get_prf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 
 struct ikev2_payload_hdr* wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ikev2_build_auth(struct ikev2_initiator_data *data,
			    struct wpabuf *msg, u8 next_payload)
{
	struct ikev2_payload_hdr *phdr;
	size_t plen;
	const struct ikev2_prf_alg *prf;

	wpa_printf(MSG_DEBUG, "IKEV2: Adding AUTH payload");

	prf = ikev2_get_prf(data->proposal.prf);
	if (prf == NULL)
		return -1;

	/* Authentication - RFC 4306, Sect. 3.8 */
	phdr = wpabuf_put(msg, sizeof(*phdr));
	phdr->next_payload = next_payload;
	phdr->flags = 0;
	wpabuf_put_u8(msg, AUTH_SHARED_KEY_MIC);
	wpabuf_put(msg, 3); /* RESERVED */

	/* msg | Nr | prf(SK_pi,IDi') */
	if (ikev2_derive_auth_data(data->proposal.prf, data->i_sign_msg,
				   data->IDi, data->IDi_len, ID_KEY_ID,
				   &data->keys, 1, data->shared_secret,
				   data->shared_secret_len,
				   data->r_nonce, data->r_nonce_len,
				   data->key_pad, data->key_pad_len,
				   wpabuf_put(msg, prf->hash_len)) < 0) {
		wpa_printf(MSG_INFO, "IKEV2: Could not derive AUTH data");
		return -1;
	}
	wpabuf_free(data->i_sign_msg);
	data->i_sign_msg = NULL;

	plen = (u8 *) wpabuf_put(msg, 0) - (u8 *) phdr;
	WPA_PUT_BE16(phdr->payload_length, plen);
	return 0;
}