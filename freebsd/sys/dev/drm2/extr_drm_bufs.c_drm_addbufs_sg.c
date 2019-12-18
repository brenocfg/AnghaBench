#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_device_dma {int buf_count; int page_count; int /*<<< orphan*/  flags; scalar_t__ byte_count; int /*<<< orphan*/  seg_count; struct drm_buf** buflist; struct drm_buf_entry* bufs; } ;
struct drm_device {int /*<<< orphan*/  buf_alloc; TYPE_2__* driver; TYPE_1__* sg; int /*<<< orphan*/  count_lock; scalar_t__ buf_use; struct drm_device_dma* dma; } ;
struct drm_buf_entry {int buf_count; int buf_size; int page_order; scalar_t__ seg_count; struct drm_buf* buflist; } ;
struct drm_buf_desc {int count; int size; int flags; unsigned long agp_start; } ;
struct drm_buf {int idx; int total; int order; unsigned long bus_address; int dev_priv_size; void* address; void* dev_private; int /*<<< orphan*/ * file_priv; scalar_t__ pending; scalar_t__ waiting; int /*<<< orphan*/ * next; scalar_t__ offset; scalar_t__ used; } ;
struct TYPE_4__ {int dev_priv_size; } ;
struct TYPE_3__ {scalar_t__ vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_SG ; 
 int /*<<< orphan*/  DRM_CURPROC ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int,...) ; 
 int /*<<< orphan*/  DRM_LOCK (struct drm_device*) ; 
 int DRM_MAX_ORDER ; 
 int /*<<< orphan*/  DRM_MEM_BUFS ; 
 int DRM_MIN_ORDER ; 
 int /*<<< orphan*/  DRM_SUSER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_UNLOCK (struct drm_device*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int PAGE_ALIGN (int) ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  _DRM_DMA_USE_SG ; 
 int _DRM_PAGE_ALIGN ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_cleanup_buf_error (struct drm_device*,struct drm_buf_entry*) ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int drm_order (int) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct drm_buf** realloc (struct drm_buf**,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int drm_addbufs_sg(struct drm_device * dev, struct drm_buf_desc * request)
{
	struct drm_device_dma *dma = dev->dma;
	struct drm_buf_entry *entry;
	struct drm_buf *buf;
	unsigned long offset;
	unsigned long agp_offset;
	int count;
	int order;
	int size;
	int alignment;
	int page_order;
	int total;
	int byte_count;
	int i;
	struct drm_buf **temp_buflist;

	if (!drm_core_check_feature(dev, DRIVER_SG))
		return -EINVAL;

	if (!dma)
		return -EINVAL;

	if (!DRM_SUSER(DRM_CURPROC))
		return -EPERM;

	count = request->count;
	order = drm_order(request->size);
	size = 1 << order;

	alignment = (request->flags & _DRM_PAGE_ALIGN)
	    ? PAGE_ALIGN(size) : size;
	page_order = order - PAGE_SHIFT > 0 ? order - PAGE_SHIFT : 0;
	total = PAGE_SIZE << page_order;

	byte_count = 0;
	agp_offset = request->agp_start;

	DRM_DEBUG("count:      %d\n", count);
	DRM_DEBUG("order:      %d\n", order);
	DRM_DEBUG("size:       %d\n", size);
	DRM_DEBUG("agp_offset: %lu\n", agp_offset);
	DRM_DEBUG("alignment:  %d\n", alignment);
	DRM_DEBUG("page_order: %d\n", page_order);
	DRM_DEBUG("total:      %d\n", total);

	if (order < DRM_MIN_ORDER || order > DRM_MAX_ORDER)
		return -EINVAL;

	mtx_lock(&dev->count_lock);
	if (dev->buf_use) {
		mtx_unlock(&dev->count_lock);
		return -EBUSY;
	}
	atomic_inc(&dev->buf_alloc);
	mtx_unlock(&dev->count_lock);

	DRM_LOCK(dev);
	entry = &dma->bufs[order];
	if (entry->buf_count) {
		DRM_UNLOCK(dev);
		atomic_dec(&dev->buf_alloc);
		return -ENOMEM;	/* May only call once for each order */
	}

	if (count < 0 || count > 4096) {
		DRM_UNLOCK(dev);
		atomic_dec(&dev->buf_alloc);
		return -EINVAL;
	}

	entry->buflist = malloc(count * sizeof(*entry->buflist), DRM_MEM_BUFS,
	    M_NOWAIT | M_ZERO);
	if (!entry->buflist) {
		DRM_UNLOCK(dev);
		atomic_dec(&dev->buf_alloc);
		return -ENOMEM;
	}

	entry->buf_size = size;
	entry->page_order = page_order;

	offset = 0;

	while (entry->buf_count < count) {
		buf = &entry->buflist[entry->buf_count];
		buf->idx = dma->buf_count + entry->buf_count;
		buf->total = alignment;
		buf->order = order;
		buf->used = 0;

		buf->offset = (dma->byte_count + offset);
		buf->bus_address = agp_offset + offset;
		buf->address = (void *)(agp_offset + offset
					+ (unsigned long)dev->sg->vaddr);
		buf->next = NULL;
		buf->waiting = 0;
		buf->pending = 0;
		buf->file_priv = NULL;

		buf->dev_priv_size = dev->driver->dev_priv_size;
		buf->dev_private = malloc(buf->dev_priv_size, DRM_MEM_BUFS,
		    M_NOWAIT | M_ZERO);
		if (!buf->dev_private) {
			/* Set count correctly so we free the proper amount. */
			entry->buf_count = count;
			drm_cleanup_buf_error(dev, entry);
			DRM_UNLOCK(dev);
			atomic_dec(&dev->buf_alloc);
			return -ENOMEM;
		}

		DRM_DEBUG("buffer %d @ %p\n", entry->buf_count, buf->address);

		offset += alignment;
		entry->buf_count++;
		byte_count += PAGE_SIZE << page_order;
	}

	DRM_DEBUG("byte_count: %d\n", byte_count);

	temp_buflist = realloc(dma->buflist,
	    (dma->buf_count + entry->buf_count) * sizeof(*dma->buflist),
	    DRM_MEM_BUFS, M_NOWAIT);
	if (!temp_buflist) {
		/* Free the entry because it isn't valid */
		drm_cleanup_buf_error(dev, entry);
		DRM_UNLOCK(dev);
		atomic_dec(&dev->buf_alloc);
		return -ENOMEM;
	}
	dma->buflist = temp_buflist;

	for (i = 0; i < entry->buf_count; i++) {
		dma->buflist[i + dma->buf_count] = &entry->buflist[i];
	}

	dma->buf_count += entry->buf_count;
	dma->seg_count += entry->seg_count;
	dma->page_count += byte_count >> PAGE_SHIFT;
	dma->byte_count += byte_count;

	DRM_DEBUG("dma->buf_count : %d\n", dma->buf_count);
	DRM_DEBUG("entry->buf_count : %d\n", entry->buf_count);

	DRM_UNLOCK(dev);

	request->count = entry->buf_count;
	request->size = size;

	dma->flags = _DRM_DMA_USE_SG;

	atomic_dec(&dev->buf_alloc);
	return 0;
}