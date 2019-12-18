#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* kari; TYPE_1__* ktri; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_3__ d; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pctx; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pctx; } ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  TYPE_4__ CMS_RecipientInfo ;

/* Variables and functions */
 scalar_t__ CMS_RECIPINFO_AGREE ; 
 scalar_t__ CMS_RECIPINFO_TRANS ; 

EVP_PKEY_CTX *CMS_RecipientInfo_get0_pkey_ctx(CMS_RecipientInfo *ri)
{
    if (ri->type == CMS_RECIPINFO_TRANS)
        return ri->d.ktri->pctx;
    else if (ri->type == CMS_RECIPINFO_AGREE)
        return ri->d.kari->pctx;
    return NULL;
}