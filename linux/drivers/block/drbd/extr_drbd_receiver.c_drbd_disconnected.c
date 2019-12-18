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
struct drbd_peer_device {TYPE_2__* connection; struct drbd_device* device; } ;
struct drbd_device {int /*<<< orphan*/  done_ee; int /*<<< orphan*/  sync_ee; int /*<<< orphan*/  active_ee; int /*<<< orphan*/  read_ee; int /*<<< orphan*/  pp_in_use; int /*<<< orphan*/  pp_in_use_by_net; int /*<<< orphan*/  net_ee; int /*<<< orphan*/ * p_uuid; int /*<<< orphan*/  resync_timer; int /*<<< orphan*/  misc_wait; int /*<<< orphan*/  rs_pending_cnt; scalar_t__ rs_failed; scalar_t__ rs_total; TYPE_1__* resource; } ;
struct TYPE_4__ {int /*<<< orphan*/  sender_work; } ;
struct TYPE_3__ {int /*<<< orphan*/  req_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_LOCKED_CHANGE_ALLOWED ; 
 int /*<<< orphan*/  D_ASSERT (struct drbd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _drbd_wait_ee_list_empty (struct drbd_device*,int /*<<< orphan*/ *) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drbd_bitmap_io (struct drbd_device*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_bm_write_copy_pages ; 
 int /*<<< orphan*/  drbd_finish_peer_reqs (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_flush_workqueue (int /*<<< orphan*/ *) ; 
 unsigned int drbd_free_peer_reqs (struct drbd_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drbd_info (struct drbd_device*,char*,unsigned int) ; 
 int /*<<< orphan*/  drbd_md_sync (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_rs_cancel_all (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_suspended (struct drbd_device*) ; 
 scalar_t__ get_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  resync_timer_fn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tl_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drbd_disconnected(struct drbd_peer_device *peer_device)
{
	struct drbd_device *device = peer_device->device;
	unsigned int i;

	/* wait for current activity to cease. */
	spin_lock_irq(&device->resource->req_lock);
	_drbd_wait_ee_list_empty(device, &device->active_ee);
	_drbd_wait_ee_list_empty(device, &device->sync_ee);
	_drbd_wait_ee_list_empty(device, &device->read_ee);
	spin_unlock_irq(&device->resource->req_lock);

	/* We do not have data structures that would allow us to
	 * get the rs_pending_cnt down to 0 again.
	 *  * On C_SYNC_TARGET we do not have any data structures describing
	 *    the pending RSDataRequest's we have sent.
	 *  * On C_SYNC_SOURCE there is no data structure that tracks
	 *    the P_RS_DATA_REPLY blocks that we sent to the SyncTarget.
	 *  And no, it is not the sum of the reference counts in the
	 *  resync_LRU. The resync_LRU tracks the whole operation including
	 *  the disk-IO, while the rs_pending_cnt only tracks the blocks
	 *  on the fly. */
	drbd_rs_cancel_all(device);
	device->rs_total = 0;
	device->rs_failed = 0;
	atomic_set(&device->rs_pending_cnt, 0);
	wake_up(&device->misc_wait);

	del_timer_sync(&device->resync_timer);
	resync_timer_fn(&device->resync_timer);

	/* wait for all w_e_end_data_req, w_e_end_rsdata_req, w_send_barrier,
	 * w_make_resync_request etc. which may still be on the worker queue
	 * to be "canceled" */
	drbd_flush_workqueue(&peer_device->connection->sender_work);

	drbd_finish_peer_reqs(device);

	/* This second workqueue flush is necessary, since drbd_finish_peer_reqs()
	   might have issued a work again. The one before drbd_finish_peer_reqs() is
	   necessary to reclain net_ee in drbd_finish_peer_reqs(). */
	drbd_flush_workqueue(&peer_device->connection->sender_work);

	/* need to do it again, drbd_finish_peer_reqs() may have populated it
	 * again via drbd_try_clear_on_disk_bm(). */
	drbd_rs_cancel_all(device);

	kfree(device->p_uuid);
	device->p_uuid = NULL;

	if (!drbd_suspended(device))
		tl_clear(peer_device->connection);

	drbd_md_sync(device);

	if (get_ldev(device)) {
		drbd_bitmap_io(device, &drbd_bm_write_copy_pages,
				"write from disconnected", BM_LOCKED_CHANGE_ALLOWED);
		put_ldev(device);
	}

	/* tcp_close and release of sendpage pages can be deferred.  I don't
	 * want to use SO_LINGER, because apparently it can be deferred for
	 * more than 20 seconds (longest time I checked).
	 *
	 * Actually we don't care for exactly when the network stack does its
	 * put_page(), but release our reference on these pages right here.
	 */
	i = drbd_free_peer_reqs(device, &device->net_ee);
	if (i)
		drbd_info(device, "net_ee not empty, killed %u entries\n", i);
	i = atomic_read(&device->pp_in_use_by_net);
	if (i)
		drbd_info(device, "pp_in_use_by_net = %d, expected 0\n", i);
	i = atomic_read(&device->pp_in_use);
	if (i)
		drbd_info(device, "pp_in_use = %d, expected 0\n", i);

	D_ASSERT(device, list_empty(&device->read_ee));
	D_ASSERT(device, list_empty(&device->active_ee));
	D_ASSERT(device, list_empty(&device->sync_ee));
	D_ASSERT(device, list_empty(&device->done_ee));

	return 0;
}