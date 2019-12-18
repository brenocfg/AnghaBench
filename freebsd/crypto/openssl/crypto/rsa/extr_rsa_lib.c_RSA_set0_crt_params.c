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
struct TYPE_3__ {int /*<<< orphan*/ * iqmp; int /*<<< orphan*/ * dmq1; int /*<<< orphan*/ * dmp1; } ;
typedef  TYPE_1__ RSA ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_FLG_CONSTTIME ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int RSA_set0_crt_params(RSA *r, BIGNUM *dmp1, BIGNUM *dmq1, BIGNUM *iqmp)
{
    /* If the fields dmp1, dmq1 and iqmp in r are NULL, the corresponding input
     * parameters MUST be non-NULL.
     */
    if ((r->dmp1 == NULL && dmp1 == NULL)
        || (r->dmq1 == NULL && dmq1 == NULL)
        || (r->iqmp == NULL && iqmp == NULL))
        return 0;

    if (dmp1 != NULL) {
        BN_clear_free(r->dmp1);
        r->dmp1 = dmp1;
        BN_set_flags(r->dmp1, BN_FLG_CONSTTIME);
    }
    if (dmq1 != NULL) {
        BN_clear_free(r->dmq1);
        r->dmq1 = dmq1;
        BN_set_flags(r->dmq1, BN_FLG_CONSTTIME);
    }
    if (iqmp != NULL) {
        BN_clear_free(r->iqmp);
        r->iqmp = iqmp;
        BN_set_flags(r->iqmp, BN_FLG_CONSTTIME);
    }

    return 1;
}