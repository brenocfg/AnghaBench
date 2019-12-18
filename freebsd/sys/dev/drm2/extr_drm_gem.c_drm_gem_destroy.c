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
struct drm_gem_mm {int /*<<< orphan*/  idxunr; int /*<<< orphan*/  offset_hash; } ;
struct drm_device {int /*<<< orphan*/  object_names; struct drm_gem_mm* mm_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MEM_DRIVER ; 
 int /*<<< orphan*/  delete_unrhdr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_names_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_ht_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct drm_gem_mm*,int /*<<< orphan*/ ) ; 

void
drm_gem_destroy(struct drm_device *dev)
{
	struct drm_gem_mm *mm = dev->mm_private;

	dev->mm_private = NULL;
	drm_ht_remove(&mm->offset_hash);
	delete_unrhdr(mm->idxunr);
	free(mm, DRM_MEM_DRIVER);
	drm_gem_names_fini(&dev->object_names);
}