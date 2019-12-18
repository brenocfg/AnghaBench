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
struct TYPE_4__ {TYPE_1__* parent; } ;
struct virtio_device {TYPE_2__ dev; } ;
struct port_buffer {int sgpages; size_t size; scalar_t__ offset; scalar_t__ len; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * dev; int /*<<< orphan*/  dma; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 scalar_t__ is_rproc_serial (struct virtio_device*) ; 
 int /*<<< orphan*/  kfree (struct port_buffer*) ; 
 void* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reclaim_dma_bufs () ; 
 int /*<<< orphan*/  sg ; 
 size_t struct_size (struct port_buffer*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct port_buffer *alloc_buf(struct virtio_device *vdev, size_t buf_size,
				     int pages)
{
	struct port_buffer *buf;

	reclaim_dma_bufs();

	/*
	 * Allocate buffer and the sg list. The sg list array is allocated
	 * directly after the port_buffer struct.
	 */
	buf = kmalloc(struct_size(buf, sg, pages), GFP_KERNEL);
	if (!buf)
		goto fail;

	buf->sgpages = pages;
	if (pages > 0) {
		buf->dev = NULL;
		buf->buf = NULL;
		return buf;
	}

	if (is_rproc_serial(vdev)) {
		/*
		 * Allocate DMA memory from ancestor. When a virtio
		 * device is created by remoteproc, the DMA memory is
		 * associated with the grandparent device:
		 * vdev => rproc => platform-dev.
		 */
		if (!vdev->dev.parent || !vdev->dev.parent->parent)
			goto free_buf;
		buf->dev = vdev->dev.parent->parent;

		/* Increase device refcnt to avoid freeing it */
		get_device(buf->dev);
		buf->buf = dma_alloc_coherent(buf->dev, buf_size, &buf->dma,
					      GFP_KERNEL);
	} else {
		buf->dev = NULL;
		buf->buf = kmalloc(buf_size, GFP_KERNEL);
	}

	if (!buf->buf)
		goto free_buf;
	buf->len = 0;
	buf->offset = 0;
	buf->size = buf_size;
	return buf;

free_buf:
	kfree(buf);
fail:
	return NULL;
}