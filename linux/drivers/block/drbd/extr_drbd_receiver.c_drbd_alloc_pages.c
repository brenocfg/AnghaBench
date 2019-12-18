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
struct page {int dummy; } ;
struct net_conf {int max_buffers; } ;
struct drbd_peer_device {TYPE_1__* connection; struct drbd_device* device; } ;
struct drbd_device {int /*<<< orphan*/  pp_in_use; int /*<<< orphan*/  pp_in_use_by_net; } ;
struct TYPE_2__ {int /*<<< orphan*/  net_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int HZ ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 unsigned int UINT_MAX ; 
 struct page* __drbd_alloc_pages (struct drbd_device*,unsigned int) ; 
 int /*<<< orphan*/  atomic_add (unsigned int,int /*<<< orphan*/ *) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  drbd_pp_wait ; 
 int /*<<< orphan*/  drbd_reclaim_net_peer_reqs (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_warn (struct drbd_device*,char*) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct net_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ schedule_timeout (int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

struct page *drbd_alloc_pages(struct drbd_peer_device *peer_device, unsigned int number,
			      bool retry)
{
	struct drbd_device *device = peer_device->device;
	struct page *page = NULL;
	struct net_conf *nc;
	DEFINE_WAIT(wait);
	unsigned int mxb;

	rcu_read_lock();
	nc = rcu_dereference(peer_device->connection->net_conf);
	mxb = nc ? nc->max_buffers : 1000000;
	rcu_read_unlock();

	if (atomic_read(&device->pp_in_use) < mxb)
		page = __drbd_alloc_pages(device, number);

	/* Try to keep the fast path fast, but occasionally we need
	 * to reclaim the pages we lended to the network stack. */
	if (page && atomic_read(&device->pp_in_use_by_net) > 512)
		drbd_reclaim_net_peer_reqs(device);

	while (page == NULL) {
		prepare_to_wait(&drbd_pp_wait, &wait, TASK_INTERRUPTIBLE);

		drbd_reclaim_net_peer_reqs(device);

		if (atomic_read(&device->pp_in_use) < mxb) {
			page = __drbd_alloc_pages(device, number);
			if (page)
				break;
		}

		if (!retry)
			break;

		if (signal_pending(current)) {
			drbd_warn(device, "drbd_alloc_pages interrupted!\n");
			break;
		}

		if (schedule_timeout(HZ/10) == 0)
			mxb = UINT_MAX;
	}
	finish_wait(&drbd_pp_wait, &wait);

	if (page)
		atomic_add(number, &device->pp_in_use);
	return page;
}