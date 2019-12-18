#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_1__ X509_ALGOR ;
typedef  int /*<<< orphan*/  RSA_PSS_PARAMS ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestVerifyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_MD_type (int /*<<< orphan*/  const*) ; 
 scalar_t__ EVP_PKEY_CTX_get_signature_md (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 scalar_t__ EVP_PKEY_CTX_set_rsa_mgf1_md (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ EVP_PKEY_CTX_set_rsa_padding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_PKEY_CTX_set_rsa_pss_saltlen (int /*<<< orphan*/ *,int) ; 
 scalar_t__ EVP_PKEY_RSA_PSS ; 
 scalar_t__ OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSA_F_RSA_PSS_TO_CTX ; 
 int /*<<< orphan*/  RSA_PKCS1_PSS_PADDING ; 
 int /*<<< orphan*/  RSA_PSS_PARAMS_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_R_DIGEST_DOES_NOT_MATCH ; 
 int /*<<< orphan*/  RSA_R_INVALID_PSS_PARAMETERS ; 
 int /*<<< orphan*/  RSA_R_UNSUPPORTED_SIGNATURE_TYPE ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rsa_pss_decode (TYPE_1__*) ; 
 int /*<<< orphan*/  rsa_pss_get_param (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int*) ; 

__attribute__((used)) static int rsa_pss_to_ctx(EVP_MD_CTX *ctx, EVP_PKEY_CTX *pkctx,
                          X509_ALGOR *sigalg, EVP_PKEY *pkey)
{
    int rv = -1;
    int saltlen;
    const EVP_MD *mgf1md = NULL, *md = NULL;
    RSA_PSS_PARAMS *pss;

    /* Sanity check: make sure it is PSS */
    if (OBJ_obj2nid(sigalg->algorithm) != EVP_PKEY_RSA_PSS) {
        RSAerr(RSA_F_RSA_PSS_TO_CTX, RSA_R_UNSUPPORTED_SIGNATURE_TYPE);
        return -1;
    }
    /* Decode PSS parameters */
    pss = rsa_pss_decode(sigalg);

    if (!rsa_pss_get_param(pss, &md, &mgf1md, &saltlen)) {
        RSAerr(RSA_F_RSA_PSS_TO_CTX, RSA_R_INVALID_PSS_PARAMETERS);
        goto err;
    }

    /* We have all parameters now set up context */
    if (pkey) {
        if (!EVP_DigestVerifyInit(ctx, &pkctx, md, NULL, pkey))
            goto err;
    } else {
        const EVP_MD *checkmd;
        if (EVP_PKEY_CTX_get_signature_md(pkctx, &checkmd) <= 0)
            goto err;
        if (EVP_MD_type(md) != EVP_MD_type(checkmd)) {
            RSAerr(RSA_F_RSA_PSS_TO_CTX, RSA_R_DIGEST_DOES_NOT_MATCH);
            goto err;
        }
    }

    if (EVP_PKEY_CTX_set_rsa_padding(pkctx, RSA_PKCS1_PSS_PADDING) <= 0)
        goto err;

    if (EVP_PKEY_CTX_set_rsa_pss_saltlen(pkctx, saltlen) <= 0)
        goto err;

    if (EVP_PKEY_CTX_set_rsa_mgf1_md(pkctx, mgf1md) <= 0)
        goto err;
    /* Carry on */
    rv = 1;

 err:
    RSA_PSS_PARAMS_free(pss);
    return rv;
}