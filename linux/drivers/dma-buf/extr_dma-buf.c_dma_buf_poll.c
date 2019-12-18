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
struct file {struct dma_buf* private_data; } ;
struct dma_resv_list {unsigned int shared_count; int /*<<< orphan*/ * shared; } ;
struct dma_resv {int /*<<< orphan*/  seq; int /*<<< orphan*/  fence_excl; int /*<<< orphan*/  fence; } ;
struct dma_fence {int dummy; } ;
struct dma_buf_poll_cb_t {int active; int /*<<< orphan*/  cb; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct dma_buf {TYPE_1__ poll; struct dma_buf_poll_cb_t cb_shared; struct dma_buf_poll_cb_t cb_excl; struct dma_resv* resv; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int /*<<< orphan*/  dma_buf_poll_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_add_callback (struct dma_fence*,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  dma_fence_get_rcu (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int poll_requested_events (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 void* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 unsigned int read_seqcount_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqcount_retry (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t dma_buf_poll(struct file *file, poll_table *poll)
{
	struct dma_buf *dmabuf;
	struct dma_resv *resv;
	struct dma_resv_list *fobj;
	struct dma_fence *fence_excl;
	__poll_t events;
	unsigned shared_count, seq;

	dmabuf = file->private_data;
	if (!dmabuf || !dmabuf->resv)
		return EPOLLERR;

	resv = dmabuf->resv;

	poll_wait(file, &dmabuf->poll, poll);

	events = poll_requested_events(poll) & (EPOLLIN | EPOLLOUT);
	if (!events)
		return 0;

retry:
	seq = read_seqcount_begin(&resv->seq);
	rcu_read_lock();

	fobj = rcu_dereference(resv->fence);
	if (fobj)
		shared_count = fobj->shared_count;
	else
		shared_count = 0;
	fence_excl = rcu_dereference(resv->fence_excl);
	if (read_seqcount_retry(&resv->seq, seq)) {
		rcu_read_unlock();
		goto retry;
	}

	if (fence_excl && (!(events & EPOLLOUT) || shared_count == 0)) {
		struct dma_buf_poll_cb_t *dcb = &dmabuf->cb_excl;
		__poll_t pevents = EPOLLIN;

		if (shared_count == 0)
			pevents |= EPOLLOUT;

		spin_lock_irq(&dmabuf->poll.lock);
		if (dcb->active) {
			dcb->active |= pevents;
			events &= ~pevents;
		} else
			dcb->active = pevents;
		spin_unlock_irq(&dmabuf->poll.lock);

		if (events & pevents) {
			if (!dma_fence_get_rcu(fence_excl)) {
				/* force a recheck */
				events &= ~pevents;
				dma_buf_poll_cb(NULL, &dcb->cb);
			} else if (!dma_fence_add_callback(fence_excl, &dcb->cb,
							   dma_buf_poll_cb)) {
				events &= ~pevents;
				dma_fence_put(fence_excl);
			} else {
				/*
				 * No callback queued, wake up any additional
				 * waiters.
				 */
				dma_fence_put(fence_excl);
				dma_buf_poll_cb(NULL, &dcb->cb);
			}
		}
	}

	if ((events & EPOLLOUT) && shared_count > 0) {
		struct dma_buf_poll_cb_t *dcb = &dmabuf->cb_shared;
		int i;

		/* Only queue a new callback if no event has fired yet */
		spin_lock_irq(&dmabuf->poll.lock);
		if (dcb->active)
			events &= ~EPOLLOUT;
		else
			dcb->active = EPOLLOUT;
		spin_unlock_irq(&dmabuf->poll.lock);

		if (!(events & EPOLLOUT))
			goto out;

		for (i = 0; i < shared_count; ++i) {
			struct dma_fence *fence = rcu_dereference(fobj->shared[i]);

			if (!dma_fence_get_rcu(fence)) {
				/*
				 * fence refcount dropped to zero, this means
				 * that fobj has been freed
				 *
				 * call dma_buf_poll_cb and force a recheck!
				 */
				events &= ~EPOLLOUT;
				dma_buf_poll_cb(NULL, &dcb->cb);
				break;
			}
			if (!dma_fence_add_callback(fence, &dcb->cb,
						    dma_buf_poll_cb)) {
				dma_fence_put(fence);
				events &= ~EPOLLOUT;
				break;
			}
			dma_fence_put(fence);
		}

		/* No callback queued, wake up any additional waiters. */
		if (i == shared_count)
			dma_buf_poll_cb(NULL, &dcb->cb);
	}

out:
	rcu_read_unlock();
	return events;
}