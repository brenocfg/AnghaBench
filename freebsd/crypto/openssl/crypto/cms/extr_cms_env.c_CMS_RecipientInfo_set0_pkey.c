#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* ktri; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__ d; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pkey; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  TYPE_3__ CMS_RecipientInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_F_CMS_RECIPIENTINFO_SET0_PKEY ; 
 scalar_t__ CMS_RECIPINFO_TRANS ; 
 int /*<<< orphan*/  CMS_R_NOT_KEY_TRANSPORT ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 

int CMS_RecipientInfo_set0_pkey(CMS_RecipientInfo *ri, EVP_PKEY *pkey)
{
    if (ri->type != CMS_RECIPINFO_TRANS) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_SET0_PKEY, CMS_R_NOT_KEY_TRANSPORT);
        return 0;
    }
    EVP_PKEY_free(ri->d.ktri->pkey);
    ri->d.ktri->pkey = pkey;
    return 1;
}