#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  int /*<<< orphan*/  CMS_ContentInfo ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_ContentInfo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CMS_ContentInfo_new () ; 
 unsigned int CMS_DETACHED ; 
 int /*<<< orphan*/  CMS_EncryptedData_set1_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  CMS_F_CMS_ENCRYPTEDDATA_ENCRYPT ; 
 unsigned int CMS_PARTIAL ; 
 int /*<<< orphan*/  CMS_R_NO_CIPHER ; 
 unsigned int CMS_STREAM ; 
 scalar_t__ CMS_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  CMS_set_detached (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

CMS_ContentInfo *CMS_EncryptedData_encrypt(BIO *in, const EVP_CIPHER *cipher,
                                           const unsigned char *key,
                                           size_t keylen, unsigned int flags)
{
    CMS_ContentInfo *cms;
    if (!cipher) {
        CMSerr(CMS_F_CMS_ENCRYPTEDDATA_ENCRYPT, CMS_R_NO_CIPHER);
        return NULL;
    }
    cms = CMS_ContentInfo_new();
    if (cms == NULL)
        return NULL;
    if (!CMS_EncryptedData_set1_key(cms, cipher, key, keylen))
        return NULL;

    if (!(flags & CMS_DETACHED))
        CMS_set_detached(cms, 0);

    if ((flags & (CMS_STREAM | CMS_PARTIAL))
        || CMS_final(cms, in, NULL, flags))
        return cms;

    CMS_ContentInfo_free(cms);
    return NULL;
}