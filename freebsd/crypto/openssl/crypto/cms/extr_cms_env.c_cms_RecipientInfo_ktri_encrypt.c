#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* envelopedData; } ;
struct TYPE_18__ {TYPE_3__ d; } ;
struct TYPE_17__ {int /*<<< orphan*/  keylen; int /*<<< orphan*/  key; } ;
struct TYPE_16__ {int /*<<< orphan*/ * pctx; int /*<<< orphan*/  encryptedKey; int /*<<< orphan*/  pkey; } ;
struct TYPE_12__ {TYPE_5__* ktri; } ;
struct TYPE_15__ {scalar_t__ type; TYPE_1__ d; } ;
struct TYPE_13__ {TYPE_6__* encryptedContentInfo; } ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  TYPE_4__ CMS_RecipientInfo ;
typedef  TYPE_5__ CMS_KeyTransRecipientInfo ;
typedef  TYPE_6__ CMS_EncryptedContentInfo ;
typedef  TYPE_7__ CMS_ContentInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_set0 (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  CMS_F_CMS_RECIPIENTINFO_KTRI_ENCRYPT ; 
 scalar_t__ CMS_RECIPINFO_TRANS ; 
 int /*<<< orphan*/  CMS_R_CTRL_ERROR ; 
 int /*<<< orphan*/  CMS_R_NOT_KEY_TRANSPORT ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_PKEY_CTRL_CMS_ENCRYPT ; 
 scalar_t__ EVP_PKEY_CTX_ctrl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_OP_ENCRYPT ; 
 scalar_t__ EVP_PKEY_encrypt (int /*<<< orphan*/ *,unsigned char*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_PKEY_encrypt_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  cms_env_asn1_ctrl (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cms_RecipientInfo_ktri_encrypt(CMS_ContentInfo *cms,
                                          CMS_RecipientInfo *ri)
{
    CMS_KeyTransRecipientInfo *ktri;
    CMS_EncryptedContentInfo *ec;
    EVP_PKEY_CTX *pctx;
    unsigned char *ek = NULL;
    size_t eklen;

    int ret = 0;

    if (ri->type != CMS_RECIPINFO_TRANS) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_KTRI_ENCRYPT, CMS_R_NOT_KEY_TRANSPORT);
        return 0;
    }
    ktri = ri->d.ktri;
    ec = cms->d.envelopedData->encryptedContentInfo;

    pctx = ktri->pctx;

    if (pctx) {
        if (!cms_env_asn1_ctrl(ri, 0))
            goto err;
    } else {
        pctx = EVP_PKEY_CTX_new(ktri->pkey, NULL);
        if (pctx == NULL)
            return 0;

        if (EVP_PKEY_encrypt_init(pctx) <= 0)
            goto err;
    }

    if (EVP_PKEY_CTX_ctrl(pctx, -1, EVP_PKEY_OP_ENCRYPT,
                          EVP_PKEY_CTRL_CMS_ENCRYPT, 0, ri) <= 0) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_KTRI_ENCRYPT, CMS_R_CTRL_ERROR);
        goto err;
    }

    if (EVP_PKEY_encrypt(pctx, NULL, &eklen, ec->key, ec->keylen) <= 0)
        goto err;

    ek = OPENSSL_malloc(eklen);

    if (ek == NULL) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_KTRI_ENCRYPT, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    if (EVP_PKEY_encrypt(pctx, ek, &eklen, ec->key, ec->keylen) <= 0)
        goto err;

    ASN1_STRING_set0(ktri->encryptedKey, ek, eklen);
    ek = NULL;

    ret = 1;

 err:
    EVP_PKEY_CTX_free(pctx);
    ktri->pctx = NULL;
    OPENSSL_free(ek);
    return ret;

}