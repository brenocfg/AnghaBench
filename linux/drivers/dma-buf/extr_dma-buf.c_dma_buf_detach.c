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
struct dma_buf_attachment {int /*<<< orphan*/  node; int /*<<< orphan*/  dir; scalar_t__ sgt; } ;
struct dma_buf {int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* detach ) (struct dma_buf*,struct dma_buf_attachment*) ;int /*<<< orphan*/  (* unmap_dma_buf ) (struct dma_buf_attachment*,scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct dma_buf_attachment*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct dma_buf_attachment*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct dma_buf*,struct dma_buf_attachment*) ; 

void dma_buf_detach(struct dma_buf *dmabuf, struct dma_buf_attachment *attach)
{
	if (WARN_ON(!dmabuf || !attach))
		return;

	if (attach->sgt)
		dmabuf->ops->unmap_dma_buf(attach, attach->sgt, attach->dir);

	mutex_lock(&dmabuf->lock);
	list_del(&attach->node);
	if (dmabuf->ops->detach)
		dmabuf->ops->detach(dmabuf, attach);

	mutex_unlock(&dmabuf->lock);
	kfree(attach);
}