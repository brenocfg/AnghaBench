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
struct glxsb_softc {int /*<<< orphan*/  sc_dev; } ;
struct glxsb_session {int ses_klen; int /*<<< orphan*/  ses_key; int /*<<< orphan*/  ses_iv; } ;
struct cryptoini {int cri_alg; int cri_klen; int /*<<< orphan*/  cri_key; struct cryptoini* cri_next; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  crypto_session_t ;

/* Variables and functions */
#define  CRYPTO_AES_CBC 135 
#define  CRYPTO_MD5_HMAC 134 
#define  CRYPTO_NULL_HMAC 133 
#define  CRYPTO_RIPEMD160_HMAC 132 
#define  CRYPTO_SHA1_HMAC 131 
#define  CRYPTO_SHA2_256_HMAC 130 
#define  CRYPTO_SHA2_384_HMAC 129 
#define  CRYPTO_SHA2_512_HMAC 128 
 int EINVAL ; 
 int /*<<< orphan*/  arc4rand (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct glxsb_session* crypto_get_driver_session (int /*<<< orphan*/ ) ; 
 struct glxsb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glxsb_crypto_freesession (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int glxsb_hash_setup (struct glxsb_session*,struct cryptoini*) ; 

__attribute__((used)) static int
glxsb_crypto_newsession(device_t dev, crypto_session_t cses,
    struct cryptoini *cri)
{
	struct glxsb_softc *sc = device_get_softc(dev);
	struct glxsb_session *ses;
	struct cryptoini *encini, *macini;
	int error;

	if (sc == NULL || cri == NULL)
		return (EINVAL);

	encini = macini = NULL;
	for (; cri != NULL; cri = cri->cri_next) {
		switch(cri->cri_alg) {
		case CRYPTO_NULL_HMAC:
		case CRYPTO_MD5_HMAC:
		case CRYPTO_SHA1_HMAC:
		case CRYPTO_RIPEMD160_HMAC:
		case CRYPTO_SHA2_256_HMAC:
		case CRYPTO_SHA2_384_HMAC:
		case CRYPTO_SHA2_512_HMAC:
			if (macini != NULL)
				return (EINVAL);
			macini = cri;
			break;
		case CRYPTO_AES_CBC:
			if (encini != NULL)
				return (EINVAL);
			encini = cri;
			break;
		default:
			return (EINVAL);
		}
	}

	/*
	 * We only support HMAC algorithms to be able to work with
	 * ipsec(4), so if we are asked only for authentication without
	 * encryption, don't pretend we can accellerate it.
	 */
	if (encini == NULL)
		return (EINVAL);

	ses = crypto_get_driver_session(cses);
	if (encini->cri_alg == CRYPTO_AES_CBC) {
		if (encini->cri_klen != 128) {
			glxsb_crypto_freesession(sc->sc_dev, cses);
			return (EINVAL);
		}
		arc4rand(ses->ses_iv, sizeof(ses->ses_iv), 0);
		ses->ses_klen = encini->cri_klen;

		/* Copy the key (Geode LX wants the primary key only) */
		bcopy(encini->cri_key, ses->ses_key, sizeof(ses->ses_key));
	}

	if (macini != NULL) {
		error = glxsb_hash_setup(ses, macini);
		if (error != 0) {
			glxsb_crypto_freesession(sc->sc_dev, cses);
			return (error);
		}
	}

	return (0);
}