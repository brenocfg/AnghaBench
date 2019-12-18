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
struct TYPE_6__ {TYPE_1__* meth; } ;
struct TYPE_5__ {int /*<<< orphan*/ * (* sign_sig ) (unsigned char const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,TYPE_2__*) ;} ;
typedef  TYPE_2__ EC_KEY ;
typedef  int /*<<< orphan*/  ECDSA_SIG ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_ECDSA_DO_SIGN_EX ; 
 int /*<<< orphan*/  EC_R_OPERATION_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (unsigned char const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,TYPE_2__*) ; 

ECDSA_SIG *ECDSA_do_sign_ex(const unsigned char *dgst, int dlen,
                            const BIGNUM *kinv, const BIGNUM *rp,
                            EC_KEY *eckey)
{
    if (eckey->meth->sign_sig != NULL)
        return eckey->meth->sign_sig(dgst, dlen, kinv, rp, eckey);
    ECerr(EC_F_ECDSA_DO_SIGN_EX, EC_R_OPERATION_NOT_SUPPORTED);
    return NULL;
}