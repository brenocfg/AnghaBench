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
struct TYPE_6__ {unsigned long (* hash ) (void const*) ;unsigned long pmax; unsigned long p; unsigned long num_alloc_nodes; scalar_t__ (* comp ) (int /*<<< orphan*/ ,void const*) ;int /*<<< orphan*/  num_comp_calls; int /*<<< orphan*/  num_hash_comps; TYPE_1__** b; int /*<<< orphan*/  num_hash_calls; } ;
struct TYPE_5__ {unsigned long hash; struct TYPE_5__* next; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ OPENSSL_LH_NODE ;
typedef  scalar_t__ (* OPENSSL_LH_COMPFUNC ) (int /*<<< orphan*/ ,void const*) ;
typedef  TYPE_2__ OPENSSL_LHASH ;

/* Variables and functions */
 unsigned long stub1 (void const*) ; 
 int /*<<< orphan*/  tsan_counter (int /*<<< orphan*/ *) ; 

__attribute__((used)) static OPENSSL_LH_NODE **getrn(OPENSSL_LHASH *lh,
                               const void *data, unsigned long *rhash)
{
    OPENSSL_LH_NODE **ret, *n1;
    unsigned long hash, nn;
    OPENSSL_LH_COMPFUNC cf;

    hash = (*(lh->hash)) (data);
    tsan_counter(&lh->num_hash_calls);
    *rhash = hash;

    nn = hash % lh->pmax;
    if (nn < lh->p)
        nn = hash % lh->num_alloc_nodes;

    cf = lh->comp;
    ret = &(lh->b[(int)nn]);
    for (n1 = *ret; n1 != NULL; n1 = n1->next) {
        tsan_counter(&lh->num_hash_comps);
        if (n1->hash != hash) {
            ret = &(n1->next);
            continue;
        }
        tsan_counter(&lh->num_comp_calls);
        if (cf(n1->data, data) == 0)
            break;
        ret = &(n1->next);
    }
    return ret;
}