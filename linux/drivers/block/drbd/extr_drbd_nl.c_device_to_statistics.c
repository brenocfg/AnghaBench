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
typedef  scalar_t__ u64 ;
struct request_queue {int /*<<< orphan*/  backing_dev_info; } ;
struct drbd_md {int /*<<< orphan*/  flags; int /*<<< orphan*/  uuid_lock; scalar_t__* uuid; } ;
struct drbd_device {int /*<<< orphan*/  ed_uuid; int /*<<< orphan*/  flags; int /*<<< orphan*/  local_cnt; int /*<<< orphan*/  ap_bio_cnt; int /*<<< orphan*/  bm_writ_cnt; int /*<<< orphan*/  al_writ_cnt; int /*<<< orphan*/  writ_cnt; int /*<<< orphan*/  read_cnt; int /*<<< orphan*/  this_bdev; TYPE_1__* ldev; } ;
struct device_statistics {int dev_upper_blocked; int history_uuids_len; int /*<<< orphan*/  dev_exposed_data_uuid; int /*<<< orphan*/  dev_al_suspended; void* dev_lower_pending; void* dev_upper_pending; int /*<<< orphan*/  dev_bm_writes; int /*<<< orphan*/  dev_al_writes; int /*<<< orphan*/  dev_write; int /*<<< orphan*/  dev_read; int /*<<< orphan*/  dev_size; int /*<<< orphan*/  dev_lower_blocked; int /*<<< orphan*/  dev_disk_flags; scalar_t__ dev_current_uuid; scalar_t__ history_uuids; } ;
struct TYPE_2__ {int /*<<< orphan*/  backing_bdev; struct drbd_md md; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_SUSPENDED ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int HISTORY_UUIDS ; 
 size_t UI_CURRENT ; 
 size_t UI_HISTORY_END ; 
 size_t UI_HISTORY_START ; 
 int WB_async_congested ; 
 int WB_sync_congested ; 
 void* atomic_read (int /*<<< orphan*/ *) ; 
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdi_congested (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drbd_get_capacity (int /*<<< orphan*/ ) ; 
 scalar_t__ get_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  may_inc_ap_bio (struct drbd_device*) ; 
 int /*<<< orphan*/  memset (struct device_statistics*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void device_to_statistics(struct device_statistics *s,
				 struct drbd_device *device)
{
	memset(s, 0, sizeof(*s));
	s->dev_upper_blocked = !may_inc_ap_bio(device);
	if (get_ldev(device)) {
		struct drbd_md *md = &device->ldev->md;
		u64 *history_uuids = (u64 *)s->history_uuids;
		struct request_queue *q;
		int n;

		spin_lock_irq(&md->uuid_lock);
		s->dev_current_uuid = md->uuid[UI_CURRENT];
		BUILD_BUG_ON(sizeof(s->history_uuids) < UI_HISTORY_END - UI_HISTORY_START + 1);
		for (n = 0; n < UI_HISTORY_END - UI_HISTORY_START + 1; n++)
			history_uuids[n] = md->uuid[UI_HISTORY_START + n];
		for (; n < HISTORY_UUIDS; n++)
			history_uuids[n] = 0;
		s->history_uuids_len = HISTORY_UUIDS;
		spin_unlock_irq(&md->uuid_lock);

		s->dev_disk_flags = md->flags;
		q = bdev_get_queue(device->ldev->backing_bdev);
		s->dev_lower_blocked =
			bdi_congested(q->backing_dev_info,
				      (1 << WB_async_congested) |
				      (1 << WB_sync_congested));
		put_ldev(device);
	}
	s->dev_size = drbd_get_capacity(device->this_bdev);
	s->dev_read = device->read_cnt;
	s->dev_write = device->writ_cnt;
	s->dev_al_writes = device->al_writ_cnt;
	s->dev_bm_writes = device->bm_writ_cnt;
	s->dev_upper_pending = atomic_read(&device->ap_bio_cnt);
	s->dev_lower_pending = atomic_read(&device->local_cnt);
	s->dev_al_suspended = test_bit(AL_SUSPENDED, &device->flags);
	s->dev_exposed_data_uuid = device->ed_uuid;
}