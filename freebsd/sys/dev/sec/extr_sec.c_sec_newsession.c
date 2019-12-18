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
struct sec_softc {int sc_version; } ;
struct sec_session {int ss_klen; int ss_mklen; struct sec_eu_methods* ss_eu; int /*<<< orphan*/  ss_mkey; int /*<<< orphan*/  ss_key; } ;
struct sec_eu_methods {int (* sem_newsession ) (struct sec_softc*,struct sec_session*,struct cryptoini*,struct cryptoini*) ;int /*<<< orphan*/ * sem_make_desc; } ;
struct cryptoini {int cri_klen; scalar_t__ cri_key; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  crypto_session_t ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 int SEC_MAX_KEY_LEN ; 
 struct sec_session* crypto_get_driver_session (int /*<<< orphan*/ ) ; 
 struct sec_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct sec_eu_methods* sec_eus ; 
 int sec_split_cri (struct cryptoini*,struct cryptoini**,struct cryptoini**) ; 
 int stub1 (struct sec_softc*,struct sec_session*,struct cryptoini*,struct cryptoini*) ; 

__attribute__((used)) static int
sec_newsession(device_t dev, crypto_session_t cses, struct cryptoini *cri)
{
	struct sec_softc *sc = device_get_softc(dev);
	struct sec_eu_methods *eu = sec_eus;
	struct cryptoini *enc = NULL;
	struct cryptoini *mac = NULL;
	struct sec_session *ses;
	int error = -1;

	error = sec_split_cri(cri, &enc, &mac);
	if (error)
		return (error);

	/* Check key lengths */
	if (enc && enc->cri_key && (enc->cri_klen / 8) > SEC_MAX_KEY_LEN)
		return (E2BIG);

	if (mac && mac->cri_key && (mac->cri_klen / 8) > SEC_MAX_KEY_LEN)
		return (E2BIG);

	/* Only SEC 3.0 supports digests larger than 256 bits */
	if (sc->sc_version < 3 && mac && mac->cri_klen > 256)
		return (E2BIG);

	ses = crypto_get_driver_session(cses);

	/* Find EU for this session */
	while (eu->sem_make_desc != NULL) {
		error = eu->sem_newsession(sc, ses, enc, mac);
		if (error >= 0)
			break;

		eu++;
	}

	/* If not found, return EINVAL */
	if (error < 0)
		return (EINVAL);

	/* Save cipher key */
	if (enc && enc->cri_key) {
		ses->ss_klen = enc->cri_klen / 8;
		memcpy(ses->ss_key, enc->cri_key, ses->ss_klen);
	}

	/* Save digest key */
	if (mac && mac->cri_key) {
		ses->ss_mklen = mac->cri_klen / 8;
		memcpy(ses->ss_mkey, mac->cri_key, ses->ss_mklen);
	}

	ses->ss_eu = eu;
	return (0);
}