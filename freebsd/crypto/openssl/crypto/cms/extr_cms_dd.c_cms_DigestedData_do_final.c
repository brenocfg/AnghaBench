#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  data; scalar_t__ length; } ;
struct TYPE_6__ {TYPE_2__* digestedData; } ;
struct TYPE_8__ {TYPE_1__ d; } ;
struct TYPE_7__ {TYPE_5__* digest; int /*<<< orphan*/  digestAlgorithm; } ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  TYPE_2__ CMS_DigestedData ;
typedef  TYPE_3__ CMS_ContentInfo ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_set (TYPE_5__*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  CMS_F_CMS_DIGESTEDDATA_DO_FINAL ; 
 int /*<<< orphan*/  CMS_R_MESSAGEDIGEST_WRONG_LENGTH ; 
 int /*<<< orphan*/  CMS_R_VERIFICATION_FAILURE ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,unsigned int*) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  cms_DigestAlgorithm_find_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 

int cms_DigestedData_do_final(CMS_ContentInfo *cms, BIO *chain, int verify)
{
    EVP_MD_CTX *mctx = EVP_MD_CTX_new();
    unsigned char md[EVP_MAX_MD_SIZE];
    unsigned int mdlen;
    int r = 0;
    CMS_DigestedData *dd;

    if (mctx == NULL) {
        CMSerr(CMS_F_CMS_DIGESTEDDATA_DO_FINAL, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    dd = cms->d.digestedData;

    if (!cms_DigestAlgorithm_find_ctx(mctx, chain, dd->digestAlgorithm))
        goto err;

    if (EVP_DigestFinal_ex(mctx, md, &mdlen) <= 0)
        goto err;

    if (verify) {
        if (mdlen != (unsigned int)dd->digest->length) {
            CMSerr(CMS_F_CMS_DIGESTEDDATA_DO_FINAL,
                   CMS_R_MESSAGEDIGEST_WRONG_LENGTH);
            goto err;
        }

        if (memcmp(md, dd->digest->data, mdlen))
            CMSerr(CMS_F_CMS_DIGESTEDDATA_DO_FINAL,
                   CMS_R_VERIFICATION_FAILURE);
        else
            r = 1;
    } else {
        if (!ASN1_STRING_set(dd->digest, md, mdlen))
            goto err;
        r = 1;
    }

 err:
    EVP_MD_CTX_free(mctx);

    return r;

}