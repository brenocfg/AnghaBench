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
struct TYPE_3__ {int /*<<< orphan*/  encryptedContentInfo; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  TYPE_1__ CMS_EnvelopedData ;
typedef  int /*<<< orphan*/  CMS_ContentInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_ContentInfo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CMS_ContentInfo_new () ; 
 int /*<<< orphan*/  CMS_F_CMS_ENVELOPEDDATA_CREATE ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  cms_EncryptedContent_init (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* cms_enveloped_data_init (int /*<<< orphan*/ *) ; 

CMS_ContentInfo *CMS_EnvelopedData_create(const EVP_CIPHER *cipher)
{
    CMS_ContentInfo *cms;
    CMS_EnvelopedData *env;
    cms = CMS_ContentInfo_new();
    if (cms == NULL)
        goto merr;
    env = cms_enveloped_data_init(cms);
    if (env == NULL)
        goto merr;
    if (!cms_EncryptedContent_init(env->encryptedContentInfo,
                                   cipher, NULL, 0))
        goto merr;
    return cms;
 merr:
    CMS_ContentInfo_free(cms);
    CMSerr(CMS_F_CMS_ENVELOPEDDATA_CREATE, ERR_R_MALLOC_FAILURE);
    return NULL;
}