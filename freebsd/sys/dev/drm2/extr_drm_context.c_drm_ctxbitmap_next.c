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
struct drm_local_map {int dummy; } ;
struct drm_device {int max_context; struct drm_local_map** context_sareas; int /*<<< orphan*/ * ctx_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int /*<<< orphan*/  DRM_LOCK (struct drm_device*) ; 
 int DRM_MAX_CTXBITMAP ; 
 int /*<<< orphan*/  DRM_MEM_SAREA ; 
 int /*<<< orphan*/  DRM_UNLOCK (struct drm_device*) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int find_first_zero_bit (int /*<<< orphan*/ *,int) ; 
 struct drm_local_map** realloc (struct drm_local_map**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drm_ctxbitmap_next(struct drm_device * dev)
{
	int bit;

	if (dev->ctx_bitmap == NULL)
		return -1;

	DRM_LOCK(dev);
	bit = find_first_zero_bit(dev->ctx_bitmap, DRM_MAX_CTXBITMAP);
	if (bit >= DRM_MAX_CTXBITMAP) {
		DRM_UNLOCK(dev);
		return -1;
	}

	set_bit(bit, dev->ctx_bitmap);
	DRM_DEBUG("bit : %d\n", bit);
	if ((bit+1) > dev->max_context) {
		struct drm_local_map **ctx_sareas;
		int max_ctx = (bit+1);

		ctx_sareas = realloc(dev->context_sareas,
		    max_ctx * sizeof(*dev->context_sareas),
		    DRM_MEM_SAREA, M_NOWAIT);
		if (ctx_sareas == NULL) {
			clear_bit(bit, dev->ctx_bitmap);
			DRM_DEBUG("failed to allocate bit : %d\n", bit);
			DRM_UNLOCK(dev);
			return -1;
		}
		dev->max_context = max_ctx;
		dev->context_sareas = ctx_sareas;
		dev->context_sareas[bit] = NULL;
	}
	DRM_UNLOCK(dev);
	return bit;
}