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
struct drm_device {int /*<<< orphan*/ ** context_sareas; int /*<<< orphan*/ * ctx_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  DRM_LOCK (struct drm_device*) ; 
 int DRM_MAX_CTXBITMAP ; 
 int /*<<< orphan*/  DRM_UNLOCK (struct drm_device*) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 

void drm_ctxbitmap_free(struct drm_device * dev, int ctx_handle)
{
	if (ctx_handle < 0 || ctx_handle >= DRM_MAX_CTXBITMAP ||
	    dev->ctx_bitmap == NULL) {
		DRM_ERROR("Attempt to free invalid context handle: %d\n",
		   ctx_handle);
		return;
	}

	DRM_LOCK(dev);
	clear_bit(ctx_handle, dev->ctx_bitmap);
	dev->context_sareas[ctx_handle] = NULL;
	DRM_UNLOCK(dev);
}