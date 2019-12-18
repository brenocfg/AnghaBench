#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* signature; scalar_t__ signedAttrs; int /*<<< orphan*/  pkey; int /*<<< orphan*/  pctx; int /*<<< orphan*/ * mctx; TYPE_1__* digestAlgorithm; } ;
struct TYPE_8__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int /*<<< orphan*/  algorithm; } ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  TYPE_3__ CMS_SignerInfo ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_ITEM_rptr (int /*<<< orphan*/ ) ; 
 int ASN1_item_i2d (int /*<<< orphan*/ *,unsigned char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMS_Attributes_Verify ; 
 int /*<<< orphan*/  CMS_F_CMS_SIGNERINFO_VERIFY ; 
 int /*<<< orphan*/  CMS_R_NO_PUBLIC_KEY ; 
 int /*<<< orphan*/  CMS_R_VERIFICATION_FAILURE ; 
 int /*<<< orphan*/  CMS_si_check_attributes (TYPE_3__*) ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int EVP_DigestVerifyFinal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_DigestVerifyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int EVP_DigestVerifyUpdate (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_MD_CTX_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_get_digestbyobj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  cms_sd_asn1_ctrl (TYPE_3__*,int) ; 

int CMS_SignerInfo_verify(CMS_SignerInfo *si)
{
    EVP_MD_CTX *mctx = NULL;
    unsigned char *abuf = NULL;
    int alen, r = -1;
    const EVP_MD *md = NULL;

    if (!si->pkey) {
        CMSerr(CMS_F_CMS_SIGNERINFO_VERIFY, CMS_R_NO_PUBLIC_KEY);
        return -1;
    }

    if (!CMS_si_check_attributes(si))
        return -1;

    md = EVP_get_digestbyobj(si->digestAlgorithm->algorithm);
    if (md == NULL)
        return -1;
    if (si->mctx == NULL && (si->mctx = EVP_MD_CTX_new()) == NULL) {
        CMSerr(CMS_F_CMS_SIGNERINFO_VERIFY, ERR_R_MALLOC_FAILURE);
        return -1;
    }
    mctx = si->mctx;
    if (EVP_DigestVerifyInit(mctx, &si->pctx, md, NULL, si->pkey) <= 0)
        goto err;

    if (!cms_sd_asn1_ctrl(si, 1))
        goto err;

    alen = ASN1_item_i2d((ASN1_VALUE *)si->signedAttrs, &abuf,
                         ASN1_ITEM_rptr(CMS_Attributes_Verify));
    if (!abuf)
        goto err;
    r = EVP_DigestVerifyUpdate(mctx, abuf, alen);
    OPENSSL_free(abuf);
    if (r <= 0) {
        r = -1;
        goto err;
    }
    r = EVP_DigestVerifyFinal(mctx,
                              si->signature->data, si->signature->length);
    if (r <= 0)
        CMSerr(CMS_F_CMS_SIGNERINFO_VERIFY, CMS_R_VERIFICATION_FAILURE);
 err:
    EVP_MD_CTX_reset(mctx);
    return r;
}