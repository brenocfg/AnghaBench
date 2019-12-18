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
typedef  int /*<<< orphan*/  malloc_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 unsigned int PROF_NCTX_LOCKS ; 
 unsigned int atomic_fetch_add_u (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cum_gctxs ; 
 int /*<<< orphan*/ * gctx_locks ; 

malloc_mutex_t *
prof_gctx_mutex_choose(void) {
	unsigned ngctxs = atomic_fetch_add_u(&cum_gctxs, 1, ATOMIC_RELAXED);

	return &gctx_locks[(ngctxs - 1) % PROF_NCTX_LOCKS];
}