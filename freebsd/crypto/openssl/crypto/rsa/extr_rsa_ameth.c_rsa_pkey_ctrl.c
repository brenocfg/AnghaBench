#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_ALGOR ;
struct TYPE_7__ {TYPE_1__* rsa; } ;
struct TYPE_8__ {TYPE_2__ pkey; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pss; } ;
typedef  TYPE_3__ EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
#define  ASN1_PKEY_CTRL_CMS_ENVELOPE 133 
#define  ASN1_PKEY_CTRL_CMS_RI_TYPE 132 
#define  ASN1_PKEY_CTRL_CMS_SIGN 131 
#define  ASN1_PKEY_CTRL_DEFAULT_MD_NID 130 
#define  ASN1_PKEY_CTRL_PKCS7_ENCRYPT 129 
#define  ASN1_PKEY_CTRL_PKCS7_SIGN 128 
 int CMS_RECIPINFO_TRANS ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int EVP_MD_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  NID_rsaEncryption ; 
 int NID_sha256 ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKCS7_RECIP_INFO_get0_alg (void*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PKCS7_SIGNER_INFO_get0_algs (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_ASN1_NULL ; 
 int /*<<< orphan*/  X509_ALGOR_set0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkey_is_pss (TYPE_3__*) ; 
 int rsa_cms_decrypt (void*) ; 
 int rsa_cms_encrypt (void*) ; 
 int rsa_cms_sign (void*) ; 
 int rsa_cms_verify (void*) ; 
 int /*<<< orphan*/  rsa_pss_get_param (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int*) ; 

__attribute__((used)) static int rsa_pkey_ctrl(EVP_PKEY *pkey, int op, long arg1, void *arg2)
{
    X509_ALGOR *alg = NULL;
    const EVP_MD *md;
    const EVP_MD *mgf1md;
    int min_saltlen;

    switch (op) {

    case ASN1_PKEY_CTRL_PKCS7_SIGN:
        if (arg1 == 0)
            PKCS7_SIGNER_INFO_get0_algs(arg2, NULL, NULL, &alg);
        break;

    case ASN1_PKEY_CTRL_PKCS7_ENCRYPT:
        if (pkey_is_pss(pkey))
            return -2;
        if (arg1 == 0)
            PKCS7_RECIP_INFO_get0_alg(arg2, &alg);
        break;
#ifndef OPENSSL_NO_CMS
    case ASN1_PKEY_CTRL_CMS_SIGN:
        if (arg1 == 0)
            return rsa_cms_sign(arg2);
        else if (arg1 == 1)
            return rsa_cms_verify(arg2);
        break;

    case ASN1_PKEY_CTRL_CMS_ENVELOPE:
        if (pkey_is_pss(pkey))
            return -2;
        if (arg1 == 0)
            return rsa_cms_encrypt(arg2);
        else if (arg1 == 1)
            return rsa_cms_decrypt(arg2);
        break;

    case ASN1_PKEY_CTRL_CMS_RI_TYPE:
        if (pkey_is_pss(pkey))
            return -2;
        *(int *)arg2 = CMS_RECIPINFO_TRANS;
        return 1;
#endif

    case ASN1_PKEY_CTRL_DEFAULT_MD_NID:
        if (pkey->pkey.rsa->pss != NULL) {
            if (!rsa_pss_get_param(pkey->pkey.rsa->pss, &md, &mgf1md,
                                   &min_saltlen)) {
                RSAerr(0, ERR_R_INTERNAL_ERROR);
                return 0;
            }
            *(int *)arg2 = EVP_MD_type(md);
            /* Return of 2 indicates this MD is mandatory */
            return 2;
        }
        *(int *)arg2 = NID_sha256;
        return 1;

    default:
        return -2;

    }

    if (alg)
        X509_ALGOR_set0(alg, OBJ_nid2obj(NID_rsaEncryption), V_ASN1_NULL, 0);

    return 1;

}