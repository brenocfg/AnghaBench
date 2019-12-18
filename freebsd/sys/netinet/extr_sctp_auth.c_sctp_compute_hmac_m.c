#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct mbuf {int dummy; } ;
struct TYPE_3__ {scalar_t__ keylen; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ sctp_key_t ;
typedef  int /*<<< orphan*/  sctp_hash_context_t ;

/* Variables and functions */
 int SCTP_AUTH_DIGEST_LEN_MAX ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ sctp_get_hmac_block_len (int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_get_hmac_digest_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_hmac_final (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_hmac_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sctp_hmac_m (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct mbuf*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_hmac_update (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

uint32_t
sctp_compute_hmac_m(uint16_t hmac_algo, sctp_key_t *key, struct mbuf *m,
    uint32_t m_offset, uint8_t *digest)
{
	uint32_t digestlen;
	uint32_t blocklen;
	sctp_hash_context_t ctx;
	uint8_t temp[SCTP_AUTH_DIGEST_LEN_MAX];

	/* sanity check */
	if ((key == NULL) || (m == NULL) || (digest == NULL)) {
		/* can't do HMAC with empty key or text or digest store */
		return (0);
	}
	/* validate the hmac algo and get the digest length */
	digestlen = sctp_get_hmac_digest_len(hmac_algo);
	if (digestlen == 0)
		return (0);

	/* hash the key if it is longer than the hash block size */
	blocklen = sctp_get_hmac_block_len(hmac_algo);
	if (key->keylen > blocklen) {
		sctp_hmac_init(hmac_algo, &ctx);
		sctp_hmac_update(hmac_algo, &ctx, key->key, key->keylen);
		sctp_hmac_final(hmac_algo, &ctx, temp);
		/* save the hashed key as the new key */
		key->keylen = digestlen;
		memcpy(key->key, temp, key->keylen);
	}
	return (sctp_hmac_m(hmac_algo, key->key, key->keylen, m, m_offset, digest, 0));
}