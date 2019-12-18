#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_3__* group; } ;
struct TYPE_14__ {int cofactor_mode; int kdf_type; size_t kdf_outlen; unsigned char* kdf_ukm; int kdf_ukmlen; int /*<<< orphan*/ * md; int /*<<< orphan*/ * kdf_md; int /*<<< orphan*/ * co_key; int /*<<< orphan*/ * gen_group; } ;
struct TYPE_13__ {TYPE_2__* pkey; TYPE_5__* data; } ;
struct TYPE_12__ {int /*<<< orphan*/  cofactor; } ;
struct TYPE_10__ {TYPE_6__* ec; } ;
struct TYPE_11__ {TYPE_1__ pkey; } ;
typedef  TYPE_4__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  TYPE_5__ EC_PKEY_CTX ;
typedef  TYPE_6__ EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/  BN_is_one (int /*<<< orphan*/ ) ; 
 int EC_FLAG_COFACTOR_ECDH ; 
 int /*<<< orphan*/  EC_F_PKEY_EC_CTRL ; 
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_GROUP_new_by_curve_name (int) ; 
 int /*<<< orphan*/  EC_GROUP_set_asn1_flag (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EC_KEY_clear_flags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * EC_KEY_dup (TYPE_6__*) ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int EC_KEY_get_flags (TYPE_6__*) ; 
 int /*<<< orphan*/  EC_KEY_set_flags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EC_R_INVALID_CURVE ; 
 int /*<<< orphan*/  EC_R_INVALID_DIGEST_TYPE ; 
 int /*<<< orphan*/  EC_R_NO_PARAMETERS_SET ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_type (int /*<<< orphan*/  const*) ; 
#define  EVP_PKEY_CTRL_CMS_SIGN 143 
#define  EVP_PKEY_CTRL_DIGESTINIT 142 
#define  EVP_PKEY_CTRL_EC_ECDH_COFACTOR 141 
#define  EVP_PKEY_CTRL_EC_KDF_MD 140 
#define  EVP_PKEY_CTRL_EC_KDF_OUTLEN 139 
#define  EVP_PKEY_CTRL_EC_KDF_TYPE 138 
#define  EVP_PKEY_CTRL_EC_KDF_UKM 137 
#define  EVP_PKEY_CTRL_EC_PARAMGEN_CURVE_NID 136 
#define  EVP_PKEY_CTRL_EC_PARAM_ENC 135 
#define  EVP_PKEY_CTRL_GET_EC_KDF_MD 134 
#define  EVP_PKEY_CTRL_GET_EC_KDF_OUTLEN 133 
#define  EVP_PKEY_CTRL_GET_EC_KDF_UKM 132 
#define  EVP_PKEY_CTRL_GET_MD 131 
#define  EVP_PKEY_CTRL_MD 130 
#define  EVP_PKEY_CTRL_PEER_KEY 129 
#define  EVP_PKEY_CTRL_PKCS7_SIGN 128 
 int EVP_PKEY_ECDH_KDF_NONE ; 
 int EVP_PKEY_ECDH_KDF_X9_63 ; 
 int /*<<< orphan*/  NID_ecdsa_with_SHA1 ; 
 int /*<<< orphan*/  NID_sha1 ; 
 int /*<<< orphan*/  NID_sha224 ; 
 int /*<<< orphan*/  NID_sha256 ; 
 int /*<<< orphan*/  NID_sha384 ; 
 int /*<<< orphan*/  NID_sha3_224 ; 
 int /*<<< orphan*/  NID_sha3_256 ; 
 int /*<<< orphan*/  NID_sha3_384 ; 
 int /*<<< orphan*/  NID_sha3_512 ; 
 int /*<<< orphan*/  NID_sha512 ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 

__attribute__((used)) static int pkey_ec_ctrl(EVP_PKEY_CTX *ctx, int type, int p1, void *p2)
{
    EC_PKEY_CTX *dctx = ctx->data;
    EC_GROUP *group;
    switch (type) {
    case EVP_PKEY_CTRL_EC_PARAMGEN_CURVE_NID:
        group = EC_GROUP_new_by_curve_name(p1);
        if (group == NULL) {
            ECerr(EC_F_PKEY_EC_CTRL, EC_R_INVALID_CURVE);
            return 0;
        }
        EC_GROUP_free(dctx->gen_group);
        dctx->gen_group = group;
        return 1;

    case EVP_PKEY_CTRL_EC_PARAM_ENC:
        if (!dctx->gen_group) {
            ECerr(EC_F_PKEY_EC_CTRL, EC_R_NO_PARAMETERS_SET);
            return 0;
        }
        EC_GROUP_set_asn1_flag(dctx->gen_group, p1);
        return 1;

#ifndef OPENSSL_NO_EC
    case EVP_PKEY_CTRL_EC_ECDH_COFACTOR:
        if (p1 == -2) {
            if (dctx->cofactor_mode != -1)
                return dctx->cofactor_mode;
            else {
                EC_KEY *ec_key = ctx->pkey->pkey.ec;
                return EC_KEY_get_flags(ec_key) & EC_FLAG_COFACTOR_ECDH ? 1 : 0;
            }
        } else if (p1 < -1 || p1 > 1)
            return -2;
        dctx->cofactor_mode = p1;
        if (p1 != -1) {
            EC_KEY *ec_key = ctx->pkey->pkey.ec;
            if (!ec_key->group)
                return -2;
            /* If cofactor is 1 cofactor mode does nothing */
            if (BN_is_one(ec_key->group->cofactor))
                return 1;
            if (!dctx->co_key) {
                dctx->co_key = EC_KEY_dup(ec_key);
                if (!dctx->co_key)
                    return 0;
            }
            if (p1)
                EC_KEY_set_flags(dctx->co_key, EC_FLAG_COFACTOR_ECDH);
            else
                EC_KEY_clear_flags(dctx->co_key, EC_FLAG_COFACTOR_ECDH);
        } else {
            EC_KEY_free(dctx->co_key);
            dctx->co_key = NULL;
        }
        return 1;
#endif

    case EVP_PKEY_CTRL_EC_KDF_TYPE:
        if (p1 == -2)
            return dctx->kdf_type;
        if (p1 != EVP_PKEY_ECDH_KDF_NONE && p1 != EVP_PKEY_ECDH_KDF_X9_63)
            return -2;
        dctx->kdf_type = p1;
        return 1;

    case EVP_PKEY_CTRL_EC_KDF_MD:
        dctx->kdf_md = p2;
        return 1;

    case EVP_PKEY_CTRL_GET_EC_KDF_MD:
        *(const EVP_MD **)p2 = dctx->kdf_md;
        return 1;

    case EVP_PKEY_CTRL_EC_KDF_OUTLEN:
        if (p1 <= 0)
            return -2;
        dctx->kdf_outlen = (size_t)p1;
        return 1;

    case EVP_PKEY_CTRL_GET_EC_KDF_OUTLEN:
        *(int *)p2 = dctx->kdf_outlen;
        return 1;

    case EVP_PKEY_CTRL_EC_KDF_UKM:
        OPENSSL_free(dctx->kdf_ukm);
        dctx->kdf_ukm = p2;
        if (p2)
            dctx->kdf_ukmlen = p1;
        else
            dctx->kdf_ukmlen = 0;
        return 1;

    case EVP_PKEY_CTRL_GET_EC_KDF_UKM:
        *(unsigned char **)p2 = dctx->kdf_ukm;
        return dctx->kdf_ukmlen;

    case EVP_PKEY_CTRL_MD:
        if (EVP_MD_type((const EVP_MD *)p2) != NID_sha1 &&
            EVP_MD_type((const EVP_MD *)p2) != NID_ecdsa_with_SHA1 &&
            EVP_MD_type((const EVP_MD *)p2) != NID_sha224 &&
            EVP_MD_type((const EVP_MD *)p2) != NID_sha256 &&
            EVP_MD_type((const EVP_MD *)p2) != NID_sha384 &&
            EVP_MD_type((const EVP_MD *)p2) != NID_sha512 &&
            EVP_MD_type((const EVP_MD *)p2) != NID_sha3_224 &&
            EVP_MD_type((const EVP_MD *)p2) != NID_sha3_256 &&
            EVP_MD_type((const EVP_MD *)p2) != NID_sha3_384 &&
            EVP_MD_type((const EVP_MD *)p2) != NID_sha3_512) {
            ECerr(EC_F_PKEY_EC_CTRL, EC_R_INVALID_DIGEST_TYPE);
            return 0;
        }
        dctx->md = p2;
        return 1;

    case EVP_PKEY_CTRL_GET_MD:
        *(const EVP_MD **)p2 = dctx->md;
        return 1;

    case EVP_PKEY_CTRL_PEER_KEY:
        /* Default behaviour is OK */
    case EVP_PKEY_CTRL_DIGESTINIT:
    case EVP_PKEY_CTRL_PKCS7_SIGN:
    case EVP_PKEY_CTRL_CMS_SIGN:
        return 1;

    default:
        return -2;

    }
}