#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  revoked; } ;
typedef  TYPE_1__ X509_CRL_INFO ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
#define  ASN1_OP_D2I_POST 128 
 int /*<<< orphan*/  X509_REVOKED_cmp ; 
 int /*<<< orphan*/  sk_X509_REVOKED_set_cmp_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crl_inf_cb(int operation, ASN1_VALUE **pval, const ASN1_ITEM *it,
                      void *exarg)
{
    X509_CRL_INFO *a = (X509_CRL_INFO *)*pval;

    if (!a || !a->revoked)
        return 1;
    switch (operation) {
        /*
         * Just set cmp function here. We don't sort because that would
         * affect the output of X509_CRL_print().
         */
    case ASN1_OP_D2I_POST:
        (void)sk_X509_REVOKED_set_cmp_func(a->revoked, X509_REVOKED_cmp);
        break;
    }
    return 1;
}