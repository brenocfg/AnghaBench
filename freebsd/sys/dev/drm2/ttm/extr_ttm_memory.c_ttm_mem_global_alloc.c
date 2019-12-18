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
typedef  int /*<<< orphan*/  uint64_t ;
struct ttm_mem_global {int dummy; } ;

/* Variables and functions */
 int ttm_mem_global_alloc_zone (struct ttm_mem_global*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

int ttm_mem_global_alloc(struct ttm_mem_global *glob, uint64_t memory,
			 bool no_wait, bool interruptible)
{
	/**
	 * Normal allocations of kernel memory are registered in
	 * all zones.
	 */

	return ttm_mem_global_alloc_zone(glob, NULL, memory, no_wait,
					 interruptible);
}