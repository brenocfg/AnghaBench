#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* meth; } ;
struct TYPE_12__ {int /*<<< orphan*/  priv_key; int /*<<< orphan*/  pub_key; TYPE_8__* group; int /*<<< orphan*/  lock; int /*<<< orphan*/  ex_data; int /*<<< orphan*/  engine; TYPE_1__* meth; int /*<<< orphan*/  references; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* keyfinish ) (TYPE_3__*) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  (* finish ) (TYPE_3__*) ;} ;
typedef  TYPE_3__ EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_DOWN_REF (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_EX_INDEX_EC_KEY ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_free_ex_data (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_free (TYPE_8__*) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (void*,int) ; 
 int /*<<< orphan*/  REF_ASSERT_ISNT (int) ; 
 int /*<<< orphan*/  REF_PRINT_COUNT (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 

void EC_KEY_free(EC_KEY *r)
{
    int i;

    if (r == NULL)
        return;

    CRYPTO_DOWN_REF(&r->references, &i, r->lock);
    REF_PRINT_COUNT("EC_KEY", r);
    if (i > 0)
        return;
    REF_ASSERT_ISNT(i < 0);

    if (r->meth != NULL && r->meth->finish != NULL)
        r->meth->finish(r);

#ifndef OPENSSL_NO_ENGINE
    ENGINE_finish(r->engine);
#endif

    if (r->group && r->group->meth->keyfinish)
        r->group->meth->keyfinish(r);

    CRYPTO_free_ex_data(CRYPTO_EX_INDEX_EC_KEY, r, &r->ex_data);
    CRYPTO_THREAD_lock_free(r->lock);
    EC_GROUP_free(r->group);
    EC_POINT_free(r->pub_key);
    BN_clear_free(r->priv_key);

    OPENSSL_clear_free((void *)r, sizeof(EC_KEY));
}