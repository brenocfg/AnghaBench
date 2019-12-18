#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_CRL ;
struct TYPE_4__ {int /*<<< orphan*/ * crl; } ;
struct TYPE_5__ {TYPE_1__ d; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ CMS_RevocationInfoChoice ;
typedef  int /*<<< orphan*/  CMS_ContentInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_REVCHOICE_CRL ; 
 TYPE_2__* CMS_add0_RevocationInfoChoice (int /*<<< orphan*/ *) ; 

int CMS_add0_crl(CMS_ContentInfo *cms, X509_CRL *crl)
{
    CMS_RevocationInfoChoice *rch;
    rch = CMS_add0_RevocationInfoChoice(cms);
    if (!rch)
        return 0;
    rch->type = CMS_REVCHOICE_CRL;
    rch->d.crl = crl;
    return 1;
}