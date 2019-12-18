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
struct safe_softc {int dummy; } ;
struct safe_session {int ses_klen; scalar_t__ ses_mlen; int /*<<< orphan*/  ses_iv; } ;
struct cryptoini {scalar_t__ cri_alg; int cri_klen; scalar_t__ cri_mlen; int /*<<< orphan*/ * cri_key; struct cryptoini* cri_next; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  crypto_session_t ;

/* Variables and functions */
#define  CRYPTO_3DES_CBC 130 
#define  CRYPTO_AES_CBC 129 
#define  CRYPTO_DES_CBC 128 
 scalar_t__ CRYPTO_MD5_HMAC ; 
 scalar_t__ CRYPTO_NULL_CBC ; 
 scalar_t__ CRYPTO_NULL_HMAC ; 
 scalar_t__ CRYPTO_SHA1_HMAC ; 
 int EINVAL ; 
 scalar_t__ MD5_HASH_LEN ; 
 scalar_t__ SHA1_HASH_LEN ; 
 struct safe_session* crypto_get_driver_session (int /*<<< orphan*/ ) ; 
 struct safe_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_random (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  safe_setup_enckey (struct safe_session*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  safe_setup_mackey (struct safe_session*,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
safe_newsession(device_t dev, crypto_session_t cses, struct cryptoini *cri)
{
	struct safe_softc *sc = device_get_softc(dev);
	struct cryptoini *c, *encini = NULL, *macini = NULL;
	struct safe_session *ses = NULL;

	if (cri == NULL || sc == NULL)
		return (EINVAL);

	for (c = cri; c != NULL; c = c->cri_next) {
		if (c->cri_alg == CRYPTO_MD5_HMAC ||
		    c->cri_alg == CRYPTO_SHA1_HMAC ||
		    c->cri_alg == CRYPTO_NULL_HMAC) {
			if (macini)
				return (EINVAL);
			macini = c;
		} else if (c->cri_alg == CRYPTO_DES_CBC ||
		    c->cri_alg == CRYPTO_3DES_CBC ||
		    c->cri_alg == CRYPTO_AES_CBC ||
		    c->cri_alg == CRYPTO_NULL_CBC) {
			if (encini)
				return (EINVAL);
			encini = c;
		} else
			return (EINVAL);
	}
	if (encini == NULL && macini == NULL)
		return (EINVAL);
	if (encini) {			/* validate key length */
		switch (encini->cri_alg) {
		case CRYPTO_DES_CBC:
			if (encini->cri_klen != 64)
				return (EINVAL);
			break;
		case CRYPTO_3DES_CBC:
			if (encini->cri_klen != 192)
				return (EINVAL);
			break;
		case CRYPTO_AES_CBC:
			if (encini->cri_klen != 128 &&
			    encini->cri_klen != 192 &&
			    encini->cri_klen != 256)
				return (EINVAL);
			break;
		}
	}

	ses = crypto_get_driver_session(cses);
	if (encini) {
		/* get an IV */
		/* XXX may read fewer than requested */
		read_random(ses->ses_iv, sizeof(ses->ses_iv));

		ses->ses_klen = encini->cri_klen;
		if (encini->cri_key != NULL)
			safe_setup_enckey(ses, encini->cri_key);
	}

	if (macini) {
		ses->ses_mlen = macini->cri_mlen;
		if (ses->ses_mlen == 0) {
			if (macini->cri_alg == CRYPTO_MD5_HMAC)
				ses->ses_mlen = MD5_HASH_LEN;
			else
				ses->ses_mlen = SHA1_HASH_LEN;
		}

		if (macini->cri_key != NULL) {
			safe_setup_mackey(ses, macini->cri_alg, macini->cri_key,
			    macini->cri_klen / 8);
		}
	}

	return (0);
}