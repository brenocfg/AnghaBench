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
struct swcr_session {int /*<<< orphan*/  swcr_lock; struct swcr_data* swcr_algorithms; } ;
struct swcr_data {scalar_t__ sw_alg; scalar_t__ sw_size; } ;
struct cryptop {int crp_etype; int crp_olen; int /*<<< orphan*/  crp_flags; int /*<<< orphan*/ * crp_buf; struct cryptodesc* crp_desc; int /*<<< orphan*/  crp_session; } ;
struct cryptodesc {scalar_t__ crd_alg; struct cryptodesc* crd_next; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  CRYPTO_3DES_CBC 165 
#define  CRYPTO_AES_128_NIST_GMAC 164 
#define  CRYPTO_AES_192_NIST_GMAC 163 
#define  CRYPTO_AES_256_NIST_GMAC 162 
#define  CRYPTO_AES_CCM_16 161 
#define  CRYPTO_AES_CCM_CBC_MAC 160 
#define  CRYPTO_AES_ICM 159 
#define  CRYPTO_AES_NIST_GCM_16 158 
#define  CRYPTO_AES_NIST_GMAC 157 
#define  CRYPTO_AES_XTS 156 
#define  CRYPTO_BLAKE2B 155 
#define  CRYPTO_BLAKE2S 154 
#define  CRYPTO_BLF_CBC 153 
#define  CRYPTO_CAMELLIA_CBC 152 
#define  CRYPTO_CAST_CBC 151 
#define  CRYPTO_CHACHA20 150 
#define  CRYPTO_DEFLATE_COMP 149 
#define  CRYPTO_DES_CBC 148 
#define  CRYPTO_MD5 147 
#define  CRYPTO_MD5_HMAC 146 
#define  CRYPTO_MD5_KPDK 145 
#define  CRYPTO_NULL_CBC 144 
#define  CRYPTO_NULL_HMAC 143 
#define  CRYPTO_POLY1305 142 
#define  CRYPTO_RIJNDAEL128_CBC 141 
#define  CRYPTO_RIPEMD160_HMAC 140 
#define  CRYPTO_SHA1 139 
#define  CRYPTO_SHA1_HMAC 138 
#define  CRYPTO_SHA1_KPDK 137 
#define  CRYPTO_SHA2_224 136 
#define  CRYPTO_SHA2_224_HMAC 135 
#define  CRYPTO_SHA2_256 134 
#define  CRYPTO_SHA2_256_HMAC 133 
#define  CRYPTO_SHA2_384 132 
#define  CRYPTO_SHA2_384_HMAC 131 
#define  CRYPTO_SHA2_512 130 
#define  CRYPTO_SHA2_512_HMAC 129 
#define  CRYPTO_SKIPJACK_CBC 128 
 int EINVAL ; 
 int /*<<< orphan*/  crypto_done (struct cryptop*) ; 
 struct swcr_session* crypto_get_driver_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 size_t nitems (struct swcr_data*) ; 
 int swcr_authcompute (struct cryptodesc*,struct swcr_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int swcr_authenc (struct cryptop*) ; 
 int swcr_compdec (struct cryptodesc*,struct swcr_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int swcr_encdec (struct cryptodesc*,struct swcr_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
swcr_process(device_t dev, struct cryptop *crp, int hint)
{
	struct swcr_session *ses = NULL;
	struct cryptodesc *crd;
	struct swcr_data *sw;
	size_t i;

	/* Sanity check */
	if (crp == NULL)
		return EINVAL;

	if (crp->crp_desc == NULL || crp->crp_buf == NULL) {
		crp->crp_etype = EINVAL;
		goto done;
	}

	ses = crypto_get_driver_session(crp->crp_session);
	mtx_lock(&ses->swcr_lock);

	/* Go through crypto descriptors, processing as we go */
	for (crd = crp->crp_desc; crd; crd = crd->crd_next) {
		/*
		 * Find the crypto context.
		 *
		 * XXX Note that the logic here prevents us from having
		 * XXX the same algorithm multiple times in a session
		 * XXX (or rather, we can but it won't give us the right
		 * XXX results). To do that, we'd need some way of differentiating
		 * XXX between the various instances of an algorithm (so we can
		 * XXX locate the correct crypto context).
		 */
		for (i = 0; i < nitems(ses->swcr_algorithms) &&
		    ses->swcr_algorithms[i].sw_alg != crd->crd_alg; i++)
			;

		/* No such context ? */
		if (i == nitems(ses->swcr_algorithms)) {
			crp->crp_etype = EINVAL;
			goto done;
		}
		sw = &ses->swcr_algorithms[i];
		switch (sw->sw_alg) {
		case CRYPTO_DES_CBC:
		case CRYPTO_3DES_CBC:
		case CRYPTO_BLF_CBC:
		case CRYPTO_CAST_CBC:
		case CRYPTO_SKIPJACK_CBC:
		case CRYPTO_RIJNDAEL128_CBC:
		case CRYPTO_AES_XTS:
		case CRYPTO_AES_ICM:
		case CRYPTO_CAMELLIA_CBC:
		case CRYPTO_CHACHA20:
			if ((crp->crp_etype = swcr_encdec(crd, sw,
			    crp->crp_buf, crp->crp_flags)) != 0)
				goto done;
			break;
		case CRYPTO_NULL_CBC:
			crp->crp_etype = 0;
			break;
		case CRYPTO_MD5_HMAC:
		case CRYPTO_SHA1_HMAC:
		case CRYPTO_SHA2_224_HMAC:
		case CRYPTO_SHA2_256_HMAC:
		case CRYPTO_SHA2_384_HMAC:
		case CRYPTO_SHA2_512_HMAC:
		case CRYPTO_RIPEMD160_HMAC:
		case CRYPTO_NULL_HMAC:
		case CRYPTO_MD5_KPDK:
		case CRYPTO_SHA1_KPDK:
		case CRYPTO_MD5:
		case CRYPTO_SHA1:
		case CRYPTO_SHA2_224:
		case CRYPTO_SHA2_256:
		case CRYPTO_SHA2_384:
		case CRYPTO_SHA2_512:
		case CRYPTO_BLAKE2B:
		case CRYPTO_BLAKE2S:
		case CRYPTO_POLY1305:
			if ((crp->crp_etype = swcr_authcompute(crd, sw,
			    crp->crp_buf, crp->crp_flags)) != 0)
				goto done;
			break;

		case CRYPTO_AES_NIST_GCM_16:
		case CRYPTO_AES_NIST_GMAC:
		case CRYPTO_AES_128_NIST_GMAC:
		case CRYPTO_AES_192_NIST_GMAC:
		case CRYPTO_AES_256_NIST_GMAC:
		case CRYPTO_AES_CCM_16:
		case CRYPTO_AES_CCM_CBC_MAC:
			crp->crp_etype = swcr_authenc(crp);
			goto done;

		case CRYPTO_DEFLATE_COMP:
			if ((crp->crp_etype = swcr_compdec(crd, sw, 
			    crp->crp_buf, crp->crp_flags)) != 0)
				goto done;
			else
				crp->crp_olen = (int)sw->sw_size;
			break;

		default:
			/* Unknown/unsupported algorithm */
			crp->crp_etype = EINVAL;
			goto done;
		}
	}

done:
	if (ses)
		mtx_unlock(&ses->swcr_lock);
	crypto_done(crp);
	return 0;
}