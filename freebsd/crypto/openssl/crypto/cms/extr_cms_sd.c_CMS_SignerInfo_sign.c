#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  signature; scalar_t__ signedAttrs; int /*<<< orphan*/ * pctx; int /*<<< orphan*/  pkey; TYPE_1__* digestAlgorithm; int /*<<< orphan*/ * mctx; } ;
struct TYPE_8__ {int /*<<< orphan*/  algorithm; } ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  TYPE_2__ CMS_SignerInfo ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_ITEM_rptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_STRING_set0 (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int ASN1_item_i2d (int /*<<< orphan*/ *,unsigned char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMS_Attributes_Sign ; 
 int /*<<< orphan*/  CMS_F_CMS_SIGNERINFO_SIGN ; 
 int /*<<< orphan*/  CMS_R_CTRL_ERROR ; 
 int /*<<< orphan*/  CMS_si_check_attributes (TYPE_2__*) ; 
 scalar_t__ CMS_signed_get_attr_by_NID (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_DigestSignFinal (int /*<<< orphan*/ *,unsigned char*,size_t*) ; 
 scalar_t__ EVP_DigestSignInit (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_DigestSignUpdate (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_MD_CTX_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_CTRL_CMS_SIGN ; 
 scalar_t__ EVP_PKEY_CTX_ctrl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  EVP_PKEY_OP_SIGN ; 
 int /*<<< orphan*/ * EVP_get_digestbyobj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NID_pkcs9_signingTime ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  cms_add1_signingTime (TYPE_2__*,int /*<<< orphan*/ *) ; 

int CMS_SignerInfo_sign(CMS_SignerInfo *si)
{
    EVP_MD_CTX *mctx = si->mctx;
    EVP_PKEY_CTX *pctx = NULL;
    unsigned char *abuf = NULL;
    int alen;
    size_t siglen;
    const EVP_MD *md = NULL;

    md = EVP_get_digestbyobj(si->digestAlgorithm->algorithm);
    if (md == NULL)
        return 0;

    if (CMS_signed_get_attr_by_NID(si, NID_pkcs9_signingTime, -1) < 0) {
        if (!cms_add1_signingTime(si, NULL))
            goto err;
    }

    if (!CMS_si_check_attributes(si))
        goto err;

    if (si->pctx)
        pctx = si->pctx;
    else {
        EVP_MD_CTX_reset(mctx);
        if (EVP_DigestSignInit(mctx, &pctx, md, NULL, si->pkey) <= 0)
            goto err;
        si->pctx = pctx;
    }

    if (EVP_PKEY_CTX_ctrl(pctx, -1, EVP_PKEY_OP_SIGN,
                          EVP_PKEY_CTRL_CMS_SIGN, 0, si) <= 0) {
        CMSerr(CMS_F_CMS_SIGNERINFO_SIGN, CMS_R_CTRL_ERROR);
        goto err;
    }

    alen = ASN1_item_i2d((ASN1_VALUE *)si->signedAttrs, &abuf,
                         ASN1_ITEM_rptr(CMS_Attributes_Sign));
    if (!abuf)
        goto err;
    if (EVP_DigestSignUpdate(mctx, abuf, alen) <= 0)
        goto err;
    if (EVP_DigestSignFinal(mctx, NULL, &siglen) <= 0)
        goto err;
    OPENSSL_free(abuf);
    abuf = OPENSSL_malloc(siglen);
    if (abuf == NULL)
        goto err;
    if (EVP_DigestSignFinal(mctx, abuf, &siglen) <= 0)
        goto err;

    if (EVP_PKEY_CTX_ctrl(pctx, -1, EVP_PKEY_OP_SIGN,
                          EVP_PKEY_CTRL_CMS_SIGN, 1, si) <= 0) {
        CMSerr(CMS_F_CMS_SIGNERINFO_SIGN, CMS_R_CTRL_ERROR);
        goto err;
    }

    EVP_MD_CTX_reset(mctx);

    ASN1_STRING_set0(si->signature, abuf, siglen);

    return 1;

 err:
    OPENSSL_free(abuf);
    EVP_MD_CTX_reset(mctx);
    return 0;
}