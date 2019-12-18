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
struct swcr_session {struct swcr_data* swcr_algorithms; int /*<<< orphan*/  swcr_lock; } ;
struct swcr_data {int sw_alg; int /*<<< orphan*/  sw_ictx; struct auth_hash* sw_axf; int /*<<< orphan*/  sw_octx; int /*<<< orphan*/  sw_klen; int /*<<< orphan*/  sw_kschedule; struct enc_xform* sw_exf; } ;
struct enc_xform {int /*<<< orphan*/  (* zerokey ) (int /*<<< orphan*/ *) ;} ;
struct auth_hash {int /*<<< orphan*/  ctxsize; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  crypto_session_t ;

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
 int /*<<< orphan*/  M_CRYPTO_DATA ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct swcr_session* crypto_get_driver_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 size_t nitems (struct swcr_data*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
swcr_freesession(device_t dev, crypto_session_t cses)
{
	struct swcr_session *ses;
	struct swcr_data *swd;
	struct enc_xform *txf;
	struct auth_hash *axf;
	size_t i;

	ses = crypto_get_driver_session(cses);

	mtx_destroy(&ses->swcr_lock);
	for (i = 0; i < nitems(ses->swcr_algorithms); i++) {
		swd = &ses->swcr_algorithms[i];

		switch (swd->sw_alg) {
		case CRYPTO_DES_CBC:
		case CRYPTO_3DES_CBC:
		case CRYPTO_BLF_CBC:
		case CRYPTO_CAST_CBC:
		case CRYPTO_SKIPJACK_CBC:
		case CRYPTO_RIJNDAEL128_CBC:
		case CRYPTO_AES_XTS:
		case CRYPTO_AES_ICM:
		case CRYPTO_AES_NIST_GCM_16:
		case CRYPTO_AES_NIST_GMAC:
		case CRYPTO_CAMELLIA_CBC:
		case CRYPTO_NULL_CBC:
		case CRYPTO_CHACHA20:
		case CRYPTO_AES_CCM_16:
			txf = swd->sw_exf;

			if (swd->sw_kschedule)
				txf->zerokey(&(swd->sw_kschedule));
			break;

		case CRYPTO_MD5_HMAC:
		case CRYPTO_SHA1_HMAC:
		case CRYPTO_SHA2_224_HMAC:
		case CRYPTO_SHA2_256_HMAC:
		case CRYPTO_SHA2_384_HMAC:
		case CRYPTO_SHA2_512_HMAC:
		case CRYPTO_RIPEMD160_HMAC:
		case CRYPTO_NULL_HMAC:
		case CRYPTO_AES_CCM_CBC_MAC:
			axf = swd->sw_axf;

			if (swd->sw_ictx) {
				bzero(swd->sw_ictx, axf->ctxsize);
				free(swd->sw_ictx, M_CRYPTO_DATA);
			}
			if (swd->sw_octx) {
				bzero(swd->sw_octx, axf->ctxsize);
				free(swd->sw_octx, M_CRYPTO_DATA);
			}
			break;

		case CRYPTO_MD5_KPDK:
		case CRYPTO_SHA1_KPDK:
			axf = swd->sw_axf;

			if (swd->sw_ictx) {
				bzero(swd->sw_ictx, axf->ctxsize);
				free(swd->sw_ictx, M_CRYPTO_DATA);
			}
			if (swd->sw_octx) {
				bzero(swd->sw_octx, swd->sw_klen);
				free(swd->sw_octx, M_CRYPTO_DATA);
			}
			break;

		case CRYPTO_BLAKE2B:
		case CRYPTO_BLAKE2S:
		case CRYPTO_MD5:
		case CRYPTO_POLY1305:
		case CRYPTO_SHA1:
		case CRYPTO_SHA2_224:
		case CRYPTO_SHA2_256:
		case CRYPTO_SHA2_384:
		case CRYPTO_SHA2_512:
		case CRYPTO_AES_128_NIST_GMAC:
		case CRYPTO_AES_192_NIST_GMAC:
		case CRYPTO_AES_256_NIST_GMAC:
			axf = swd->sw_axf;

			if (swd->sw_ictx) {
				explicit_bzero(swd->sw_ictx, axf->ctxsize);
				free(swd->sw_ictx, M_CRYPTO_DATA);
			}
			break;

		case CRYPTO_DEFLATE_COMP:
			/* Nothing to do */
			break;
		}
	}
}