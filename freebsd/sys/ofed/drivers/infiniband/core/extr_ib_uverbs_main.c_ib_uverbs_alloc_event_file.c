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
struct ib_uverbs_file {int /*<<< orphan*/  ref; struct ib_uverbs_event_file* async_file; int /*<<< orphan*/  event_handler; TYPE_1__* device; } ;
struct ib_uverbs_event_file {int is_async; int /*<<< orphan*/  ref; struct ib_uverbs_file* uverbs_file; int /*<<< orphan*/  list; scalar_t__ is_closed; int /*<<< orphan*/ * async_queue; int /*<<< orphan*/  poll_wait; int /*<<< orphan*/  event_list; int /*<<< orphan*/  lock; } ;
struct ib_device {int dummy; } ;
struct file {struct ib_uverbs_event_file* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  lists_mutex; int /*<<< orphan*/  uverbs_events_file_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct file* ERR_PTR (int) ; 
 int /*<<< orphan*/  FMODE_READ ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_IB_EVENT_HANDLER (int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int /*<<< orphan*/  WARN_ON (struct ib_uverbs_event_file*) ; 
 struct file* alloc_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fops_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int ib_register_event_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_uverbs_event_handler ; 
 int /*<<< orphan*/  ib_uverbs_release_event_file ; 
 int /*<<< orphan*/  ib_uverbs_release_file ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ib_uverbs_event_file* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uverbs_event_fops ; 

struct file *ib_uverbs_alloc_event_file(struct ib_uverbs_file *uverbs_file,
					struct ib_device	*ib_dev,
					int is_async)
{
	struct ib_uverbs_event_file *ev_file;
	struct file *filp;
	int ret;

	ev_file = kzalloc(sizeof(*ev_file), GFP_KERNEL);
	if (!ev_file)
		return ERR_PTR(-ENOMEM);

	kref_init(&ev_file->ref);
	spin_lock_init(&ev_file->lock);
	INIT_LIST_HEAD(&ev_file->event_list);
	init_waitqueue_head(&ev_file->poll_wait);
	ev_file->uverbs_file = uverbs_file;
	kref_get(&ev_file->uverbs_file->ref);
	ev_file->async_queue = NULL;
	ev_file->is_closed   = 0;

	/*
	 * fops_get() can't fail here, because we're coming from a
	 * system call on a uverbs file, which will already have a
	 * module reference.
	 */
	filp = alloc_file(FMODE_READ, fops_get(&uverbs_event_fops));
	if (IS_ERR(filp))
		goto err_put_refs;
	filp->private_data = ev_file;

	mutex_lock(&uverbs_file->device->lists_mutex);
	list_add_tail(&ev_file->list,
		      &uverbs_file->device->uverbs_events_file_list);
	mutex_unlock(&uverbs_file->device->lists_mutex);

	if (is_async) {
		WARN_ON(uverbs_file->async_file);
		uverbs_file->async_file = ev_file;
		kref_get(&uverbs_file->async_file->ref);
		INIT_IB_EVENT_HANDLER(&uverbs_file->event_handler,
				      ib_dev,
				      ib_uverbs_event_handler);
		ret = ib_register_event_handler(&uverbs_file->event_handler);
		if (ret)
			goto err_put_file;

		/* At that point async file stuff was fully set */
		ev_file->is_async = 1;
	}

	return filp;

err_put_file:
	fput(filp);
	kref_put(&uverbs_file->async_file->ref, ib_uverbs_release_event_file);
	uverbs_file->async_file = NULL;
	return ERR_PTR(ret);

err_put_refs:
	kref_put(&ev_file->uverbs_file->ref, ib_uverbs_release_file);
	kref_put(&ev_file->ref, ib_uverbs_release_event_file);
	return filp;
}