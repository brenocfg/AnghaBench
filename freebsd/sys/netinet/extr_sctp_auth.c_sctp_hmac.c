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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  sctp_hash_context_t ;

/* Variables and functions */
 int SCTP_AUTH_DIGEST_LEN_MAX ; 
 int /*<<< orphan*/  memcpy (int*,int*,scalar_t__) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ sctp_get_hmac_block_len (int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_get_hmac_digest_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_hmac_final (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  sctp_hmac_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_hmac_update (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,scalar_t__) ; 

uint32_t
sctp_hmac(uint16_t hmac_algo, uint8_t *key, uint32_t keylen,
    uint8_t *text, uint32_t textlen, uint8_t *digest)
{
	uint32_t digestlen;
	uint32_t blocklen;
	sctp_hash_context_t ctx;
	uint8_t ipad[128], opad[128];	/* keyed hash inner/outer pads */
	uint8_t temp[SCTP_AUTH_DIGEST_LEN_MAX];
	uint32_t i;

	/* sanity check the material and length */
	if ((key == NULL) || (keylen == 0) || (text == NULL) ||
	    (textlen == 0) || (digest == NULL)) {
		/* can't do HMAC with empty key or text or digest store */
		return (0);
	}
	/* validate the hmac algo and get the digest length */
	digestlen = sctp_get_hmac_digest_len(hmac_algo);
	if (digestlen == 0)
		return (0);

	/* hash the key if it is longer than the hash block size */
	blocklen = sctp_get_hmac_block_len(hmac_algo);
	if (keylen > blocklen) {
		sctp_hmac_init(hmac_algo, &ctx);
		sctp_hmac_update(hmac_algo, &ctx, key, keylen);
		sctp_hmac_final(hmac_algo, &ctx, temp);
		/* set the hashed key as the key */
		keylen = digestlen;
		key = temp;
	}
	/* initialize the inner/outer pads with the key and "append" zeroes */
	memset(ipad, 0, blocklen);
	memset(opad, 0, blocklen);
	memcpy(ipad, key, keylen);
	memcpy(opad, key, keylen);

	/* XOR the key with ipad and opad values */
	for (i = 0; i < blocklen; i++) {
		ipad[i] ^= 0x36;
		opad[i] ^= 0x5c;
	}

	/* perform inner hash */
	sctp_hmac_init(hmac_algo, &ctx);
	sctp_hmac_update(hmac_algo, &ctx, ipad, blocklen);
	sctp_hmac_update(hmac_algo, &ctx, text, textlen);
	sctp_hmac_final(hmac_algo, &ctx, temp);

	/* perform outer hash */
	sctp_hmac_init(hmac_algo, &ctx);
	sctp_hmac_update(hmac_algo, &ctx, opad, blocklen);
	sctp_hmac_update(hmac_algo, &ctx, temp, digestlen);
	sctp_hmac_final(hmac_algo, &ctx, digest);

	return (digestlen);
}