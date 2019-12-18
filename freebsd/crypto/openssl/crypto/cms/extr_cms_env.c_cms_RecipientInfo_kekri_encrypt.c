#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  actx ;
struct TYPE_11__ {TYPE_1__* envelopedData; } ;
struct TYPE_16__ {TYPE_2__ d; } ;
struct TYPE_15__ {scalar_t__ keylen; int /*<<< orphan*/  key; } ;
struct TYPE_14__ {int keylen; int /*<<< orphan*/  encryptedKey; int /*<<< orphan*/  key; } ;
struct TYPE_12__ {TYPE_5__* kekri; } ;
struct TYPE_13__ {TYPE_3__ d; } ;
struct TYPE_10__ {TYPE_6__* encryptedContentInfo; } ;
typedef  TYPE_4__ CMS_RecipientInfo ;
typedef  TYPE_5__ CMS_KEKRecipientInfo ;
typedef  TYPE_6__ CMS_EncryptedContentInfo ;
typedef  TYPE_7__ CMS_ContentInfo ;
typedef  int /*<<< orphan*/  AES_KEY ;

/* Variables and functions */
 scalar_t__ AES_set_encrypt_key (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int AES_wrap_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ASN1_STRING_set0 (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  CMS_F_CMS_RECIPIENTINFO_KEKRI_ENCRYPT ; 
 int /*<<< orphan*/  CMS_R_ERROR_SETTING_KEY ; 
 int /*<<< orphan*/  CMS_R_NO_KEY ; 
 int /*<<< orphan*/  CMS_R_WRAP_ERROR ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_cleanse (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (scalar_t__) ; 

__attribute__((used)) static int cms_RecipientInfo_kekri_encrypt(CMS_ContentInfo *cms,
                                           CMS_RecipientInfo *ri)
{
    CMS_EncryptedContentInfo *ec;
    CMS_KEKRecipientInfo *kekri;
    AES_KEY actx;
    unsigned char *wkey = NULL;
    int wkeylen;
    int r = 0;

    ec = cms->d.envelopedData->encryptedContentInfo;

    kekri = ri->d.kekri;

    if (!kekri->key) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_KEKRI_ENCRYPT, CMS_R_NO_KEY);
        return 0;
    }

    if (AES_set_encrypt_key(kekri->key, kekri->keylen << 3, &actx)) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_KEKRI_ENCRYPT,
               CMS_R_ERROR_SETTING_KEY);
        goto err;
    }

    wkey = OPENSSL_malloc(ec->keylen + 8);

    if (wkey == NULL) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_KEKRI_ENCRYPT, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    wkeylen = AES_wrap_key(&actx, NULL, wkey, ec->key, ec->keylen);

    if (wkeylen <= 0) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_KEKRI_ENCRYPT, CMS_R_WRAP_ERROR);
        goto err;
    }

    ASN1_STRING_set0(kekri->encryptedKey, wkey, wkeylen);

    r = 1;

 err:

    if (!r)
        OPENSSL_free(wkey);
    OPENSSL_cleanse(&actx, sizeof(actx));

    return r;

}