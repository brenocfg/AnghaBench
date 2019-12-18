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
struct drm_file {int dummy; } ;
struct drm_device_dma {struct drm_buf_entry* bufs; } ;
struct drm_device {struct drm_device_dma* dma; } ;
struct TYPE_2__ {scalar_t__ low_mark; scalar_t__ high_mark; } ;
struct drm_buf_entry {scalar_t__ buf_count; TYPE_1__ freelist; } ;
struct drm_buf_desc {scalar_t__ low_mark; scalar_t__ high_mark; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_HAVE_DMA ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int DRM_MAX_ORDER ; 
 int DRM_MIN_ORDER ; 
 int EINVAL ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int drm_order (int /*<<< orphan*/ ) ; 

int drm_markbufs(struct drm_device *dev, void *data,
		 struct drm_file *file_priv)
{
	struct drm_device_dma *dma = dev->dma;
	struct drm_buf_desc *request = data;
	int order;
	struct drm_buf_entry *entry;

	if (!drm_core_check_feature(dev, DRIVER_HAVE_DMA))
		return -EINVAL;

	if (!dma)
		return -EINVAL;

	DRM_DEBUG("%d, %d, %d\n",
		  request->size, request->low_mark, request->high_mark);
	order = drm_order(request->size);
	if (order < DRM_MIN_ORDER || order > DRM_MAX_ORDER)
		return -EINVAL;
	entry = &dma->bufs[order];

	if (request->low_mark < 0 || request->low_mark > entry->buf_count)
		return -EINVAL;
	if (request->high_mark < 0 || request->high_mark > entry->buf_count)
		return -EINVAL;

	entry->freelist.low_mark = request->low_mark;
	entry->freelist.high_mark = request->high_mark;

	return 0;
}