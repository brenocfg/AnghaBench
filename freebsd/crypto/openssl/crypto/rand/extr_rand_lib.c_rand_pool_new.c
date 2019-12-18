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
struct TYPE_4__ {size_t min_len; size_t max_len; size_t alloc_len; int entropy_requested; int secure; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ RAND_POOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/ * OPENSSL_secure_zalloc (size_t) ; 
 void* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  RAND_F_RAND_POOL_NEW ; 
 size_t RAND_POOL_MAX_LENGTH ; 
 size_t RAND_POOL_MIN_ALLOCATION (int) ; 
 int /*<<< orphan*/  RANDerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

RAND_POOL *rand_pool_new(int entropy_requested, int secure,
                         size_t min_len, size_t max_len)
{
    RAND_POOL *pool = OPENSSL_zalloc(sizeof(*pool));
    size_t min_alloc_size = RAND_POOL_MIN_ALLOCATION(secure);

    if (pool == NULL) {
        RANDerr(RAND_F_RAND_POOL_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    pool->min_len = min_len;
    pool->max_len = (max_len > RAND_POOL_MAX_LENGTH) ?
        RAND_POOL_MAX_LENGTH : max_len;
    pool->alloc_len = min_len < min_alloc_size ? min_alloc_size : min_len;
    if (pool->alloc_len > pool->max_len)
        pool->alloc_len = pool->max_len;

    if (secure)
        pool->buffer = OPENSSL_secure_zalloc(pool->alloc_len);
    else
        pool->buffer = OPENSSL_zalloc(pool->alloc_len);

    if (pool->buffer == NULL) {
        RANDerr(RAND_F_RAND_POOL_NEW, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    pool->entropy_requested = entropy_requested;
    pool->secure = secure;

    return pool;

err:
    OPENSSL_free(pool);
    return NULL;
}