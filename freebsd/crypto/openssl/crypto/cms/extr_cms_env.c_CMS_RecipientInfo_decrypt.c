#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int type; } ;
typedef  TYPE_1__ CMS_RecipientInfo ;
typedef  int /*<<< orphan*/  CMS_ContentInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_F_CMS_RECIPIENTINFO_DECRYPT ; 
#define  CMS_RECIPINFO_KEK 130 
#define  CMS_RECIPINFO_PASS 129 
#define  CMS_RECIPINFO_TRANS 128 
 int /*<<< orphan*/  CMS_R_UNSUPPORTED_RECIPIENTINFO_TYPE ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cms_RecipientInfo_kekri_decrypt (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int cms_RecipientInfo_ktri_decrypt (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int cms_RecipientInfo_pwri_crypt (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

int CMS_RecipientInfo_decrypt(CMS_ContentInfo *cms, CMS_RecipientInfo *ri)
{
    switch (ri->type) {
    case CMS_RECIPINFO_TRANS:
        return cms_RecipientInfo_ktri_decrypt(cms, ri);

    case CMS_RECIPINFO_KEK:
        return cms_RecipientInfo_kekri_decrypt(cms, ri);

    case CMS_RECIPINFO_PASS:
        return cms_RecipientInfo_pwri_crypt(cms, ri, 0);

    default:
        CMSerr(CMS_F_CMS_RECIPIENTINFO_DECRYPT,
               CMS_R_UNSUPPORTED_RECIPIENTINFO_TYPE);
        return 0;
    }
}