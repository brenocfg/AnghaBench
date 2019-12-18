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
struct drm_mm_node {int /*<<< orphan*/  node_list; } ;
struct drm_mm {int num_unused; int /*<<< orphan*/  unused_lock; int /*<<< orphan*/  unused_nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MEM_MM ; 
 int ENOMEM ; 
 int MM_UNUSED_TARGET ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct drm_mm_node* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int drm_mm_pre_get(struct drm_mm *mm)
{
	struct drm_mm_node *node;

	mtx_lock(&mm->unused_lock);
	while (mm->num_unused < MM_UNUSED_TARGET) {
		mtx_unlock(&mm->unused_lock);
		node = malloc(sizeof(*node), DRM_MEM_MM, M_NOWAIT | M_ZERO);
		mtx_lock(&mm->unused_lock);

		if (unlikely(node == NULL)) {
			int ret = (mm->num_unused < 2) ? -ENOMEM : 0;
			mtx_unlock(&mm->unused_lock);
			return ret;
		}
		++mm->num_unused;
		list_add_tail(&node->node_list, &mm->unused_nodes);
	}
	mtx_unlock(&mm->unused_lock);
	return 0;
}