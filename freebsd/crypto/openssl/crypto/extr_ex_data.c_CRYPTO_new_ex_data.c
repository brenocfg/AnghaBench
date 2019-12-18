#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/ * sk; } ;
struct TYPE_13__ {int /*<<< orphan*/  argp; int /*<<< orphan*/  argl; int /*<<< orphan*/  (* new_func ) (void*,void*,TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  meth; } ;
typedef  TYPE_1__ EX_CALLBACKS ;
typedef  TYPE_2__ EX_CALLBACK ;
typedef  TYPE_3__ CRYPTO_EX_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_F_CRYPTO_NEW_EX_DATA ; 
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 void* CRYPTO_get_ex_data (TYPE_3__*,int) ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__**) ; 
 TYPE_2__** OPENSSL_malloc (int) ; 
 scalar_t__ OSSL_NELEM (TYPE_2__**) ; 
 int /*<<< orphan*/  ex_data_lock ; 
 TYPE_1__* get_and_lock (int) ; 
 int sk_EX_CALLBACK_num (int /*<<< orphan*/ ) ; 
 TYPE_2__* sk_EX_CALLBACK_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (void*,void*,TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int CRYPTO_new_ex_data(int class_index, void *obj, CRYPTO_EX_DATA *ad)
{
    int mx, i;
    void *ptr;
    EX_CALLBACK **storage = NULL;
    EX_CALLBACK *stack[10];
    EX_CALLBACKS *ip = get_and_lock(class_index);

    if (ip == NULL)
        return 0;

    ad->sk = NULL;

    mx = sk_EX_CALLBACK_num(ip->meth);
    if (mx > 0) {
        if (mx < (int)OSSL_NELEM(stack))
            storage = stack;
        else
            storage = OPENSSL_malloc(sizeof(*storage) * mx);
        if (storage != NULL)
            for (i = 0; i < mx; i++)
                storage[i] = sk_EX_CALLBACK_value(ip->meth, i);
    }
    CRYPTO_THREAD_unlock(ex_data_lock);

    if (mx > 0 && storage == NULL) {
        CRYPTOerr(CRYPTO_F_CRYPTO_NEW_EX_DATA, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    for (i = 0; i < mx; i++) {
        if (storage[i] && storage[i]->new_func) {
            ptr = CRYPTO_get_ex_data(ad, i);
            storage[i]->new_func(obj, ptr, ad, i,
                                 storage[i]->argl, storage[i]->argp);
        }
    }
    if (storage != stack)
        OPENSSL_free(storage);
    return 1;
}