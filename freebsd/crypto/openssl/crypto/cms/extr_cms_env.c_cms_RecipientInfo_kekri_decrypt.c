#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  actx ;
struct TYPE_13__ {TYPE_1__* envelopedData; } ;
struct TYPE_20__ {TYPE_2__ d; } ;
struct TYPE_19__ {unsigned char* key; int keylen; } ;
struct TYPE_18__ {int keylen; TYPE_5__* encryptedKey; int /*<<< orphan*/  key; TYPE_4__* keyEncryptionAlgorithm; } ;
struct TYPE_14__ {TYPE_7__* kekri; } ;
struct TYPE_17__ {TYPE_3__ d; } ;
struct TYPE_16__ {int length; int /*<<< orphan*/  data; } ;
struct TYPE_15__ {int /*<<< orphan*/  algorithm; } ;
struct TYPE_12__ {TYPE_8__* encryptedContentInfo; } ;
typedef  TYPE_6__ CMS_RecipientInfo ;
typedef  TYPE_7__ CMS_KEKRecipientInfo ;
typedef  TYPE_8__ CMS_EncryptedContentInfo ;
typedef  TYPE_9__ CMS_ContentInfo ;
typedef  int /*<<< orphan*/  AES_KEY ;

/* Variables and functions */
 scalar_t__ AES_set_decrypt_key (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int AES_unwrap_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CMS_F_CMS_RECIPIENTINFO_KEKRI_DECRYPT ; 
 int /*<<< orphan*/  CMS_R_ERROR_SETTING_KEY ; 
 int /*<<< orphan*/  CMS_R_INVALID_ENCRYPTED_KEY_LENGTH ; 
 int /*<<< orphan*/  CMS_R_INVALID_KEY_LENGTH ; 
 int /*<<< orphan*/  CMS_R_NO_KEY ; 
 int /*<<< orphan*/  CMS_R_UNWRAP_ERROR ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int aes_wrap_keylen (int) ; 

__attribute__((used)) static int cms_RecipientInfo_kekri_decrypt(CMS_ContentInfo *cms,
                                           CMS_RecipientInfo *ri)
{
    CMS_EncryptedContentInfo *ec;
    CMS_KEKRecipientInfo *kekri;
    AES_KEY actx;
    unsigned char *ukey = NULL;
    int ukeylen;
    int r = 0, wrap_nid;

    ec = cms->d.envelopedData->encryptedContentInfo;

    kekri = ri->d.kekri;

    if (!kekri->key) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_KEKRI_DECRYPT, CMS_R_NO_KEY);
        return 0;
    }

    wrap_nid = OBJ_obj2nid(kekri->keyEncryptionAlgorithm->algorithm);
    if (aes_wrap_keylen(wrap_nid) != kekri->keylen) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_KEKRI_DECRYPT,
               CMS_R_INVALID_KEY_LENGTH);
        return 0;
    }

    /* If encrypted key length is invalid don't bother */

    if (kekri->encryptedKey->length < 16) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_KEKRI_DECRYPT,
               CMS_R_INVALID_ENCRYPTED_KEY_LENGTH);
        goto err;
    }

    if (AES_set_decrypt_key(kekri->key, kekri->keylen << 3, &actx)) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_KEKRI_DECRYPT,
               CMS_R_ERROR_SETTING_KEY);
        goto err;
    }

    ukey = OPENSSL_malloc(kekri->encryptedKey->length - 8);

    if (ukey == NULL) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_KEKRI_DECRYPT, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    ukeylen = AES_unwrap_key(&actx, NULL, ukey,
                             kekri->encryptedKey->data,
                             kekri->encryptedKey->length);

    if (ukeylen <= 0) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_KEKRI_DECRYPT, CMS_R_UNWRAP_ERROR);
        goto err;
    }

    ec->key = ukey;
    ec->keylen = ukeylen;

    r = 1;

 err:

    if (!r)
        OPENSSL_free(ukey);
    OPENSSL_cleanse(&actx, sizeof(actx));

    return r;

}