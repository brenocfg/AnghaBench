#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int num; void const** data; int num_alloc; } ;
typedef  TYPE_1__ OPENSSL_STACK ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_F_SK_RESERVE ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 void** OPENSSL_realloc (void*,int) ; 
 void const** OPENSSL_zalloc (int) ; 
 int compute_growth (int,int) ; 
 int max_nodes ; 
 int min_nodes ; 

__attribute__((used)) static int sk_reserve(OPENSSL_STACK *st, int n, int exact)
{
    const void **tmpdata;
    int num_alloc;

    /* Check to see the reservation isn't exceeding the hard limit */
    if (n > max_nodes - st->num)
        return 0;

    /* Figure out the new size */
    num_alloc = st->num + n;
    if (num_alloc < min_nodes)
        num_alloc = min_nodes;

    /* If |st->data| allocation was postponed */
    if (st->data == NULL) {
        /*
         * At this point, |st->num_alloc| and |st->num| are 0;
         * so |num_alloc| value is |n| or |min_nodes| if greater than |n|.
         */
        if ((st->data = OPENSSL_zalloc(sizeof(void *) * num_alloc)) == NULL) {
            CRYPTOerr(CRYPTO_F_SK_RESERVE, ERR_R_MALLOC_FAILURE);
            return 0;
        }
        st->num_alloc = num_alloc;
        return 1;
    }

    if (!exact) {
        if (num_alloc <= st->num_alloc)
            return 1;
        num_alloc = compute_growth(num_alloc, st->num_alloc);
        if (num_alloc == 0)
            return 0;
    } else if (num_alloc == st->num_alloc) {
        return 1;
    }

    tmpdata = OPENSSL_realloc((void *)st->data, sizeof(void *) * num_alloc);
    if (tmpdata == NULL)
        return 0;

    st->data = tmpdata;
    st->num_alloc = num_alloc;
    return 1;
}