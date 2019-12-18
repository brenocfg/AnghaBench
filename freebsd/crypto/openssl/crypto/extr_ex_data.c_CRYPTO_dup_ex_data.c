#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/ * sk; } ;
struct TYPE_16__ {int /*<<< orphan*/  argp; int /*<<< orphan*/  argl; int /*<<< orphan*/  (* dup_func ) (TYPE_3__ const*,TYPE_3__ const*,void**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  meth; } ;
typedef  TYPE_1__ EX_CALLBACKS ;
typedef  TYPE_2__ EX_CALLBACK ;
typedef  TYPE_3__ const CRYPTO_EX_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_F_CRYPTO_DUP_EX_DATA ; 
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 void* CRYPTO_get_ex_data (TYPE_3__ const*,int) ; 
 int /*<<< orphan*/  CRYPTO_set_ex_data (TYPE_3__ const*,int,void*) ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__**) ; 
 TYPE_2__** OPENSSL_malloc (int) ; 
 scalar_t__ OSSL_NELEM (TYPE_2__**) ; 
 int /*<<< orphan*/  ex_data_lock ; 
 TYPE_1__* get_and_lock (int) ; 
 int sk_EX_CALLBACK_num (int /*<<< orphan*/ ) ; 
 TYPE_2__* sk_EX_CALLBACK_value (int /*<<< orphan*/ ,int) ; 
 int sk_void_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__ const*,TYPE_3__ const*,void**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int CRYPTO_dup_ex_data(int class_index, CRYPTO_EX_DATA *to,
                       const CRYPTO_EX_DATA *from)
{
    int mx, j, i;
    void *ptr;
    EX_CALLBACK *stack[10];
    EX_CALLBACK **storage = NULL;
    EX_CALLBACKS *ip;
    int toret = 0;

    if (from->sk == NULL)
        /* Nothing to copy over */
        return 1;
    if ((ip = get_and_lock(class_index)) == NULL)
        return 0;

    mx = sk_EX_CALLBACK_num(ip->meth);
    j = sk_void_num(from->sk);
    if (j < mx)
        mx = j;
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

    if (mx == 0)
        return 1;
    if (storage == NULL) {
        CRYPTOerr(CRYPTO_F_CRYPTO_DUP_EX_DATA, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    /*
     * Make sure the ex_data stack is at least |mx| elements long to avoid
     * issues in the for loop that follows; so go get the |mx|'th element
     * (if it does not exist CRYPTO_get_ex_data() returns NULL), and assign
     * to itself. This is normally a no-op; but ensures the stack is the
     * proper size
     */
    if (!CRYPTO_set_ex_data(to, mx - 1, CRYPTO_get_ex_data(to, mx - 1)))
        goto err;

    for (i = 0; i < mx; i++) {
        ptr = CRYPTO_get_ex_data(from, i);
        if (storage[i] && storage[i]->dup_func)
            if (!storage[i]->dup_func(to, from, &ptr, i,
                                      storage[i]->argl, storage[i]->argp))
                goto err;
        CRYPTO_set_ex_data(to, i, ptr);
    }
    toret = 1;
 err:
    if (storage != stack)
        OPENSSL_free(storage);
    return toret;
}