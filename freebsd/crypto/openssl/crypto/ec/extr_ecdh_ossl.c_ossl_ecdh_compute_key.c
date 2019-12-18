#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* group; } ;
struct TYPE_7__ {TYPE_1__* meth; } ;
struct TYPE_6__ {int (* ecdh_compute_key ) (unsigned char**,size_t*,int /*<<< orphan*/  const*,TYPE_3__ const*) ;} ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  TYPE_3__ EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_OSSL_ECDH_COMPUTE_KEY ; 
 int /*<<< orphan*/  EC_R_CURVE_DOES_NOT_SUPPORT_ECDH ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (unsigned char**,size_t*,int /*<<< orphan*/  const*,TYPE_3__ const*) ; 

int ossl_ecdh_compute_key(unsigned char **psec, size_t *pseclen,
                          const EC_POINT *pub_key, const EC_KEY *ecdh)
{
    if (ecdh->group->meth->ecdh_compute_key == NULL) {
        ECerr(EC_F_OSSL_ECDH_COMPUTE_KEY, EC_R_CURVE_DOES_NOT_SUPPORT_ECDH);
        return 0;
    }

    return ecdh->group->meth->ecdh_compute_key(psec, pseclen, pub_key, ecdh);
}