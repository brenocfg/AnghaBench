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
typedef  scalar_t__ ossl_ssize_t ;
struct TYPE_7__ {unsigned char* pass; scalar_t__ passlen; } ;
struct TYPE_5__ {TYPE_3__* pwri; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ d; } ;
typedef  TYPE_2__ CMS_RecipientInfo ;
typedef  TYPE_3__ CMS_PasswordRecipientInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_F_CMS_RECIPIENTINFO_SET0_PASSWORD ; 
 scalar_t__ CMS_RECIPINFO_PASS ; 
 int /*<<< orphan*/  CMS_R_NOT_PWRI ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

int CMS_RecipientInfo_set0_password(CMS_RecipientInfo *ri,
                                    unsigned char *pass, ossl_ssize_t passlen)
{
    CMS_PasswordRecipientInfo *pwri;
    if (ri->type != CMS_RECIPINFO_PASS) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_SET0_PASSWORD, CMS_R_NOT_PWRI);
        return 0;
    }

    pwri = ri->d.pwri;
    pwri->pass = pass;
    if (pass && passlen < 0)
        passlen = strlen((char *)pass);
    pwri->passlen = passlen;
    return 1;
}