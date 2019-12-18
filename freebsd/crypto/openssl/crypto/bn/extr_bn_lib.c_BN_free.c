#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; } ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int BN_FLG_MALLOCED ; 
 int /*<<< orphan*/  BN_FLG_STATIC_DATA ; 
 int /*<<< orphan*/  BN_get_flags (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  bn_free_d (TYPE_1__*,int /*<<< orphan*/ ) ; 

void BN_free(BIGNUM *a)
{
    if (a == NULL)
        return;
    if (!BN_get_flags(a, BN_FLG_STATIC_DATA))
        bn_free_d(a, 0);
    if (a->flags & BN_FLG_MALLOCED)
        OPENSSL_free(a);
}