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
struct ttm_range_manager {int /*<<< orphan*/  lock; int /*<<< orphan*/  mm; } ;
struct ttm_mem_type_manager {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mm_debug_table (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ttm_bo_man_debug(struct ttm_mem_type_manager *man,
			     const char *prefix)
{
	struct ttm_range_manager *rman = (struct ttm_range_manager *) man->priv;

	mtx_lock(&rman->lock);
	drm_mm_debug_table(&rman->mm, prefix);
	mtx_unlock(&rman->lock);
}