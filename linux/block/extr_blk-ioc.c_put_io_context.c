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
struct io_context {int /*<<< orphan*/  lock; int /*<<< orphan*/  release_work; int /*<<< orphan*/  icq_list; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ atomic_long_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iocontext_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct io_context*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

void put_io_context(struct io_context *ioc)
{
	unsigned long flags;
	bool free_ioc = false;

	if (ioc == NULL)
		return;

	BUG_ON(atomic_long_read(&ioc->refcount) <= 0);

	/*
	 * Releasing ioc requires reverse order double locking and we may
	 * already be holding a queue_lock.  Do it asynchronously from wq.
	 */
	if (atomic_long_dec_and_test(&ioc->refcount)) {
		spin_lock_irqsave(&ioc->lock, flags);
		if (!hlist_empty(&ioc->icq_list))
			queue_work(system_power_efficient_wq,
					&ioc->release_work);
		else
			free_ioc = true;
		spin_unlock_irqrestore(&ioc->lock, flags);
	}

	if (free_ioc)
		kmem_cache_free(iocontext_cachep, ioc);
}