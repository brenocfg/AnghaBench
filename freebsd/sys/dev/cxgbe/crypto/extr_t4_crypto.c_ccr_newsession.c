#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct cryptoini {int cri_alg; scalar_t__ cri_mlen; int /*<<< orphan*/  cri_klen; int /*<<< orphan*/ * cri_key; struct cryptoini* cri_next; } ;
struct ccr_softc {int /*<<< orphan*/  lock; scalar_t__ detaching; TYPE_4__* txq; TYPE_3__* rxq; } ;
struct TYPE_8__ {unsigned int cipher_mode; unsigned int iv_len; } ;
struct TYPE_14__ {unsigned int auth_mode; unsigned int mk_size; unsigned int partial_digest_len; scalar_t__ hash_len; int /*<<< orphan*/  pads; struct auth_hash* auth_hash; } ;
struct TYPE_13__ {scalar_t__ hash_len; } ;
struct TYPE_12__ {scalar_t__ hash_len; int /*<<< orphan*/  ghash_h; } ;
struct ccr_session {int active; TYPE_1__ blkcipher; TYPE_7__ hmac; TYPE_6__ ccm_mac; TYPE_5__ gmac; int /*<<< orphan*/  mode; } ;
struct auth_hash {scalar_t__ hashsize; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  crypto_session_t ;
struct TYPE_11__ {int /*<<< orphan*/ * adapter; } ;
struct TYPE_9__ {int /*<<< orphan*/ * adapter; } ;
struct TYPE_10__ {TYPE_2__ iq; } ;

/* Variables and functions */
 unsigned int AES_BLOCK_LEN ; 
 scalar_t__ AES_CBC_MAC_HASH_LEN ; 
 unsigned int AES_CCM_IV_LEN ; 
 unsigned int AES_GCM_IV_LEN ; 
 scalar_t__ AES_GMAC_HASH_LEN ; 
 int /*<<< orphan*/  AUTHENC ; 
 int /*<<< orphan*/  BLKCIPHER ; 
 int /*<<< orphan*/  CCM ; 
 unsigned int CHCR_KEYCTX_MAC_KEY_SIZE_128 ; 
 unsigned int CHCR_KEYCTX_MAC_KEY_SIZE_160 ; 
 unsigned int CHCR_KEYCTX_MAC_KEY_SIZE_256 ; 
 unsigned int CHCR_KEYCTX_MAC_KEY_SIZE_512 ; 
#define  CRYPTO_AES_128_NIST_GMAC 146 
#define  CRYPTO_AES_192_NIST_GMAC 145 
#define  CRYPTO_AES_256_NIST_GMAC 144 
#define  CRYPTO_AES_CBC 143 
#define  CRYPTO_AES_CCM_16 142 
#define  CRYPTO_AES_CCM_CBC_MAC 141 
#define  CRYPTO_AES_ICM 140 
#define  CRYPTO_AES_NIST_GCM_16 139 
#define  CRYPTO_AES_XTS 138 
#define  CRYPTO_SHA1 137 
#define  CRYPTO_SHA1_HMAC 136 
#define  CRYPTO_SHA2_224 135 
#define  CRYPTO_SHA2_224_HMAC 134 
#define  CRYPTO_SHA2_256 133 
#define  CRYPTO_SHA2_256_HMAC 132 
#define  CRYPTO_SHA2_384 131 
#define  CRYPTO_SHA2_384_HMAC 130 
#define  CRYPTO_SHA2_512 129 
#define  CRYPTO_SHA2_512_HMAC 128 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  GCM ; 
 int /*<<< orphan*/  HASH ; 
 int /*<<< orphan*/  HMAC ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 unsigned int SCMD_AUTH_MODE_CBCMAC ; 
 unsigned int SCMD_AUTH_MODE_GHASH ; 
 unsigned int SCMD_AUTH_MODE_NOP ; 
 unsigned int SCMD_AUTH_MODE_SHA1 ; 
 unsigned int SCMD_AUTH_MODE_SHA224 ; 
 unsigned int SCMD_AUTH_MODE_SHA256 ; 
 unsigned int SCMD_AUTH_MODE_SHA512_384 ; 
 unsigned int SCMD_AUTH_MODE_SHA512_512 ; 
 unsigned int SCMD_CIPH_MODE_AES_CBC ; 
 unsigned int SCMD_CIPH_MODE_AES_CCM ; 
 unsigned int SCMD_CIPH_MODE_AES_CTR ; 
 unsigned int SCMD_CIPH_MODE_AES_GCM ; 
 unsigned int SCMD_CIPH_MODE_AES_XTS ; 
 unsigned int SCMD_CIPH_MODE_NOP ; 
 unsigned int SHA1_HASH_LEN ; 
 unsigned int SHA2_256_HASH_LEN ; 
 unsigned int SHA2_512_HASH_LEN ; 
 struct auth_hash auth_hash_hmac_sha1 ; 
 struct auth_hash auth_hash_hmac_sha2_224 ; 
 struct auth_hash auth_hash_hmac_sha2_256 ; 
 struct auth_hash auth_hash_hmac_sha2_384 ; 
 struct auth_hash auth_hash_hmac_sha2_512 ; 
 int ccr_aes_check_keylen (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccr_aes_setkey (struct ccr_session*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccr_init_hash_digest (struct ccr_session*,int) ; 
 struct ccr_session* crypto_get_driver_session (int /*<<< orphan*/ ) ; 
 struct ccr_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_init_gmac_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_init_hmac_digest (struct auth_hash*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ccr_newsession(device_t dev, crypto_session_t cses, struct cryptoini *cri)
{
	struct ccr_softc *sc;
	struct ccr_session *s;
	struct auth_hash *auth_hash;
	struct cryptoini *c, *hash, *cipher;
	unsigned int auth_mode, cipher_mode, iv_len, mk_size;
	unsigned int partial_digest_len;
	int error;
	bool gcm_hash, hmac;

	if (cri == NULL)
		return (EINVAL);

	gcm_hash = false;
	hmac = false;
	cipher = NULL;
	hash = NULL;
	auth_hash = NULL;
	auth_mode = SCMD_AUTH_MODE_NOP;
	cipher_mode = SCMD_CIPH_MODE_NOP;
	iv_len = 0;
	mk_size = 0;
	partial_digest_len = 0;
	for (c = cri; c != NULL; c = c->cri_next) {
		switch (c->cri_alg) {
		case CRYPTO_SHA1:
		case CRYPTO_SHA2_224:
		case CRYPTO_SHA2_256:
		case CRYPTO_SHA2_384:
		case CRYPTO_SHA2_512:
		case CRYPTO_SHA1_HMAC:
		case CRYPTO_SHA2_224_HMAC:
		case CRYPTO_SHA2_256_HMAC:
		case CRYPTO_SHA2_384_HMAC:
		case CRYPTO_SHA2_512_HMAC:
		case CRYPTO_AES_128_NIST_GMAC:
		case CRYPTO_AES_192_NIST_GMAC:
		case CRYPTO_AES_256_NIST_GMAC:
		case CRYPTO_AES_CCM_CBC_MAC:
			if (hash)
				return (EINVAL);
			hash = c;
			switch (c->cri_alg) {
			case CRYPTO_SHA1:
			case CRYPTO_SHA1_HMAC:
				auth_hash = &auth_hash_hmac_sha1;
				auth_mode = SCMD_AUTH_MODE_SHA1;
				mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_160;
				partial_digest_len = SHA1_HASH_LEN;
				break;
			case CRYPTO_SHA2_224:
			case CRYPTO_SHA2_224_HMAC:
				auth_hash = &auth_hash_hmac_sha2_224;
				auth_mode = SCMD_AUTH_MODE_SHA224;
				mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_256;
				partial_digest_len = SHA2_256_HASH_LEN;
				break;
			case CRYPTO_SHA2_256:
			case CRYPTO_SHA2_256_HMAC:
				auth_hash = &auth_hash_hmac_sha2_256;
				auth_mode = SCMD_AUTH_MODE_SHA256;
				mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_256;
				partial_digest_len = SHA2_256_HASH_LEN;
				break;
			case CRYPTO_SHA2_384:
			case CRYPTO_SHA2_384_HMAC:
				auth_hash = &auth_hash_hmac_sha2_384;
				auth_mode = SCMD_AUTH_MODE_SHA512_384;
				mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_512;
				partial_digest_len = SHA2_512_HASH_LEN;
				break;
			case CRYPTO_SHA2_512:
			case CRYPTO_SHA2_512_HMAC:
				auth_hash = &auth_hash_hmac_sha2_512;
				auth_mode = SCMD_AUTH_MODE_SHA512_512;
				mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_512;
				partial_digest_len = SHA2_512_HASH_LEN;
				break;
			case CRYPTO_AES_128_NIST_GMAC:
			case CRYPTO_AES_192_NIST_GMAC:
			case CRYPTO_AES_256_NIST_GMAC:
				gcm_hash = true;
				auth_mode = SCMD_AUTH_MODE_GHASH;
				mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_128;
				break;
			case CRYPTO_AES_CCM_CBC_MAC:
				auth_mode = SCMD_AUTH_MODE_CBCMAC;
				break;
			}
			switch (c->cri_alg) {
			case CRYPTO_SHA1_HMAC:
			case CRYPTO_SHA2_224_HMAC:
			case CRYPTO_SHA2_256_HMAC:
			case CRYPTO_SHA2_384_HMAC:
			case CRYPTO_SHA2_512_HMAC:
				hmac = true;
				break;
			}
			break;
		case CRYPTO_AES_CBC:
		case CRYPTO_AES_ICM:
		case CRYPTO_AES_NIST_GCM_16:
		case CRYPTO_AES_XTS:
		case CRYPTO_AES_CCM_16:
			if (cipher)
				return (EINVAL);
			cipher = c;
			switch (c->cri_alg) {
			case CRYPTO_AES_CBC:
				cipher_mode = SCMD_CIPH_MODE_AES_CBC;
				iv_len = AES_BLOCK_LEN;
				break;
			case CRYPTO_AES_ICM:
				cipher_mode = SCMD_CIPH_MODE_AES_CTR;
				iv_len = AES_BLOCK_LEN;
				break;
			case CRYPTO_AES_NIST_GCM_16:
				cipher_mode = SCMD_CIPH_MODE_AES_GCM;
				iv_len = AES_GCM_IV_LEN;
				break;
			case CRYPTO_AES_XTS:
				cipher_mode = SCMD_CIPH_MODE_AES_XTS;
				iv_len = AES_BLOCK_LEN;
				break;
			case CRYPTO_AES_CCM_16:
				cipher_mode = SCMD_CIPH_MODE_AES_CCM;
				iv_len = AES_CCM_IV_LEN;
				break;
			}
			if (c->cri_key != NULL) {
				error = ccr_aes_check_keylen(c->cri_alg,
				    c->cri_klen);
				if (error)
					return (error);
			}
			break;
		default:
			return (EINVAL);
		}
	}
	if (gcm_hash != (cipher_mode == SCMD_CIPH_MODE_AES_GCM))
		return (EINVAL);
	if ((auth_mode == SCMD_AUTH_MODE_CBCMAC) !=
	    (cipher_mode == SCMD_CIPH_MODE_AES_CCM))
		return (EINVAL);
	if (hash == NULL && cipher == NULL)
		return (EINVAL);
	if (hash != NULL) {
		if (hmac || gcm_hash || auth_mode == SCMD_AUTH_MODE_CBCMAC) {
			if (hash->cri_key == NULL)
				return (EINVAL);
		} else {
			if (hash->cri_key != NULL)
				return (EINVAL);
		}
	}

	sc = device_get_softc(dev);

	/*
	 * XXX: Don't create a session if the queues aren't
	 * initialized.  This is racy as the rxq can be destroyed by
	 * the associated VI detaching.  Eventually ccr should use
	 * dedicated queues.
	 */
	if (sc->rxq->iq.adapter == NULL || sc->txq->adapter == NULL)
		return (ENXIO);
	
	mtx_lock(&sc->lock);
	if (sc->detaching) {
		mtx_unlock(&sc->lock);
		return (ENXIO);
	}

	s = crypto_get_driver_session(cses);

	if (gcm_hash)
		s->mode = GCM;
	else if (cipher_mode == SCMD_CIPH_MODE_AES_CCM)
		s->mode = CCM;
	else if (hash != NULL && cipher != NULL)
		s->mode = AUTHENC;
	else if (hash != NULL) {
		if (hmac)
			s->mode = HMAC;
		else
			s->mode = HASH;
	} else {
		MPASS(cipher != NULL);
		s->mode = BLKCIPHER;
	}
	if (gcm_hash) {
		if (hash->cri_mlen == 0)
			s->gmac.hash_len = AES_GMAC_HASH_LEN;
		else
			s->gmac.hash_len = hash->cri_mlen;
		t4_init_gmac_hash(hash->cri_key, hash->cri_klen,
		    s->gmac.ghash_h);
	} else if (auth_mode == SCMD_AUTH_MODE_CBCMAC) {
		if (hash->cri_mlen == 0)
			s->ccm_mac.hash_len = AES_CBC_MAC_HASH_LEN;
		else
			s->ccm_mac.hash_len = hash->cri_mlen;
	} else if (hash != NULL) {
		s->hmac.auth_hash = auth_hash;
		s->hmac.auth_mode = auth_mode;
		s->hmac.mk_size = mk_size;
		s->hmac.partial_digest_len = partial_digest_len;
		if (hash->cri_mlen == 0)
			s->hmac.hash_len = auth_hash->hashsize;
		else
			s->hmac.hash_len = hash->cri_mlen;
		if (hmac)
			t4_init_hmac_digest(auth_hash, partial_digest_len,
			    hash->cri_key, hash->cri_klen, s->hmac.pads);
		else
			ccr_init_hash_digest(s, hash->cri_alg);
	}
	if (cipher != NULL) {
		s->blkcipher.cipher_mode = cipher_mode;
		s->blkcipher.iv_len = iv_len;
		if (cipher->cri_key != NULL)
			ccr_aes_setkey(s, cipher->cri_alg, cipher->cri_key,
			    cipher->cri_klen);
	}

	s->active = true;
	mtx_unlock(&sc->lock);
	return (0);
}