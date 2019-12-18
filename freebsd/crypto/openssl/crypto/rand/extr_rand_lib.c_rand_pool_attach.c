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
struct TYPE_4__ {unsigned char* buffer; size_t len; int attached; size_t min_len; size_t max_len; size_t alloc_len; size_t entropy; } ;
typedef  TYPE_1__ RAND_POOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  RAND_F_RAND_POOL_ATTACH ; 
 int /*<<< orphan*/  RANDerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

RAND_POOL *rand_pool_attach(const unsigned char *buffer, size_t len,
                            size_t entropy)
{
    RAND_POOL *pool = OPENSSL_zalloc(sizeof(*pool));

    if (pool == NULL) {
        RANDerr(RAND_F_RAND_POOL_ATTACH, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    /*
     * The const needs to be cast away, but attached buffers will not be
     * modified (in contrary to allocated buffers which are zeroed and
     * freed in the end).
     */
    pool->buffer = (unsigned char *) buffer;
    pool->len = len;

    pool->attached = 1;

    pool->min_len = pool->max_len = pool->alloc_len = pool->len;
    pool->entropy = entropy;

    return pool;
}