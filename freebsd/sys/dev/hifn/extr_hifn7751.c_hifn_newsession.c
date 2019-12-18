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
struct hifn_softc {int dummy; } ;
struct hifn_session {int hs_mlen; int /*<<< orphan*/  hs_iv; } ;
struct cryptoini {int cri_alg; int cri_mlen; struct cryptoini* cri_next; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  crypto_session_t ;

/* Variables and functions */
#define  CRYPTO_3DES_CBC 135 
#define  CRYPTO_AES_CBC 134 
#define  CRYPTO_ARC4 133 
#define  CRYPTO_DES_CBC 132 
#define  CRYPTO_MD5 131 
#define  CRYPTO_MD5_HMAC 130 
#define  CRYPTO_SHA1 129 
#define  CRYPTO_SHA1_HMAC 128 
 int EINVAL ; 
 int /*<<< orphan*/  HIFN_AES_IV_LENGTH ; 
 int /*<<< orphan*/  HIFN_IV_LENGTH ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct hifn_session* crypto_get_driver_session (int /*<<< orphan*/ ) ; 
 struct hifn_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_random (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hifn_newsession(device_t dev, crypto_session_t cses, struct cryptoini *cri)
{
	struct hifn_softc *sc = device_get_softc(dev);
	struct cryptoini *c;
	int mac = 0, cry = 0;
	struct hifn_session *ses;

	KASSERT(sc != NULL, ("hifn_newsession: null softc"));
	if (cri == NULL || sc == NULL)
		return (EINVAL);

	ses = crypto_get_driver_session(cses);

	for (c = cri; c != NULL; c = c->cri_next) {
		switch (c->cri_alg) {
		case CRYPTO_MD5:
		case CRYPTO_SHA1:
		case CRYPTO_MD5_HMAC:
		case CRYPTO_SHA1_HMAC:
			if (mac)
				return (EINVAL);
			mac = 1;
			ses->hs_mlen = c->cri_mlen;
			if (ses->hs_mlen == 0) {
				switch (c->cri_alg) {
				case CRYPTO_MD5:
				case CRYPTO_MD5_HMAC:
					ses->hs_mlen = 16;
					break;
				case CRYPTO_SHA1:
				case CRYPTO_SHA1_HMAC:
					ses->hs_mlen = 20;
					break;
				}
			}
			break;
		case CRYPTO_DES_CBC:
		case CRYPTO_3DES_CBC:
		case CRYPTO_AES_CBC:
			/* XXX this may read fewer, does it matter? */
			read_random(ses->hs_iv,
				c->cri_alg == CRYPTO_AES_CBC ?
					HIFN_AES_IV_LENGTH : HIFN_IV_LENGTH);
			/*FALLTHROUGH*/
		case CRYPTO_ARC4:
			if (cry)
				return (EINVAL);
			cry = 1;
			break;
		default:
			return (EINVAL);
		}
	}
	if (mac == 0 && cry == 0)
		return (EINVAL);
	return (0);
}