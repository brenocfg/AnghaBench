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
struct drm_mm_node {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mm_insert_helper (struct drm_mm_node*,struct drm_mm_node*,unsigned long,unsigned int,unsigned long) ; 
 struct drm_mm_node* drm_mm_kmalloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

struct drm_mm_node *drm_mm_get_block_generic(struct drm_mm_node *hole_node,
					     unsigned long size,
					     unsigned alignment,
					     unsigned long color,
					     int atomic)
{
	struct drm_mm_node *node;

	node = drm_mm_kmalloc(hole_node->mm, atomic);
	if (unlikely(node == NULL))
		return NULL;

	drm_mm_insert_helper(hole_node, node, size, alignment, color);

	return node;
}