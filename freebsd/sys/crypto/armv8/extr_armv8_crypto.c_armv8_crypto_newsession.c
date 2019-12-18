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
struct armv8_crypto_softc {int /*<<< orphan*/  lock; scalar_t__ dieing; } ;
struct armv8_crypto_session {int algo; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  crypto_session_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTDEB (char*) ; 
#define  CRYPTO_AES_CBC 128 
 int EINVAL ; 
 int armv8_crypto_cipher_setup (struct armv8_crypto_session*,struct cryptoini*) ; 
 struct armv8_crypto_session* crypto_get_driver_session (int /*<<< orphan*/ ) ; 
 struct armv8_crypto_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
armv8_crypto_newsession(device_t dev, crypto_session_t cses,
    struct cryptoini *cri)
{
	struct armv8_crypto_softc *sc;
	struct armv8_crypto_session *ses;
	struct cryptoini *encini;
	int error;

	if (cri == NULL) {
		CRYPTDEB("no cri");
		return (EINVAL);
	}

	sc = device_get_softc(dev);
	if (sc->dieing)
		return (EINVAL);

	ses = NULL;
	encini = NULL;
	for (; cri != NULL; cri = cri->cri_next) {
		switch (cri->cri_alg) {
		case CRYPTO_AES_CBC:
			if (encini != NULL) {
				CRYPTDEB("encini already set");
				return (EINVAL);
			}
			encini = cri;
			break;
		default:
			CRYPTDEB("unhandled algorithm");
			return (EINVAL);
		}
	}
	if (encini == NULL) {
		CRYPTDEB("no cipher");
		return (EINVAL);
	}

	rw_wlock(&sc->lock);
	if (sc->dieing) {
		rw_wunlock(&sc->lock);
		return (EINVAL);
	}

	ses = crypto_get_driver_session(cses);
	ses->algo = encini->cri_alg;

	error = armv8_crypto_cipher_setup(ses, encini);
	if (error != 0) {
		CRYPTDEB("setup failed");
		rw_wunlock(&sc->lock);
		return (error);
	}

	rw_wunlock(&sc->lock);
	return (0);
}