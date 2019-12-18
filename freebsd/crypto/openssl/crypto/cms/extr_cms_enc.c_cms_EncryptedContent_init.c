#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t keylen; int /*<<< orphan*/  contentType; int /*<<< orphan*/ * key; int /*<<< orphan*/  const* cipher; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  TYPE_1__ CMS_EncryptedContentInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_F_CMS_ENCRYPTEDCONTENT_INIT ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  NID_pkcs7_data ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

int cms_EncryptedContent_init(CMS_EncryptedContentInfo *ec,
                              const EVP_CIPHER *cipher,
                              const unsigned char *key, size_t keylen)
{
    ec->cipher = cipher;
    if (key) {
        if ((ec->key = OPENSSL_malloc(keylen)) == NULL) {
            CMSerr(CMS_F_CMS_ENCRYPTEDCONTENT_INIT, ERR_R_MALLOC_FAILURE);
            return 0;
        }
        memcpy(ec->key, key, keylen);
    }
    ec->keylen = keylen;
    if (cipher)
        ec->contentType = OBJ_nid2obj(NID_pkcs7_data);
    return 1;
}