#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mtx_pool {int mtx_pool_size; int mtx_pool_mask; int /*<<< orphan*/ * mtx_pool_ary; scalar_t__ mtx_pool_next; scalar_t__ mtx_pool_shift; } ;

/* Variables and functions */
 scalar_t__ POINTER_BITS ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
mtx_pool_initialize(struct mtx_pool *pool, const char *mtx_name, int pool_size,
    int opts)
{
	int i, maskbits;

	pool->mtx_pool_size = pool_size;
	pool->mtx_pool_mask = pool_size - 1;
	for (i = 1, maskbits = 0; (i & pool_size) == 0; i = i << 1)
		maskbits++;
	pool->mtx_pool_shift = POINTER_BITS - maskbits;
	pool->mtx_pool_next = 0;
	for (i = 0; i < pool_size; ++i)
		mtx_init(&pool->mtx_pool_ary[i], mtx_name, NULL, opts);
}