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
struct TYPE_5__ {int num; int num_alloc; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ OPENSSL_STACK ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_F_OPENSSL_SK_DUP ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 void* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  OPENSSL_sk_free (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

OPENSSL_STACK *OPENSSL_sk_dup(const OPENSSL_STACK *sk)
{
    OPENSSL_STACK *ret;

    if ((ret = OPENSSL_malloc(sizeof(*ret))) == NULL) {
        CRYPTOerr(CRYPTO_F_OPENSSL_SK_DUP, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    /* direct structure assignment */
    *ret = *sk;

    if (sk->num == 0) {
        /* postpone |ret->data| allocation */
        ret->data = NULL;
        ret->num_alloc = 0;
        return ret;
    }
    /* duplicate |sk->data| content */
    if ((ret->data = OPENSSL_malloc(sizeof(*ret->data) * sk->num_alloc)) == NULL)
        goto err;
    memcpy(ret->data, sk->data, sizeof(void *) * sk->num);
    return ret;
 err:
    OPENSSL_sk_free(ret);
    return NULL;
}