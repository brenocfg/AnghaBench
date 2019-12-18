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
struct drm_device {int /*<<< orphan*/ * ctx_bitmap; int /*<<< orphan*/ * context_sareas; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_LOCK (struct drm_device*) ; 
 int /*<<< orphan*/  DRM_MEM_CTXBITMAP ; 
 int /*<<< orphan*/  DRM_MEM_SAREA ; 
 int /*<<< orphan*/  DRM_UNLOCK (struct drm_device*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void drm_ctxbitmap_cleanup(struct drm_device * dev)
{
	DRM_LOCK(dev);
	if (dev->context_sareas != NULL)
		free(dev->context_sareas, DRM_MEM_SAREA);
	free(dev->ctx_bitmap, DRM_MEM_CTXBITMAP);
	DRM_UNLOCK(dev);
}