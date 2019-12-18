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
struct mtx_pool {int mtx_pool_next; int mtx_pool_mask; struct mtx* mtx_pool_ary; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 

struct mtx *
mtx_pool_alloc(struct mtx_pool *pool)
{
	int i;

	KASSERT(pool != NULL, ("mtx_pool_alloc(): null pool"));
	/*
	 * mtx_pool_next is unprotected against multiple accesses,
	 * but simultaneous access by two CPUs should not be very
	 * harmful.
	 */
	i = pool->mtx_pool_next;
	pool->mtx_pool_next = (i + 1) & pool->mtx_pool_mask;
	return (&pool->mtx_pool_ary[i]);
}