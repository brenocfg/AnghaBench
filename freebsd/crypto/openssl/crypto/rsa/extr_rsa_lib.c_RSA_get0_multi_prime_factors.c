#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  prime_infos; } ;
struct TYPE_6__ {int /*<<< orphan*/ * r; } ;
typedef  TYPE_1__ RSA_PRIME_INFO ;
typedef  TYPE_2__ RSA ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int RSA_get_multi_prime_extra_count (TYPE_2__ const*) ; 
 TYPE_1__* sk_RSA_PRIME_INFO_value (int /*<<< orphan*/ ,int) ; 

int RSA_get0_multi_prime_factors(const RSA *r, const BIGNUM *primes[])
{
    int pnum, i;
    RSA_PRIME_INFO *pinfo;

    if ((pnum = RSA_get_multi_prime_extra_count(r)) == 0)
        return 0;

    /*
     * return other primes
     * it's caller's responsibility to allocate oth_primes[pnum]
     */
    for (i = 0; i < pnum; i++) {
        pinfo = sk_RSA_PRIME_INFO_value(r->prime_infos, i);
        primes[i] = pinfo->r;
    }

    return 1;
}