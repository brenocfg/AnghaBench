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
struct TYPE_6__ {int /*<<< orphan*/  comp; } ;
typedef  int /*<<< orphan*/  OPENSSL_sk_compfunc ;
typedef  TYPE_1__ OPENSSL_STACK ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_sk_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  sk_reserve (TYPE_1__*,int,int) ; 

OPENSSL_STACK *OPENSSL_sk_new_reserve(OPENSSL_sk_compfunc c, int n)
{
    OPENSSL_STACK *st = OPENSSL_zalloc(sizeof(OPENSSL_STACK));

    if (st == NULL)
        return NULL;

    st->comp = c;

    if (n <= 0)
        return st;

    if (!sk_reserve(st, n, 1)) {
        OPENSSL_sk_free(st);
        return NULL;
    }

    return st;
}