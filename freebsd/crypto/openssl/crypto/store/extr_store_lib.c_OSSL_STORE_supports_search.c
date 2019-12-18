#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* loader; } ;
struct TYPE_7__ {int search_type; } ;
struct TYPE_6__ {int (* find ) (int /*<<< orphan*/ *,TYPE_2__*) ;} ;
typedef  TYPE_2__ OSSL_STORE_SEARCH ;
typedef  TYPE_3__ OSSL_STORE_CTX ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,TYPE_2__*) ; 

int OSSL_STORE_supports_search(OSSL_STORE_CTX *ctx, int search_type)
{
    OSSL_STORE_SEARCH tmp_search;

    if (ctx->loader->find == NULL)
        return 0;
    tmp_search.search_type = search_type;
    return ctx->loader->find(NULL, &tmp_search);
}