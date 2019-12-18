#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  key; } ;
struct drm_gem_object {int on_map; TYPE_1__ map_list; struct drm_device* dev; } ;
struct drm_gem_mm {int /*<<< orphan*/  idxunr; int /*<<< orphan*/  offset_hash; } ;
struct drm_device {struct drm_gem_mm* mm_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  alloc_unr (int /*<<< orphan*/ ) ; 
 int drm_ht_insert_item (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
drm_gem_create_mmap_offset(struct drm_gem_object *obj)
{
	struct drm_device *dev = obj->dev;
	struct drm_gem_mm *mm = dev->mm_private;
	int ret;

	if (obj->on_map)
		return 0;

	obj->map_list.key = alloc_unr(mm->idxunr);
	ret = drm_ht_insert_item(&mm->offset_hash, &obj->map_list);
	if (ret) {
		DRM_ERROR("failed to add to map hash\n");
		free_unr(mm->idxunr, obj->map_list.key);
		return ret;
	}
	obj->on_map = true;

	return 0;
}