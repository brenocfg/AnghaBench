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
struct TYPE_4__ {size_t max_len; size_t len; unsigned char const* buffer; scalar_t__ alloc_len; size_t entropy; } ;
typedef  TYPE_1__ RAND_POOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  RAND_F_RAND_POOL_ADD ; 
 int /*<<< orphan*/  RAND_R_ENTROPY_INPUT_TOO_LONG ; 
 int /*<<< orphan*/  RANDerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char const*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  rand_pool_grow (TYPE_1__*,size_t) ; 

int rand_pool_add(RAND_POOL *pool,
                  const unsigned char *buffer, size_t len, size_t entropy)
{
    if (len > pool->max_len - pool->len) {
        RANDerr(RAND_F_RAND_POOL_ADD, RAND_R_ENTROPY_INPUT_TOO_LONG);
        return 0;
    }

    if (pool->buffer == NULL) {
        RANDerr(RAND_F_RAND_POOL_ADD, ERR_R_INTERNAL_ERROR);
        return 0;
    }

    if (len > 0) {
        /*
         * This is to protect us from accidentally passing the buffer
         * returned from rand_pool_add_begin.
         * The check for alloc_len makes sure we do not compare the
         * address of the end of the allocated memory to something
         * different, since that comparison would have an
         * indeterminate result.
         */
        if (pool->alloc_len > pool->len && pool->buffer + pool->len == buffer) {
            RANDerr(RAND_F_RAND_POOL_ADD, ERR_R_INTERNAL_ERROR);
            return 0;
        }
        /*
         * We have that only for cases when a pool is used to collect
         * additional data.
         * For entropy data, as long as the allocation request stays within
         * the limits given by rand_pool_bytes_needed this rand_pool_grow
         * below is guaranteed to succeed, thus no allocation happens.
         */
        if (!rand_pool_grow(pool, len))
            return 0;
        memcpy(pool->buffer + pool->len, buffer, len);
        pool->len += len;
        pool->entropy += entropy;
    }

    return 1;
}