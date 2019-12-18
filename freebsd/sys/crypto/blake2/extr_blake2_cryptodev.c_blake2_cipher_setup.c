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
struct cryptoini {scalar_t__ cri_mlen; int cri_klen; int /*<<< orphan*/  cri_key; } ;
struct blake2_session {int algo; int klen; scalar_t__ mlen; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 scalar_t__ BLAKE2B_OUTBYTES ; 
 int BLAKE2S_KEYBYTES ; 
 scalar_t__ BLAKE2S_OUTBYTES ; 
#define  CRYPTO_BLAKE2B 129 
#define  CRYPTO_BLAKE2S 128 
 int /*<<< orphan*/  CTASSERT (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
blake2_cipher_setup(struct blake2_session *ses, struct cryptoini *authini)
{
	int keylen;

	CTASSERT((size_t)BLAKE2S_OUTBYTES <= (size_t)BLAKE2B_OUTBYTES);

	if (authini->cri_mlen < 0)
		return (EINVAL);

	switch (ses->algo) {
	case CRYPTO_BLAKE2S:
		if (authini->cri_mlen != 0 &&
		    authini->cri_mlen > BLAKE2S_OUTBYTES)
			return (EINVAL);
		/* FALLTHROUGH */
	case CRYPTO_BLAKE2B:
		if (authini->cri_mlen != 0 &&
		    authini->cri_mlen > BLAKE2B_OUTBYTES)
			return (EINVAL);

		if (authini->cri_klen % 8 != 0)
			return (EINVAL);
		keylen = authini->cri_klen / 8;
		if (keylen > sizeof(ses->key) ||
		    (ses->algo == CRYPTO_BLAKE2S && keylen > BLAKE2S_KEYBYTES))
			return (EINVAL);
		ses->klen = keylen;
		memcpy(ses->key, authini->cri_key, keylen);
		ses->mlen = authini->cri_mlen;
	}
	return (0);
}