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
struct mtx_pool {uintptr_t mtx_pool_shift; uintptr_t mtx_pool_mask; struct mtx* mtx_pool_ary; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 uintptr_t HASH_MULTIPLIER ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 

struct mtx *
mtx_pool_find(struct mtx_pool *pool, void *ptr)
{
	int p;

	KASSERT(pool != NULL, ("_mtx_pool_find(): null pool"));
	/*
	 * Fibonacci hash, see Knuth's
	 * _Art of Computer Programming, Volume 3 / Sorting and Searching_
	 */
	p = ((HASH_MULTIPLIER * (uintptr_t)ptr) >> pool->mtx_pool_shift) &
	    pool->mtx_pool_mask;
	return (&pool->mtx_pool_ary[p]);
}