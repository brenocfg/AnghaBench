#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int blocksize; int w; int references; int /*<<< orphan*/ * lock; int /*<<< orphan*/  const* group; } ;
typedef  TYPE_1__ EC_PRE_COMP ;
typedef  int /*<<< orphan*/  EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/  EC_F_EC_PRE_COMP_NEW ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 

__attribute__((used)) static EC_PRE_COMP *ec_pre_comp_new(const EC_GROUP *group)
{
    EC_PRE_COMP *ret = NULL;

    if (!group)
        return NULL;

    ret = OPENSSL_zalloc(sizeof(*ret));
    if (ret == NULL) {
        ECerr(EC_F_EC_PRE_COMP_NEW, ERR_R_MALLOC_FAILURE);
        return ret;
    }

    ret->group = group;
    ret->blocksize = 8;         /* default */
    ret->w = 4;                 /* default */
    ret->references = 1;

    ret->lock = CRYPTO_THREAD_lock_new();
    if (ret->lock == NULL) {
        ECerr(EC_F_EC_PRE_COMP_NEW, ERR_R_MALLOC_FAILURE);
        OPENSSL_free(ret);
        return NULL;
    }
    return ret;
}