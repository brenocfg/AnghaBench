#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct padlock_session {int /*<<< orphan*/ * ses_octx; int /*<<< orphan*/ * ses_ictx; TYPE_1__* ses_axf; int /*<<< orphan*/  ses_mlen; } ;
struct cryptoini {int cri_alg; int /*<<< orphan*/  cri_klen; int /*<<< orphan*/ * cri_key; int /*<<< orphan*/  cri_mlen; } ;
struct TYPE_10__ {int /*<<< orphan*/  ctxsize; } ;

/* Variables and functions */
#define  CRYPTO_MD5_HMAC 134 
#define  CRYPTO_NULL_HMAC 133 
#define  CRYPTO_RIPEMD160_HMAC 132 
#define  CRYPTO_SHA1_HMAC 131 
#define  CRYPTO_SHA2_256_HMAC 130 
#define  CRYPTO_SHA2_384_HMAC 129 
#define  CRYPTO_SHA2_512_HMAC 128 
 int ENOMEM ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_PADLOCK ; 
 int M_ZERO ; 
 int VIA_HAS_SHA ; 
 TYPE_1__ auth_hash_hmac_md5 ; 
 TYPE_1__ auth_hash_hmac_ripemd_160 ; 
 TYPE_1__ auth_hash_hmac_sha1 ; 
 TYPE_1__ auth_hash_hmac_sha2_256 ; 
 TYPE_1__ auth_hash_hmac_sha2_384 ; 
 TYPE_1__ auth_hash_hmac_sha2_512 ; 
 TYPE_1__ auth_hash_null ; 
 void* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  padlock_hash_key_setup (struct padlock_session*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ padlock_hmac_sha1 ; 
 TYPE_1__ padlock_hmac_sha256 ; 
 int via_feature_xcrypt ; 

int
padlock_hash_setup(struct padlock_session *ses, struct cryptoini *macini)
{

	ses->ses_mlen = macini->cri_mlen;

	/* Find software structure which describes HMAC algorithm. */
	switch (macini->cri_alg) {
	case CRYPTO_NULL_HMAC:
		ses->ses_axf = &auth_hash_null;
		break;
	case CRYPTO_MD5_HMAC:
		ses->ses_axf = &auth_hash_hmac_md5;
		break;
	case CRYPTO_SHA1_HMAC:
		if ((via_feature_xcrypt & VIA_HAS_SHA) != 0)
			ses->ses_axf = &padlock_hmac_sha1;
		else
			ses->ses_axf = &auth_hash_hmac_sha1;
		break;
	case CRYPTO_RIPEMD160_HMAC:
		ses->ses_axf = &auth_hash_hmac_ripemd_160;
		break;
	case CRYPTO_SHA2_256_HMAC:
		if ((via_feature_xcrypt & VIA_HAS_SHA) != 0)
			ses->ses_axf = &padlock_hmac_sha256;
		else
			ses->ses_axf = &auth_hash_hmac_sha2_256;
		break;
	case CRYPTO_SHA2_384_HMAC:
		ses->ses_axf = &auth_hash_hmac_sha2_384;
		break;
	case CRYPTO_SHA2_512_HMAC:
		ses->ses_axf = &auth_hash_hmac_sha2_512;
		break;
	}

	/* Allocate memory for HMAC inner and outer contexts. */
	ses->ses_ictx = malloc(ses->ses_axf->ctxsize, M_PADLOCK,
	    M_ZERO | M_NOWAIT);
	ses->ses_octx = malloc(ses->ses_axf->ctxsize, M_PADLOCK,
	    M_ZERO | M_NOWAIT);
	if (ses->ses_ictx == NULL || ses->ses_octx == NULL)
		return (ENOMEM);

	/* Setup key if given. */
	if (macini->cri_key != NULL) {
		padlock_hash_key_setup(ses, macini->cri_key,
		    macini->cri_klen);
	}
	return (0);
}