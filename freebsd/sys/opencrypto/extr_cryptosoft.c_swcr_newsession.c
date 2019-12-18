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
struct swcr_session {int /*<<< orphan*/  swcr_nalgs; struct swcr_data* swcr_algorithms; int /*<<< orphan*/  swcr_lock; } ;
struct swcr_data {int sw_alg; struct comp_algo* sw_cxf; struct auth_hash* sw_axf; int /*<<< orphan*/ * sw_ictx; int /*<<< orphan*/  sw_mlen; int /*<<< orphan*/ * sw_octx; struct enc_xform* sw_exf; int /*<<< orphan*/  sw_kschedule; } ;
struct enc_xform {int (* setkey ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;} ;
struct cryptoini {int cri_alg; int cri_klen; struct cryptoini* cri_next; int /*<<< orphan*/ * cri_key; int /*<<< orphan*/  cri_mlen; } ;
struct comp_algo {int dummy; } ;
struct auth_hash {int ctxsize; int /*<<< orphan*/  (* Init ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* Setkey ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;} ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/ * crypto_session_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTDEB (char*) ; 
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
 int ENOBUFS ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_CRYPTO_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 struct auth_hash auth_hash_blake2b ; 
 struct auth_hash auth_hash_blake2s ; 
 struct auth_hash auth_hash_ccm_cbc_mac_128 ; 
 struct auth_hash auth_hash_ccm_cbc_mac_192 ; 
 struct auth_hash auth_hash_ccm_cbc_mac_256 ; 
 struct auth_hash auth_hash_hmac_md5 ; 
 struct auth_hash auth_hash_hmac_ripemd_160 ; 
 struct auth_hash auth_hash_hmac_sha1 ; 
 struct auth_hash auth_hash_hmac_sha2_224 ; 
 struct auth_hash auth_hash_hmac_sha2_256 ; 
 struct auth_hash auth_hash_hmac_sha2_384 ; 
 struct auth_hash auth_hash_hmac_sha2_512 ; 
 struct auth_hash auth_hash_key_md5 ; 
 struct auth_hash auth_hash_key_sha1 ; 
 struct auth_hash auth_hash_md5 ; 
 struct auth_hash auth_hash_nist_gmac_aes_128 ; 
 struct auth_hash auth_hash_nist_gmac_aes_192 ; 
 struct auth_hash auth_hash_nist_gmac_aes_256 ; 
 struct auth_hash auth_hash_null ; 
 struct auth_hash auth_hash_poly1305 ; 
 struct auth_hash auth_hash_sha1 ; 
 struct auth_hash auth_hash_sha2_224 ; 
 struct auth_hash auth_hash_sha2_256 ; 
 struct auth_hash auth_hash_sha2_384 ; 
 struct auth_hash auth_hash_sha2_512 ; 
 struct comp_algo comp_algo_deflate ; 
 struct swcr_session* crypto_get_driver_session (int /*<<< orphan*/ *) ; 
 struct enc_xform enc_xform_3des ; 
 struct enc_xform enc_xform_aes_icm ; 
 struct enc_xform enc_xform_aes_nist_gcm ; 
 struct enc_xform enc_xform_aes_nist_gmac ; 
 struct enc_xform enc_xform_aes_xts ; 
 struct enc_xform enc_xform_blf ; 
 struct enc_xform enc_xform_camellia ; 
 struct enc_xform enc_xform_cast5 ; 
 struct enc_xform enc_xform_ccm ; 
 struct enc_xform enc_xform_chacha20 ; 
 struct enc_xform enc_xform_des ; 
 struct enc_xform enc_xform_null ; 
 struct enc_xform enc_xform_rijndael128 ; 
 struct enc_xform enc_xform_skipjack ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t nitems (struct swcr_data*) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *) ; 
 int swcr_authprepare (struct auth_hash*,struct swcr_data*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  swcr_freesession (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
swcr_newsession(device_t dev, crypto_session_t cses, struct cryptoini *cri)
{
	struct swcr_session *ses;
	struct swcr_data *swd;
	struct auth_hash *axf;
	struct enc_xform *txf;
	struct comp_algo *cxf;
	size_t i;
	int len;
	int error;

	if (cses == NULL || cri == NULL)
		return EINVAL;

	ses = crypto_get_driver_session(cses);
	mtx_init(&ses->swcr_lock, "swcr session lock", NULL, MTX_DEF);

	for (i = 0; cri != NULL && i < nitems(ses->swcr_algorithms); i++) {
		swd = &ses->swcr_algorithms[i];

		switch (cri->cri_alg) {
		case CRYPTO_DES_CBC:
			txf = &enc_xform_des;
			goto enccommon;
		case CRYPTO_3DES_CBC:
			txf = &enc_xform_3des;
			goto enccommon;
		case CRYPTO_BLF_CBC:
			txf = &enc_xform_blf;
			goto enccommon;
		case CRYPTO_CAST_CBC:
			txf = &enc_xform_cast5;
			goto enccommon;
		case CRYPTO_SKIPJACK_CBC:
			txf = &enc_xform_skipjack;
			goto enccommon;
		case CRYPTO_RIJNDAEL128_CBC:
			txf = &enc_xform_rijndael128;
			goto enccommon;
		case CRYPTO_AES_XTS:
			txf = &enc_xform_aes_xts;
			goto enccommon;
		case CRYPTO_AES_ICM:
			txf = &enc_xform_aes_icm;
			goto enccommon;
		case CRYPTO_AES_NIST_GCM_16:
			txf = &enc_xform_aes_nist_gcm;
			goto enccommon;
		case CRYPTO_AES_CCM_16:
			txf = &enc_xform_ccm;
			goto enccommon;
		case CRYPTO_AES_NIST_GMAC:
			txf = &enc_xform_aes_nist_gmac;
			swd->sw_exf = txf;
			break;
		case CRYPTO_CAMELLIA_CBC:
			txf = &enc_xform_camellia;
			goto enccommon;
		case CRYPTO_NULL_CBC:
			txf = &enc_xform_null;
			goto enccommon;
		case CRYPTO_CHACHA20:
			txf = &enc_xform_chacha20;
			goto enccommon;
		enccommon:
			if (cri->cri_key != NULL) {
				error = txf->setkey(&swd->sw_kschedule,
				    cri->cri_key, cri->cri_klen / 8);
				if (error) {
					swcr_freesession(dev, cses);
					return error;
				}
			}
			swd->sw_exf = txf;
			break;
	
		case CRYPTO_MD5_HMAC:
			axf = &auth_hash_hmac_md5;
			goto authcommon;
		case CRYPTO_SHA1_HMAC:
			axf = &auth_hash_hmac_sha1;
			goto authcommon;
		case CRYPTO_SHA2_224_HMAC:
			axf = &auth_hash_hmac_sha2_224;
			goto authcommon;
		case CRYPTO_SHA2_256_HMAC:
			axf = &auth_hash_hmac_sha2_256;
			goto authcommon;
		case CRYPTO_SHA2_384_HMAC:
			axf = &auth_hash_hmac_sha2_384;
			goto authcommon;
		case CRYPTO_SHA2_512_HMAC:
			axf = &auth_hash_hmac_sha2_512;
			goto authcommon;
		case CRYPTO_NULL_HMAC:
			axf = &auth_hash_null;
			goto authcommon;
		case CRYPTO_RIPEMD160_HMAC:
			axf = &auth_hash_hmac_ripemd_160;
		authcommon:
			swd->sw_ictx = malloc(axf->ctxsize, M_CRYPTO_DATA,
			    M_NOWAIT);
			if (swd->sw_ictx == NULL) {
				swcr_freesession(dev, cses);
				return ENOBUFS;
			}
	
			swd->sw_octx = malloc(axf->ctxsize, M_CRYPTO_DATA,
			    M_NOWAIT);
			if (swd->sw_octx == NULL) {
				swcr_freesession(dev, cses);
				return ENOBUFS;
			}

			if (cri->cri_key != NULL) {
				error = swcr_authprepare(axf, swd,
				    cri->cri_key, cri->cri_klen);
				if (error != 0) {
					swcr_freesession(dev, cses);
					return error;
				}
			}

			swd->sw_mlen = cri->cri_mlen;
			swd->sw_axf = axf;
			break;
	
		case CRYPTO_MD5_KPDK:
			axf = &auth_hash_key_md5;
			goto auth2common;
	
		case CRYPTO_SHA1_KPDK:
			axf = &auth_hash_key_sha1;
		auth2common:
			swd->sw_ictx = malloc(axf->ctxsize, M_CRYPTO_DATA,
			    M_NOWAIT);
			if (swd->sw_ictx == NULL) {
				swcr_freesession(dev, cses);
				return ENOBUFS;
			}
	
			swd->sw_octx = malloc(cri->cri_klen / 8,
			    M_CRYPTO_DATA, M_NOWAIT);
			if (swd->sw_octx == NULL) {
				swcr_freesession(dev, cses);
				return ENOBUFS;
			}

			/* Store the key so we can "append" it to the payload */
			if (cri->cri_key != NULL) {
				error = swcr_authprepare(axf, swd,
				    cri->cri_key, cri->cri_klen);
				if (error != 0) {
					swcr_freesession(dev, cses);
					return error;
				}
			}

			swd->sw_mlen = cri->cri_mlen;
			swd->sw_axf = axf;
			break;
#ifdef notdef
		case CRYPTO_MD5:
			axf = &auth_hash_md5;
			goto auth3common;
#endif

		case CRYPTO_SHA1:
			axf = &auth_hash_sha1;
			goto auth3common;
		case CRYPTO_SHA2_224:
			axf = &auth_hash_sha2_224;
			goto auth3common;
		case CRYPTO_SHA2_256:
			axf = &auth_hash_sha2_256;
			goto auth3common;
		case CRYPTO_SHA2_384:
			axf = &auth_hash_sha2_384;
			goto auth3common;
		case CRYPTO_SHA2_512:
			axf = &auth_hash_sha2_512;

		auth3common:
			swd->sw_ictx = malloc(axf->ctxsize, M_CRYPTO_DATA,
			    M_NOWAIT);
			if (swd->sw_ictx == NULL) {
				swcr_freesession(dev, cses);
				return ENOBUFS;
			}

			axf->Init(swd->sw_ictx);
			swd->sw_mlen = cri->cri_mlen;
			swd->sw_axf = axf;
			break;

		case CRYPTO_AES_CCM_CBC_MAC:
			switch (cri->cri_klen) {
			case 128:
				axf = &auth_hash_ccm_cbc_mac_128;
				break;
			case 192:
				axf = &auth_hash_ccm_cbc_mac_192;
				break;
			case 256:
				axf = &auth_hash_ccm_cbc_mac_256;
				break;
			default:
				swcr_freesession(dev, cses);
				return EINVAL;
			}
			goto auth4common;
		case CRYPTO_AES_128_NIST_GMAC:
			axf = &auth_hash_nist_gmac_aes_128;
			goto auth4common;

		case CRYPTO_AES_192_NIST_GMAC:
			axf = &auth_hash_nist_gmac_aes_192;
			goto auth4common;

		case CRYPTO_AES_256_NIST_GMAC:
			axf = &auth_hash_nist_gmac_aes_256;
		auth4common:
			len = cri->cri_klen / 8;
			if (len != 16 && len != 24 && len != 32) {
				swcr_freesession(dev, cses);
				return EINVAL;
			}

			swd->sw_ictx = malloc(axf->ctxsize, M_CRYPTO_DATA,
			    M_NOWAIT);
			if (swd->sw_ictx == NULL) {
				swcr_freesession(dev, cses);
				return ENOBUFS;
			}
			axf->Init(swd->sw_ictx);
			axf->Setkey(swd->sw_ictx, cri->cri_key, len);
			swd->sw_axf = axf;
			break;

		case CRYPTO_BLAKE2B:
			axf = &auth_hash_blake2b;
			goto auth5common;
		case CRYPTO_BLAKE2S:
			axf = &auth_hash_blake2s;
			goto auth5common;
		case CRYPTO_POLY1305:
			axf = &auth_hash_poly1305;
		auth5common:
			swd->sw_ictx = malloc(axf->ctxsize, M_CRYPTO_DATA,
			    M_NOWAIT);
			if (swd->sw_ictx == NULL) {
				swcr_freesession(dev, cses);
				return ENOBUFS;
			}
			axf->Setkey(swd->sw_ictx, cri->cri_key,
			    cri->cri_klen / 8);
			axf->Init(swd->sw_ictx);
			swd->sw_axf = axf;
			break;

		case CRYPTO_DEFLATE_COMP:
			cxf = &comp_algo_deflate;
			swd->sw_cxf = cxf;
			break;
		default:
			swcr_freesession(dev, cses);
			return EINVAL;
		}
	
		swd->sw_alg = cri->cri_alg;
		cri = cri->cri_next;
		ses->swcr_nalgs++;
	}

	if (cri != NULL) {
		CRYPTDEB("Bogus session request for three or more algorithms");
		return EINVAL;
	}
	return 0;
}