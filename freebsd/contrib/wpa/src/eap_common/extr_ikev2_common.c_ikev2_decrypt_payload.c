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
typedef  size_t u8 ;
struct ikev2_keys {size_t* SK_ei; size_t* SK_er; size_t* SK_ai; size_t* SK_ar; int /*<<< orphan*/  SK_encr_len; int /*<<< orphan*/  SK_integ_len; } ;
struct ikev2_integ_alg {size_t hash_len; } ;
struct ikev2_hdr {int dummy; } ;
struct ikev2_encr_alg {size_t block_size; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int IKEV2_MAX_HASH_LEN ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ ikev2_encr_decrypt (int /*<<< orphan*/ ,size_t const*,int /*<<< orphan*/ ,size_t const*,size_t const*,size_t*,size_t) ; 
 struct ikev2_encr_alg* ikev2_get_encr (int) ; 
 struct ikev2_integ_alg* ikev2_get_integ (int) ; 
 scalar_t__ ikev2_integ_hash (int,size_t const*,int /*<<< orphan*/ ,size_t const*,int,size_t*) ; 
 int /*<<< orphan*/  os_free (size_t*) ; 
 size_t* os_malloc (size_t) ; 
 scalar_t__ os_memcmp_const (size_t const*,size_t*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

u8 * ikev2_decrypt_payload(int encr_id, int integ_id,
			   struct ikev2_keys *keys, int initiator,
			   const struct ikev2_hdr *hdr,
			   const u8 *encrypted, size_t encrypted_len,
			   size_t *res_len)
{
	size_t iv_len;
	const u8 *pos, *end, *iv, *integ;
	u8 hash[IKEV2_MAX_HASH_LEN], *decrypted;
	size_t decrypted_len, pad_len;
	const struct ikev2_integ_alg *integ_alg;
	const struct ikev2_encr_alg *encr_alg;
	const u8 *SK_e = initiator ? keys->SK_ei : keys->SK_er;
	const u8 *SK_a = initiator ? keys->SK_ai : keys->SK_ar;

	if (encrypted == NULL) {
		wpa_printf(MSG_INFO, "IKEV2: No Encrypted payload in SA_AUTH");
		return NULL;
	}

	encr_alg = ikev2_get_encr(encr_id);
	if (encr_alg == NULL) {
		wpa_printf(MSG_INFO, "IKEV2: Unsupported encryption type");
		return NULL;
	}
	iv_len = encr_alg->block_size;

	integ_alg = ikev2_get_integ(integ_id);
	if (integ_alg == NULL) {
		wpa_printf(MSG_INFO, "IKEV2: Unsupported intergrity type");
		return NULL;
	}

	if (encrypted_len < iv_len + 1 + integ_alg->hash_len) {
		wpa_printf(MSG_INFO, "IKEV2: No room for IV or Integrity "
			  "Checksum");
		return NULL;
	}

	iv = encrypted;
	pos = iv + iv_len;
	end = encrypted + encrypted_len;
	integ = end - integ_alg->hash_len;

	if (SK_a == NULL) {
		wpa_printf(MSG_INFO, "IKEV2: No SK_a available");
		return NULL;
	}
	if (ikev2_integ_hash(integ_id, SK_a, keys->SK_integ_len,
			     (const u8 *) hdr,
			     integ - (const u8 *) hdr, hash) < 0) {
		wpa_printf(MSG_INFO, "IKEV2: Failed to calculate integrity "
			   "hash");
		return NULL;
	}
	if (os_memcmp_const(integ, hash, integ_alg->hash_len) != 0) {
		wpa_printf(MSG_INFO, "IKEV2: Incorrect Integrity Checksum "
			   "Data");
		return NULL;
	}

	if (SK_e == NULL) {
		wpa_printf(MSG_INFO, "IKEV2: No SK_e available");
		return NULL;
	}

	decrypted_len = integ - pos;
	decrypted = os_malloc(decrypted_len);
	if (decrypted == NULL)
		return NULL;

	if (ikev2_encr_decrypt(encr_alg->id, SK_e, keys->SK_encr_len, iv, pos,
			       decrypted, decrypted_len) < 0) {
		os_free(decrypted);
		return NULL;
	}

	pad_len = decrypted[decrypted_len - 1];
	if (decrypted_len < pad_len + 1) {
		wpa_printf(MSG_INFO, "IKEV2: Invalid padding in encrypted "
			   "payload");
		os_free(decrypted);
		return NULL;
	}

	decrypted_len -= pad_len + 1;

	*res_len = decrypted_len;
	return decrypted;
}