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
struct TYPE_3__ {int /*<<< orphan*/ * g; int /*<<< orphan*/ * q; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ DSA ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 

int DSA_set0_pqg(DSA *d, BIGNUM *p, BIGNUM *q, BIGNUM *g)
{
    /* If the fields p, q and g in d are NULL, the corresponding input
     * parameters MUST be non-NULL.
     */
    if ((d->p == NULL && p == NULL)
        || (d->q == NULL && q == NULL)
        || (d->g == NULL && g == NULL))
        return 0;

    if (p != NULL) {
        BN_free(d->p);
        d->p = p;
    }
    if (q != NULL) {
        BN_free(d->q);
        d->q = q;
    }
    if (g != NULL) {
        BN_free(d->g);
        d->g = g;
    }

    return 1;
}