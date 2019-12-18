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
typedef  int /*<<< orphan*/  X509_CRL ;
typedef  int /*<<< orphan*/  CMS_ContentInfo ;

/* Variables and functions */
 int CMS_add0_crl (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_CRL_up_ref (int /*<<< orphan*/ *) ; 

int CMS_add1_crl(CMS_ContentInfo *cms, X509_CRL *crl)
{
    int r;
    r = CMS_add0_crl(cms, crl);
    if (r > 0)
        X509_CRL_up_ref(crl);
    return r;
}