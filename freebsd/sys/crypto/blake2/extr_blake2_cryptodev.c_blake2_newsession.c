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
struct cryptoini {int cri_alg; struct cryptoini* cri_next; } ;
struct blake2_softc {int /*<<< orphan*/  lock; scalar_t__ dying; } ;
struct blake2_session {int algo; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  crypto_session_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTDEB (char*) ; 
#define  CRYPTO_BLAKE2B 129 
#define  CRYPTO_BLAKE2S 128 
 int EINVAL ; 
 int blake2_cipher_setup (struct blake2_session*,struct cryptoini*) ; 
 struct blake2_session* crypto_get_driver_session (int /*<<< orphan*/ ) ; 
 struct blake2_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
blake2_newsession(device_t dev, crypto_session_t cses, struct cryptoini *cri)
{
	struct blake2_softc *sc;
	struct blake2_session *ses;
	struct cryptoini *authini;
	int error;

	if (cri == NULL) {
		CRYPTDEB("no cri");
		return (EINVAL);
	}

	sc = device_get_softc(dev);

	authini = NULL;
	for (; cri != NULL; cri = cri->cri_next) {
		switch (cri->cri_alg) {
		case CRYPTO_BLAKE2B:
		case CRYPTO_BLAKE2S:
			if (authini != NULL) {
				CRYPTDEB("authini already set");
				return (EINVAL);
			}
			authini = cri;
			break;
		default:
			CRYPTDEB("unhandled algorithm");
			return (EINVAL);
		}
	}
	if (authini == NULL) {
		CRYPTDEB("no cipher");
		return (EINVAL);
	}

	rw_wlock(&sc->lock);
	if (sc->dying) {
		rw_wunlock(&sc->lock);
		return (EINVAL);
	}
	rw_wunlock(&sc->lock);

	ses = crypto_get_driver_session(cses);

	ses->algo = authini->cri_alg;
	error = blake2_cipher_setup(ses, authini);
	if (error != 0) {
		CRYPTDEB("setup failed");
		return (error);
	}

	return (0);
}