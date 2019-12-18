#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  list; } ;
struct TYPE_10__ {int /*<<< orphan*/  list; } ;
struct drbd_device {TYPE_5__ unplug_work; TYPE_4__ resync_work; int /*<<< orphan*/  resync_reads; int /*<<< orphan*/  net_ee; int /*<<< orphan*/  read_ee; int /*<<< orphan*/  done_ee; int /*<<< orphan*/  sync_ee; int /*<<< orphan*/  active_ee; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ldev; scalar_t__ bitmap; scalar_t__* rs_mark_time; scalar_t__* rs_mark_left; scalar_t__ rs_last_sect_ev; scalar_t__ rs_last_events; scalar_t__ rs_failed; scalar_t__ rs_total; scalar_t__ rs_start; scalar_t__ p_size; scalar_t__ writ_cnt; scalar_t__ send_cnt; scalar_t__ recv_cnt; scalar_t__ read_cnt; scalar_t__ bm_writ_cnt; scalar_t__ al_writ_cnt; } ;
struct TYPE_12__ {TYPE_3__* connection; } ;
struct TYPE_8__ {int /*<<< orphan*/  q; } ;
struct TYPE_7__ {scalar_t__ t_state; } ;
struct TYPE_9__ {TYPE_2__ sender_work; int /*<<< orphan*/ * net_conf; TYPE_1__ receiver; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_SUSPENDED ; 
 int DRBD_SYNC_MARKS ; 
 int /*<<< orphan*/  D_ASSERT (struct drbd_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ NONE ; 
 int /*<<< orphan*/  _drbd_set_my_capacity (struct drbd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drbd_backing_dev_free (struct drbd_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drbd_bm_cleanup (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_bm_resize (struct drbd_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drbd_err (struct drbd_device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  drbd_set_defaults (struct drbd_device*) ; 
 TYPE_6__* first_peer_device (struct drbd_device*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void drbd_device_cleanup(struct drbd_device *device)
{
	int i;
	if (first_peer_device(device)->connection->receiver.t_state != NONE)
		drbd_err(device, "ASSERT FAILED: receiver t_state == %d expected 0.\n",
				first_peer_device(device)->connection->receiver.t_state);

	device->al_writ_cnt  =
	device->bm_writ_cnt  =
	device->read_cnt     =
	device->recv_cnt     =
	device->send_cnt     =
	device->writ_cnt     =
	device->p_size       =
	device->rs_start     =
	device->rs_total     =
	device->rs_failed    = 0;
	device->rs_last_events = 0;
	device->rs_last_sect_ev = 0;
	for (i = 0; i < DRBD_SYNC_MARKS; i++) {
		device->rs_mark_left[i] = 0;
		device->rs_mark_time[i] = 0;
	}
	D_ASSERT(device, first_peer_device(device)->connection->net_conf == NULL);

	_drbd_set_my_capacity(device, 0);
	if (device->bitmap) {
		/* maybe never allocated. */
		drbd_bm_resize(device, 0, 1);
		drbd_bm_cleanup(device);
	}

	drbd_backing_dev_free(device, device->ldev);
	device->ldev = NULL;

	clear_bit(AL_SUSPENDED, &device->flags);

	D_ASSERT(device, list_empty(&device->active_ee));
	D_ASSERT(device, list_empty(&device->sync_ee));
	D_ASSERT(device, list_empty(&device->done_ee));
	D_ASSERT(device, list_empty(&device->read_ee));
	D_ASSERT(device, list_empty(&device->net_ee));
	D_ASSERT(device, list_empty(&device->resync_reads));
	D_ASSERT(device, list_empty(&first_peer_device(device)->connection->sender_work.q));
	D_ASSERT(device, list_empty(&device->resync_work.list));
	D_ASSERT(device, list_empty(&device->unplug_work.list));

	drbd_set_defaults(device);
}