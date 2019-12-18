#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  jobs; } ;
typedef  TYPE_1__ async_pool ;

/* Variables and functions */
 scalar_t__ CRYPTO_THREAD_get_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_set_local (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  async_ctx_free () ; 
 int /*<<< orphan*/  async_empty_pool (TYPE_1__*) ; 
 int /*<<< orphan*/  async_local_cleanup () ; 
 int /*<<< orphan*/  poolkey ; 
 int /*<<< orphan*/  sk_ASYNC_JOB_free (int /*<<< orphan*/ ) ; 

void async_delete_thread_state(void)
{
    async_pool *pool = (async_pool *)CRYPTO_THREAD_get_local(&poolkey);

    if (pool != NULL) {
        async_empty_pool(pool);
        sk_ASYNC_JOB_free(pool->jobs);
        OPENSSL_free(pool);
        CRYPTO_THREAD_set_local(&poolkey, NULL);
    }
    async_local_cleanup();
    async_ctx_free();
}