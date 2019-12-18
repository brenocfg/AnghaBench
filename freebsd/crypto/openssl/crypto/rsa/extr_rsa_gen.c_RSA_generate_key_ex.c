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
struct TYPE_7__ {TYPE_1__* meth; } ;
struct TYPE_6__ {int (* rsa_keygen ) (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ RSA ;
typedef  int /*<<< orphan*/  BN_GENCB ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  RSA_DEFAULT_PRIME_NUM ; 
 int RSA_generate_multi_prime_key (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int RSA_generate_key_ex(RSA *rsa, int bits, BIGNUM *e_value, BN_GENCB *cb)
{
    if (rsa->meth->rsa_keygen != NULL)
        return rsa->meth->rsa_keygen(rsa, bits, e_value, cb);

    return RSA_generate_multi_prime_key(rsa, bits, RSA_DEFAULT_PRIME_NUM,
                                        e_value, cb);
}