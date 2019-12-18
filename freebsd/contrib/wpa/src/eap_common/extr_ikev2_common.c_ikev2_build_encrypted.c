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
struct wpabuf {int dummy; } ;
struct ikev2_payload_hdr {int /*<<< orphan*/  payload_length; scalar_t__ flags; int /*<<< orphan*/  next_payload; } ;
struct ikev2_keys {int /*<<< orphan*/  SK_integ_len; int /*<<< orphan*/  SK_encr_len; int /*<<< orphan*/ * SK_ar; int /*<<< orphan*/ * SK_ai; int /*<<< orphan*/ * SK_er; int /*<<< orphan*/ * SK_ei; } ;
struct ikev2_integ_alg {size_t hash_len; } ;
struct ikev2_encr_alg {size_t block_size; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ ikev2_encr_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 struct ikev2_encr_alg* ikev2_get_encr (int) ; 
 struct ikev2_integ_alg* ikev2_get_integ (int) ; 
 int ikev2_integ_hash (int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ikev2_update_hdr (struct wpabuf*) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 size_t wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_mhead (struct wpabuf*) ; 
 void* wpabuf_put (struct wpabuf*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,size_t) ; 

int ikev2_build_encrypted(int encr_id, int integ_id, struct ikev2_keys *keys,
			  int initiator, struct wpabuf *msg,
			  struct wpabuf *plain, u8 next_payload)
{
	struct ikev2_payload_hdr *phdr;
	size_t plen;
	size_t iv_len, pad_len;
	u8 *icv, *iv;
	const struct ikev2_integ_alg *integ_alg;
	const struct ikev2_encr_alg *encr_alg;
	const u8 *SK_e = initiator ? keys->SK_ei : keys->SK_er;
	const u8 *SK_a = initiator ? keys->SK_ai : keys->SK_ar;

	wpa_printf(MSG_DEBUG, "IKEV2: Adding Encrypted payload");

	/* Encr - RFC 4306, Sect. 3.14 */

	encr_alg = ikev2_get_encr(encr_id);
	if (encr_alg == NULL) {
		wpa_printf(MSG_INFO, "IKEV2: Unsupported encryption type");
		return -1;
	}
	iv_len = encr_alg->block_size;

	integ_alg = ikev2_get_integ(integ_id);
	if (integ_alg == NULL) {
		wpa_printf(MSG_INFO, "IKEV2: Unsupported intergrity type");
		return -1;
	}

	if (SK_e == NULL) {
		wpa_printf(MSG_INFO, "IKEV2: No SK_e available");
		return -1;
	}

	if (SK_a == NULL) {
		wpa_printf(MSG_INFO, "IKEV2: No SK_a available");
		return -1;
	}

	phdr = wpabuf_put(msg, sizeof(*phdr));
	phdr->next_payload = next_payload;
	phdr->flags = 0;

	iv = wpabuf_put(msg, iv_len);
	if (random_get_bytes(iv, iv_len)) {
		wpa_printf(MSG_INFO, "IKEV2: Could not generate IV");
		return -1;
	}

	pad_len = iv_len - (wpabuf_len(plain) + 1) % iv_len;
	if (pad_len == iv_len)
		pad_len = 0;
	wpabuf_put(plain, pad_len);
	wpabuf_put_u8(plain, pad_len);

	if (ikev2_encr_encrypt(encr_alg->id, SK_e, keys->SK_encr_len, iv,
			       wpabuf_head(plain), wpabuf_mhead(plain),
			       wpabuf_len(plain)) < 0)
		return -1;

	wpabuf_put_buf(msg, plain);

	/* Need to update all headers (Length fields) prior to hash func */
	icv = wpabuf_put(msg, integ_alg->hash_len);
	plen = (u8 *) wpabuf_put(msg, 0) - (u8 *) phdr;
	WPA_PUT_BE16(phdr->payload_length, plen);

	ikev2_update_hdr(msg);

	return ikev2_integ_hash(integ_id, SK_a, keys->SK_integ_len,
				wpabuf_head(msg),
				wpabuf_len(msg) - integ_alg->hash_len, icv);

	return 0;
}