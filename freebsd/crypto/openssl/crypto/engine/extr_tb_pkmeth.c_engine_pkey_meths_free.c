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
struct TYPE_5__ {int (* pkey_meths ) (TYPE_1__*,int /*<<< orphan*/ **,int const**,int const) ;} ;
typedef  int /*<<< orphan*/  EVP_PKEY_METHOD ;
typedef  TYPE_1__ ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_meth_free (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ **,int const**,int const) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ **,int const**,int const) ; 

void engine_pkey_meths_free(ENGINE *e)
{
    int i;
    EVP_PKEY_METHOD *pkm;
    if (e->pkey_meths) {
        const int *pknids;
        int npknids;
        npknids = e->pkey_meths(e, NULL, &pknids, 0);
        for (i = 0; i < npknids; i++) {
            if (e->pkey_meths(e, &pkm, NULL, pknids[i])) {
                EVP_PKEY_meth_free(pkm);
            }
        }
    }
}