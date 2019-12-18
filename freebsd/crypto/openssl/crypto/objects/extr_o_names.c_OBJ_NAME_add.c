#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* free_func ) (char const*,scalar_t__,char const*) ;} ;
struct TYPE_7__ {char const* name; int alias; int type; char const* data; } ;
typedef  TYPE_1__ OBJ_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int OBJ_NAME_ALIAS ; 
 int /*<<< orphan*/  OBJ_NAME_init () ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_malloc (int) ; 
 scalar_t__ lh_OBJ_NAME_error (int /*<<< orphan*/ ) ; 
 TYPE_1__* lh_OBJ_NAME_insert (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * name_funcs_stack ; 
 int /*<<< orphan*/  names_lh ; 
 int /*<<< orphan*/  obj_lock ; 
 scalar_t__ sk_NAME_FUNCS_num (int /*<<< orphan*/ *) ; 
 TYPE_2__* sk_NAME_FUNCS_value (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (char const*,scalar_t__,char const*) ; 

int OBJ_NAME_add(const char *name, int type, const char *data)
{
    OBJ_NAME *onp, *ret;
    int alias, ok = 0;

    if (!OBJ_NAME_init())
        return 0;

    alias = type & OBJ_NAME_ALIAS;
    type &= ~OBJ_NAME_ALIAS;

    onp = OPENSSL_malloc(sizeof(*onp));
    if (onp == NULL) {
        /* ERROR */
        goto unlock;
    }

    onp->name = name;
    onp->alias = alias;
    onp->type = type;
    onp->data = data;

    CRYPTO_THREAD_write_lock(obj_lock);

    ret = lh_OBJ_NAME_insert(names_lh, onp);
    if (ret != NULL) {
        /* free things */
        if ((name_funcs_stack != NULL)
            && (sk_NAME_FUNCS_num(name_funcs_stack) > ret->type)) {
            /*
             * XXX: I'm not sure I understand why the free function should
             * get three arguments... -- Richard Levitte
             */
            sk_NAME_FUNCS_value(name_funcs_stack,
                                ret->type)->free_func(ret->name, ret->type,
                                                      ret->data);
        }
        OPENSSL_free(ret);
    } else {
        if (lh_OBJ_NAME_error(names_lh)) {
            /* ERROR */
            OPENSSL_free(onp);
            goto unlock;
        }
    }

    ok = 1;

unlock:
    CRYPTO_THREAD_unlock(obj_lock);
    return ok;
}