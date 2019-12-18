#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ type; } ;
struct TYPE_15__ {scalar_t__ type; } ;
struct TYPE_14__ {int version; int /*<<< orphan*/  signerInfos; TYPE_1__* encapContentInfo; int /*<<< orphan*/  crls; int /*<<< orphan*/  certificates; } ;
struct TYPE_13__ {int version; TYPE_2__* sid; } ;
struct TYPE_12__ {scalar_t__ type; } ;
struct TYPE_11__ {int /*<<< orphan*/  eContentType; } ;
typedef  TYPE_3__ CMS_SignerInfo ;
typedef  TYPE_4__ CMS_SignedData ;
typedef  TYPE_5__ CMS_RevocationInfoChoice ;
typedef  TYPE_6__ CMS_CertificateChoices ;

/* Variables and functions */
 scalar_t__ CMS_CERTCHOICE_OTHER ; 
 scalar_t__ CMS_CERTCHOICE_V1ACERT ; 
 scalar_t__ CMS_CERTCHOICE_V2ACERT ; 
 scalar_t__ CMS_REVCHOICE_OTHER ; 
 scalar_t__ CMS_SIGNERINFO_KEYIDENTIFIER ; 
 scalar_t__ NID_pkcs7_data ; 
 scalar_t__ OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int sk_CMS_CertificateChoices_num (int /*<<< orphan*/ ) ; 
 TYPE_6__* sk_CMS_CertificateChoices_value (int /*<<< orphan*/ ,int) ; 
 int sk_CMS_RevocationInfoChoice_num (int /*<<< orphan*/ ) ; 
 TYPE_5__* sk_CMS_RevocationInfoChoice_value (int /*<<< orphan*/ ,int) ; 
 int sk_CMS_SignerInfo_num (int /*<<< orphan*/ ) ; 
 TYPE_3__* sk_CMS_SignerInfo_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cms_sd_set_version(CMS_SignedData *sd)
{
    int i;
    CMS_CertificateChoices *cch;
    CMS_RevocationInfoChoice *rch;
    CMS_SignerInfo *si;

    for (i = 0; i < sk_CMS_CertificateChoices_num(sd->certificates); i++) {
        cch = sk_CMS_CertificateChoices_value(sd->certificates, i);
        if (cch->type == CMS_CERTCHOICE_OTHER) {
            if (sd->version < 5)
                sd->version = 5;
        } else if (cch->type == CMS_CERTCHOICE_V2ACERT) {
            if (sd->version < 4)
                sd->version = 4;
        } else if (cch->type == CMS_CERTCHOICE_V1ACERT) {
            if (sd->version < 3)
                sd->version = 3;
        }
    }

    for (i = 0; i < sk_CMS_RevocationInfoChoice_num(sd->crls); i++) {
        rch = sk_CMS_RevocationInfoChoice_value(sd->crls, i);
        if (rch->type == CMS_REVCHOICE_OTHER) {
            if (sd->version < 5)
                sd->version = 5;
        }
    }

    if ((OBJ_obj2nid(sd->encapContentInfo->eContentType) != NID_pkcs7_data)
        && (sd->version < 3))
        sd->version = 3;

    for (i = 0; i < sk_CMS_SignerInfo_num(sd->signerInfos); i++) {
        si = sk_CMS_SignerInfo_value(sd->signerInfos, i);
        if (si->sid->type == CMS_SIGNERINFO_KEYIDENTIFIER) {
            if (si->version < 3)
                si->version = 3;
            if (sd->version < 3)
                sd->version = 3;
        } else if (si->version < 1)
            si->version = 1;
    }

    if (sd->version < 1)
        sd->version = 1;

}