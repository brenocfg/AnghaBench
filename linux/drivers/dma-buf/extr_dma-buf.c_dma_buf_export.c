#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct file {int /*<<< orphan*/  f_mode; } ;
struct dma_resv {int dummy; } ;
struct dma_buf_export_info {int /*<<< orphan*/  owner; int /*<<< orphan*/  flags; int /*<<< orphan*/  exp_name; int /*<<< orphan*/  size; TYPE_1__* ops; scalar_t__ priv; struct dma_resv* resv; } ;
struct TYPE_7__ {scalar_t__ active; int /*<<< orphan*/ * poll; } ;
struct TYPE_6__ {scalar_t__ active; int /*<<< orphan*/ * poll; } ;
struct dma_buf {int /*<<< orphan*/  list_node; int /*<<< orphan*/  attachments; int /*<<< orphan*/  lock; struct file* file; struct dma_resv* resv; TYPE_3__ cb_shared; TYPE_2__ cb_excl; int /*<<< orphan*/  poll; int /*<<< orphan*/  owner; int /*<<< orphan*/  exp_name; int /*<<< orphan*/  size; TYPE_1__* ops; scalar_t__ priv; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  head; } ;
struct TYPE_5__ {int /*<<< orphan*/  release; int /*<<< orphan*/  unmap_dma_buf; int /*<<< orphan*/  map_dma_buf; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct dma_buf* ERR_PTR (int) ; 
 int /*<<< orphan*/  FMODE_LSEEK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int PTR_ERR (struct file*) ; 
 scalar_t__ WARN_ON (int) ; 
 TYPE_4__ db_list ; 
 struct file* dma_buf_getfile (struct dma_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_resv_init (struct dma_resv*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dma_buf*) ; 
 struct dma_buf* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

struct dma_buf *dma_buf_export(const struct dma_buf_export_info *exp_info)
{
	struct dma_buf *dmabuf;
	struct dma_resv *resv = exp_info->resv;
	struct file *file;
	size_t alloc_size = sizeof(struct dma_buf);
	int ret;

	if (!exp_info->resv)
		alloc_size += sizeof(struct dma_resv);
	else
		/* prevent &dma_buf[1] == dma_buf->resv */
		alloc_size += 1;

	if (WARN_ON(!exp_info->priv
			  || !exp_info->ops
			  || !exp_info->ops->map_dma_buf
			  || !exp_info->ops->unmap_dma_buf
			  || !exp_info->ops->release)) {
		return ERR_PTR(-EINVAL);
	}

	if (!try_module_get(exp_info->owner))
		return ERR_PTR(-ENOENT);

	dmabuf = kzalloc(alloc_size, GFP_KERNEL);
	if (!dmabuf) {
		ret = -ENOMEM;
		goto err_module;
	}

	dmabuf->priv = exp_info->priv;
	dmabuf->ops = exp_info->ops;
	dmabuf->size = exp_info->size;
	dmabuf->exp_name = exp_info->exp_name;
	dmabuf->owner = exp_info->owner;
	init_waitqueue_head(&dmabuf->poll);
	dmabuf->cb_excl.poll = dmabuf->cb_shared.poll = &dmabuf->poll;
	dmabuf->cb_excl.active = dmabuf->cb_shared.active = 0;

	if (!resv) {
		resv = (struct dma_resv *)&dmabuf[1];
		dma_resv_init(resv);
	}
	dmabuf->resv = resv;

	file = dma_buf_getfile(dmabuf, exp_info->flags);
	if (IS_ERR(file)) {
		ret = PTR_ERR(file);
		goto err_dmabuf;
	}

	file->f_mode |= FMODE_LSEEK;
	dmabuf->file = file;

	mutex_init(&dmabuf->lock);
	INIT_LIST_HEAD(&dmabuf->attachments);

	mutex_lock(&db_list.lock);
	list_add(&dmabuf->list_node, &db_list.head);
	mutex_unlock(&db_list.lock);

	return dmabuf;

err_dmabuf:
	kfree(dmabuf);
err_module:
	module_put(exp_info->owner);
	return ERR_PTR(ret);
}