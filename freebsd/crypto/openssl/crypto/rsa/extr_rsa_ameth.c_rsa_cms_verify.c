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
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  CMS_SignerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_SignerInfo_get0_algs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/ * CMS_SignerInfo_get0_pkey_ctx (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_RSA_PSS ; 
 int NID_rsaEncryption ; 
 scalar_t__ OBJ_find_sigid_algs (int,int /*<<< orphan*/ *,int*) ; 
 int OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSA_F_RSA_CMS_VERIFY ; 
 int /*<<< orphan*/  RSA_R_ILLEGAL_OR_UNSUPPORTED_PADDING_MODE ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pkey_ctx_is_pss (int /*<<< orphan*/ *) ; 
 int rsa_pss_to_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rsa_cms_verify(CMS_SignerInfo *si)
{
    int nid, nid2;
    X509_ALGOR *alg;
    EVP_PKEY_CTX *pkctx = CMS_SignerInfo_get0_pkey_ctx(si);

    CMS_SignerInfo_get0_algs(si, NULL, NULL, NULL, &alg);
    nid = OBJ_obj2nid(alg->algorithm);
    if (nid == EVP_PKEY_RSA_PSS)
        return rsa_pss_to_ctx(NULL, pkctx, alg, NULL);
    /* Only PSS allowed for PSS keys */
    if (pkey_ctx_is_pss(pkctx)) {
        RSAerr(RSA_F_RSA_CMS_VERIFY, RSA_R_ILLEGAL_OR_UNSUPPORTED_PADDING_MODE);
        return 0;
    }
    if (nid == NID_rsaEncryption)
        return 1;
    /* Workaround for some implementation that use a signature OID */
    if (OBJ_find_sigid_algs(nid, NULL, &nid2)) {
        if (nid2 == NID_rsaEncryption)
            return 1;
    }
    return 0;
}