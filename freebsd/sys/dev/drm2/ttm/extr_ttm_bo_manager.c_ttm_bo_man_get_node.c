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
struct drm_mm {int dummy; } ;
struct ttm_range_manager {int /*<<< orphan*/  lock; struct drm_mm mm; } ;
struct ttm_placement {unsigned long lpfn; int /*<<< orphan*/  fpfn; } ;
struct ttm_mem_type_manager {unsigned long size; scalar_t__ priv; } ;
struct ttm_mem_reg {int /*<<< orphan*/  start; struct drm_mm_node* mm_node; int /*<<< orphan*/  page_alignment; int /*<<< orphan*/  num_pages; } ;
struct ttm_buffer_object {int dummy; } ;
struct drm_mm_node {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 struct drm_mm_node* drm_mm_get_block_atomic_range (struct drm_mm_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int drm_mm_pre_get (struct drm_mm*) ; 
 struct drm_mm_node* drm_mm_search_free_in_range (struct drm_mm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ttm_bo_man_get_node(struct ttm_mem_type_manager *man,
			       struct ttm_buffer_object *bo,
			       struct ttm_placement *placement,
			       struct ttm_mem_reg *mem)
{
	struct ttm_range_manager *rman = (struct ttm_range_manager *) man->priv;
	struct drm_mm *mm = &rman->mm;
	struct drm_mm_node *node = NULL;
	unsigned long lpfn;
	int ret;

	lpfn = placement->lpfn;
	if (!lpfn)
		lpfn = man->size;
	do {
		ret = drm_mm_pre_get(mm);
		if (unlikely(ret))
			return ret;

		mtx_lock(&rman->lock);
		node = drm_mm_search_free_in_range(mm,
					mem->num_pages, mem->page_alignment,
					placement->fpfn, lpfn, 1);
		if (unlikely(node == NULL)) {
			mtx_unlock(&rman->lock);
			return 0;
		}
		node = drm_mm_get_block_atomic_range(node, mem->num_pages,
						     mem->page_alignment,
						     placement->fpfn,
						     lpfn);
		mtx_unlock(&rman->lock);
	} while (node == NULL);

	mem->mm_node = node;
	mem->start = node->start;
	return 0;
}