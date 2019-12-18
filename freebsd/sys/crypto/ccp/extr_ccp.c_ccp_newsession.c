#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cryptoini {int cri_alg; scalar_t__ cri_mlen; int /*<<< orphan*/  cri_klen; int /*<<< orphan*/ * cri_key; struct cryptoini* cri_next; } ;
struct ccp_softc {int valid_queues; int /*<<< orphan*/  lock; int /*<<< orphan*/  queues; scalar_t__ detaching; } ;
struct TYPE_6__ {int cipher_mode; unsigned int iv_len; } ;
struct TYPE_5__ {unsigned int auth_mode; unsigned int partial_digest_len; scalar_t__ hash_len; struct auth_hash* auth_hash; } ;
struct TYPE_4__ {scalar_t__ hash_len; } ;
struct ccp_session {unsigned int queue; int active; TYPE_3__ blkcipher; TYPE_2__ hmac; TYPE_1__ gmac; int /*<<< orphan*/  mode; } ;
struct auth_hash {scalar_t__ hashsize; } ;
typedef  enum ccp_aes_mode { ____Placeholder_ccp_aes_mode } ccp_aes_mode ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  crypto_session_t ;

/* Variables and functions */
 unsigned int AES_BLOCK_LEN ; 
 unsigned int AES_GCM_IV_LEN ; 
 scalar_t__ AES_GMAC_HASH_LEN ; 
 int /*<<< orphan*/  AUTHENC ; 
 int /*<<< orphan*/  BLKCIPHER ; 
 int CCP_AES_MODE_CBC ; 
 int CCP_AES_MODE_CTR ; 
 int CCP_AES_MODE_ECB ; 
 int CCP_AES_MODE_GCTR ; 
 int CCP_AES_MODE_XTS ; 
 unsigned int CHCR_SCMD_AUTH_MODE_GHASH ; 
#define  CRYPTO_AES_128_NIST_GMAC 138 
#define  CRYPTO_AES_192_NIST_GMAC 137 
#define  CRYPTO_AES_256_NIST_GMAC 136 
#define  CRYPTO_AES_CBC 135 
#define  CRYPTO_AES_ICM 134 
#define  CRYPTO_AES_NIST_GCM_16 133 
#define  CRYPTO_AES_XTS 132 
#define  CRYPTO_SHA1_HMAC 131 
#define  CRYPTO_SHA2_256_HMAC 130 
#define  CRYPTO_SHA2_384_HMAC 129 
#define  CRYPTO_SHA2_512_HMAC 128 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  GCM ; 
 int /*<<< orphan*/  HMAC ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 unsigned int SHA1 ; 
 unsigned int SHA1_HASH_LEN ; 
 unsigned int SHA2_256 ; 
 unsigned int SHA2_256_HASH_LEN ; 
 unsigned int SHA2_384 ; 
 unsigned int SHA2_512 ; 
 unsigned int SHA2_512_HASH_LEN ; 
 struct auth_hash auth_hash_hmac_sha1 ; 
 struct auth_hash auth_hash_hmac_sha2_256 ; 
 struct auth_hash auth_hash_hmac_sha2_384 ; 
 struct auth_hash auth_hash_hmac_sha2_512 ; 
 int ccp_aes_check_keylen (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccp_aes_setkey (struct ccp_session*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccp_init_hmac_digest (struct ccp_session*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ccp_session* crypto_get_driver_session (int /*<<< orphan*/ ) ; 
 struct ccp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 unsigned int nitems (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ccp_newsession(device_t dev, crypto_session_t cses, struct cryptoini *cri)
{
	struct ccp_softc *sc;
	struct ccp_session *s;
	struct auth_hash *auth_hash;
	struct cryptoini *c, *hash, *cipher;
	enum ccp_aes_mode cipher_mode;
	unsigned auth_mode, iv_len;
	unsigned partial_digest_len;
	unsigned q;
	int error;
	bool gcm_hash;

	if (cri == NULL)
		return (EINVAL);

	s = crypto_get_driver_session(cses);

	gcm_hash = false;
	cipher = NULL;
	hash = NULL;
	auth_hash = NULL;
	/* XXX reconcile auth_mode with use by ccp_sha */
	auth_mode = 0;
	cipher_mode = CCP_AES_MODE_ECB;
	iv_len = 0;
	partial_digest_len = 0;
	for (c = cri; c != NULL; c = c->cri_next) {
		switch (c->cri_alg) {
		case CRYPTO_SHA1_HMAC:
		case CRYPTO_SHA2_256_HMAC:
		case CRYPTO_SHA2_384_HMAC:
		case CRYPTO_SHA2_512_HMAC:
		case CRYPTO_AES_128_NIST_GMAC:
		case CRYPTO_AES_192_NIST_GMAC:
		case CRYPTO_AES_256_NIST_GMAC:
			if (hash)
				return (EINVAL);
			hash = c;
			switch (c->cri_alg) {
			case CRYPTO_SHA1_HMAC:
				auth_hash = &auth_hash_hmac_sha1;
				auth_mode = SHA1;
				partial_digest_len = SHA1_HASH_LEN;
				break;
			case CRYPTO_SHA2_256_HMAC:
				auth_hash = &auth_hash_hmac_sha2_256;
				auth_mode = SHA2_256;
				partial_digest_len = SHA2_256_HASH_LEN;
				break;
			case CRYPTO_SHA2_384_HMAC:
				auth_hash = &auth_hash_hmac_sha2_384;
				auth_mode = SHA2_384;
				partial_digest_len = SHA2_512_HASH_LEN;
				break;
			case CRYPTO_SHA2_512_HMAC:
				auth_hash = &auth_hash_hmac_sha2_512;
				auth_mode = SHA2_512;
				partial_digest_len = SHA2_512_HASH_LEN;
				break;
			case CRYPTO_AES_128_NIST_GMAC:
			case CRYPTO_AES_192_NIST_GMAC:
			case CRYPTO_AES_256_NIST_GMAC:
				gcm_hash = true;
#if 0
				auth_mode = CHCR_SCMD_AUTH_MODE_GHASH;
#endif
				break;
			}
			break;
		case CRYPTO_AES_CBC:
		case CRYPTO_AES_ICM:
		case CRYPTO_AES_NIST_GCM_16:
		case CRYPTO_AES_XTS:
			if (cipher)
				return (EINVAL);
			cipher = c;
			switch (c->cri_alg) {
			case CRYPTO_AES_CBC:
				cipher_mode = CCP_AES_MODE_CBC;
				iv_len = AES_BLOCK_LEN;
				break;
			case CRYPTO_AES_ICM:
				cipher_mode = CCP_AES_MODE_CTR;
				iv_len = AES_BLOCK_LEN;
				break;
			case CRYPTO_AES_NIST_GCM_16:
				cipher_mode = CCP_AES_MODE_GCTR;
				iv_len = AES_GCM_IV_LEN;
				break;
			case CRYPTO_AES_XTS:
				cipher_mode = CCP_AES_MODE_XTS;
				iv_len = AES_BLOCK_LEN;
				break;
			}
			if (c->cri_key != NULL) {
				error = ccp_aes_check_keylen(c->cri_alg,
				    c->cri_klen);
				if (error != 0)
					return (error);
			}
			break;
		default:
			return (EINVAL);
		}
	}
	if (gcm_hash != (cipher_mode == CCP_AES_MODE_GCTR))
		return (EINVAL);
	if (hash == NULL && cipher == NULL)
		return (EINVAL);
	if (hash != NULL && hash->cri_key == NULL)
		return (EINVAL);

	sc = device_get_softc(dev);
	mtx_lock(&sc->lock);
	if (sc->detaching) {
		mtx_unlock(&sc->lock);
		return (ENXIO);
	}

	/* Just grab the first usable queue for now. */
	for (q = 0; q < nitems(sc->queues); q++)
		if ((sc->valid_queues & (1 << q)) != 0)
			break;
	if (q == nitems(sc->queues)) {
		mtx_unlock(&sc->lock);
		return (ENXIO);
	}
	s->queue = q;

	if (gcm_hash)
		s->mode = GCM;
	else if (hash != NULL && cipher != NULL)
		s->mode = AUTHENC;
	else if (hash != NULL)
		s->mode = HMAC;
	else {
		MPASS(cipher != NULL);
		s->mode = BLKCIPHER;
	}
	if (gcm_hash) {
		if (hash->cri_mlen == 0)
			s->gmac.hash_len = AES_GMAC_HASH_LEN;
		else
			s->gmac.hash_len = hash->cri_mlen;
	} else if (hash != NULL) {
		s->hmac.auth_hash = auth_hash;
		s->hmac.auth_mode = auth_mode;
		s->hmac.partial_digest_len = partial_digest_len;
		if (hash->cri_mlen == 0)
			s->hmac.hash_len = auth_hash->hashsize;
		else
			s->hmac.hash_len = hash->cri_mlen;
		ccp_init_hmac_digest(s, hash->cri_alg, hash->cri_key,
		    hash->cri_klen);
	}
	if (cipher != NULL) {
		s->blkcipher.cipher_mode = cipher_mode;
		s->blkcipher.iv_len = iv_len;
		if (cipher->cri_key != NULL)
			ccp_aes_setkey(s, cipher->cri_alg, cipher->cri_key,
			    cipher->cri_klen);
	}

	s->active = true;
	mtx_unlock(&sc->lock);

	return (0);
}