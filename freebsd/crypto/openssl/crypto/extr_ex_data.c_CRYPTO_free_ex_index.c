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
struct TYPE_6__ {int /*<<< orphan*/  free_func; int /*<<< orphan*/  dup_func; int /*<<< orphan*/  new_func; } ;
struct TYPE_5__ {int /*<<< orphan*/  meth; } ;
typedef  TYPE_1__ EX_CALLBACKS ;
typedef  TYPE_2__ EX_CALLBACK ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dummy_dup ; 
 int /*<<< orphan*/  dummy_free ; 
 int /*<<< orphan*/  dummy_new ; 
 int /*<<< orphan*/  ex_data_lock ; 
 TYPE_1__* get_and_lock (int) ; 
 int sk_EX_CALLBACK_num (int /*<<< orphan*/ ) ; 
 TYPE_2__* sk_EX_CALLBACK_value (int /*<<< orphan*/ ,int) ; 

int CRYPTO_free_ex_index(int class_index, int idx)
{
    EX_CALLBACKS *ip = get_and_lock(class_index);
    EX_CALLBACK *a;
    int toret = 0;

    if (ip == NULL)
        return 0;
    if (idx < 0 || idx >= sk_EX_CALLBACK_num(ip->meth))
        goto err;
    a = sk_EX_CALLBACK_value(ip->meth, idx);
    if (a == NULL)
        goto err;
    a->new_func = dummy_new;
    a->dup_func = dummy_dup;
    a->free_func = dummy_free;
    toret = 1;
err:
    CRYPTO_THREAD_unlock(ex_data_lock);
    return toret;
}