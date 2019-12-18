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
struct drm_device {struct drm_gem_mm* mm_private; int /*<<< orphan*/  object_names; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_GEM_MAX_IDX ; 
 int /*<<< orphan*/  DRM_MEM_DRIVER ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  drm_gem_names_init (int /*<<< orphan*/ *) ; 
 scalar_t__ drm_ht_create (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (struct drm_gem_mm*,int /*<<< orphan*/ ) ; 
 struct drm_gem_mm* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_unrhdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
drm_gem_init(struct drm_device *dev)
{
	struct drm_gem_mm *mm;

	drm_gem_names_init(&dev->object_names);

	mm = malloc(sizeof(*mm), DRM_MEM_DRIVER, M_NOWAIT);
	if (!mm) {
		DRM_ERROR("out of memory\n");
		return -ENOMEM;
	}

	dev->mm_private = mm;

	if (drm_ht_create(&mm->offset_hash, 19)) {
		free(mm, DRM_MEM_DRIVER);
		return -ENOMEM;
	}

	mm->idxunr = new_unrhdr(0, DRM_GEM_MAX_IDX, NULL);

	return 0;
}