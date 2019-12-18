#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_conf {int on_congestion; scalar_t__ cong_fill; scalar_t__ cong_extents; } ;
struct TYPE_4__ {scalar_t__ conn; } ;
struct drbd_device {TYPE_2__* act_log; int /*<<< orphan*/  ap_in_flight; TYPE_1__ state; } ;
struct drbd_connection {int agreed_pro_version; int /*<<< orphan*/  net_conf; } ;
typedef  enum drbd_on_congestion { ____Placeholder_drbd_on_congestion } drbd_on_congestion ;
struct TYPE_6__ {struct drbd_connection* connection; } ;
struct TYPE_5__ {scalar_t__ used; } ;

/* Variables and functions */
 scalar_t__ C_AHEAD ; 
 scalar_t__ C_DISCONNECTING ; 
 int /*<<< orphan*/  D_UP_TO_DATE ; 
 int OC_BLOCK ; 
 int OC_PULL_AHEAD ; 
 int /*<<< orphan*/  _NS (struct drbd_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _drbd_set_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  drbd_info (struct drbd_device*,char*) ; 
 TYPE_3__* first_peer_device (struct drbd_device*) ; 
 int /*<<< orphan*/  get_ldev_if_state (struct drbd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ldev (struct drbd_device*) ; 
 struct net_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  start_new_tl_epoch (struct drbd_connection*) ; 

__attribute__((used)) static void maybe_pull_ahead(struct drbd_device *device)
{
	struct drbd_connection *connection = first_peer_device(device)->connection;
	struct net_conf *nc;
	bool congested = false;
	enum drbd_on_congestion on_congestion;

	rcu_read_lock();
	nc = rcu_dereference(connection->net_conf);
	on_congestion = nc ? nc->on_congestion : OC_BLOCK;
	rcu_read_unlock();
	if (on_congestion == OC_BLOCK ||
	    connection->agreed_pro_version < 96)
		return;

	if (on_congestion == OC_PULL_AHEAD && device->state.conn == C_AHEAD)
		return; /* nothing to do ... */

	/* If I don't even have good local storage, we can not reasonably try
	 * to pull ahead of the peer. We also need the local reference to make
	 * sure device->act_log is there.
	 */
	if (!get_ldev_if_state(device, D_UP_TO_DATE))
		return;

	if (nc->cong_fill &&
	    atomic_read(&device->ap_in_flight) >= nc->cong_fill) {
		drbd_info(device, "Congestion-fill threshold reached\n");
		congested = true;
	}

	if (device->act_log->used >= nc->cong_extents) {
		drbd_info(device, "Congestion-extents threshold reached\n");
		congested = true;
	}

	if (congested) {
		/* start a new epoch for non-mirrored writes */
		start_new_tl_epoch(first_peer_device(device)->connection);

		if (on_congestion == OC_PULL_AHEAD)
			_drbd_set_state(_NS(device, conn, C_AHEAD), 0, NULL);
		else  /*nc->on_congestion == OC_DISCONNECT */
			_drbd_set_state(_NS(device, conn, C_DISCONNECTING), 0, NULL);
	}
	put_ldev(device);
}