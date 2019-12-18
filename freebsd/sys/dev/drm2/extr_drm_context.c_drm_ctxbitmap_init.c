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
struct drm_device {int max_context; int /*<<< orphan*/ * context_sareas; int /*<<< orphan*/ * ctx_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int /*<<< orphan*/  DRM_LOCK (struct drm_device*) ; 
 int /*<<< orphan*/  DRM_MEM_CTXBITMAP ; 
 int DRM_RESERVED_CONTEXTS ; 
 int /*<<< orphan*/  DRM_UNLOCK (struct drm_device*) ; 
 int ENOMEM ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int drm_ctxbitmap_next (struct drm_device*) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int drm_ctxbitmap_init(struct drm_device * dev)
{
	int i;
   	int temp;

	DRM_LOCK(dev);
	dev->ctx_bitmap = malloc(PAGE_SIZE, DRM_MEM_CTXBITMAP,
	    M_NOWAIT | M_ZERO);
	if (dev->ctx_bitmap == NULL) {
		DRM_UNLOCK(dev);
		return ENOMEM;
	}
	dev->context_sareas = NULL;
	dev->max_context = -1;
	DRM_UNLOCK(dev);

	for (i = 0; i < DRM_RESERVED_CONTEXTS; i++) {
		temp = drm_ctxbitmap_next(dev);
		DRM_DEBUG("drm_ctxbitmap_init : %d\n", temp);
	}

	return 0;
}