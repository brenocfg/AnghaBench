#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* ameth; } ;
struct TYPE_5__ {int (* pkey_ctrl ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
typedef  TYPE_2__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_PKEY_CTRL_CMS_RI_TYPE ; 
 int CMS_RECIPINFO_TRANS ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int cms_pkey_get_ri_type(EVP_PKEY *pk)
{
    if (pk->ameth && pk->ameth->pkey_ctrl) {
        int i, r;
        i = pk->ameth->pkey_ctrl(pk, ASN1_PKEY_CTRL_CMS_RI_TYPE, 0, &r);
        if (i > 0)
            return r;
    }
    return CMS_RECIPINFO_TRANS;
}