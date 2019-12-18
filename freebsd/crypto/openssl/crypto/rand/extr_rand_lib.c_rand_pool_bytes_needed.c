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
struct TYPE_5__ {size_t max_len; size_t len; scalar_t__ min_len; } ;
typedef  TYPE_1__ RAND_POOL ;

/* Variables and functions */
 size_t ENTROPY_TO_BYTES (size_t,unsigned int) ; 
 int /*<<< orphan*/  RAND_F_RAND_POOL_BYTES_NEEDED ; 
 int /*<<< orphan*/  RAND_R_ARGUMENT_OUT_OF_RANGE ; 
 int /*<<< orphan*/  RAND_R_RANDOM_POOL_OVERFLOW ; 
 int /*<<< orphan*/  RANDerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t rand_pool_entropy_needed (TYPE_1__*) ; 
 int /*<<< orphan*/  rand_pool_grow (TYPE_1__*,size_t) ; 

size_t rand_pool_bytes_needed(RAND_POOL *pool, unsigned int entropy_factor)
{
    size_t bytes_needed;
    size_t entropy_needed = rand_pool_entropy_needed(pool);

    if (entropy_factor < 1) {
        RANDerr(RAND_F_RAND_POOL_BYTES_NEEDED, RAND_R_ARGUMENT_OUT_OF_RANGE);
        return 0;
    }

    bytes_needed = ENTROPY_TO_BYTES(entropy_needed, entropy_factor);

    if (bytes_needed > pool->max_len - pool->len) {
        /* not enough space left */
        RANDerr(RAND_F_RAND_POOL_BYTES_NEEDED, RAND_R_RANDOM_POOL_OVERFLOW);
        return 0;
    }

    if (pool->len < pool->min_len &&
        bytes_needed < pool->min_len - pool->len)
        /* to meet the min_len requirement */
        bytes_needed = pool->min_len - pool->len;

    /*
     * Make sure the buffer is large enough for the requested amount
     * of data. This guarantees that existing code patterns where
     * rand_pool_add_begin, rand_pool_add_end or rand_pool_add
     * are used to collect entropy data without any error handling
     * whatsoever, continue to be valid.
     * Furthermore if the allocation here fails once, make sure that
     * we don't fall back to a less secure or even blocking random source,
     * as that could happen by the existing code patterns.
     * This is not a concern for additional data, therefore that
     * is not needed if rand_pool_grow fails in other places.
     */
    if (!rand_pool_grow(pool, bytes_needed)) {
        /* persistent error for this pool */
        pool->max_len = pool->len = 0;
        return 0;
    }

    return bytes_needed;
}