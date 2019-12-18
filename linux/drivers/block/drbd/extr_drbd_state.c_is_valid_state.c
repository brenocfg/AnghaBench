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
union drbd_state {scalar_t__ role; scalar_t__ peer; scalar_t__ conn; scalar_t__ disk; scalar_t__ pdsk; } ;
struct net_conf {int fencing; scalar_t__* verify_alg; int /*<<< orphan*/  two_primaries; } ;
struct drbd_device {scalar_t__ open_cnt; TYPE_1__* ldev; } ;
typedef  enum drbd_state_rv { ____Placeholder_drbd_state_rv } drbd_state_rv ;
typedef  enum drbd_fencing_p { ____Placeholder_drbd_fencing_p } drbd_fencing_p ;
struct TYPE_6__ {int agreed_pro_version; int /*<<< orphan*/  net_conf; } ;
struct TYPE_5__ {TYPE_3__* connection; } ;
struct TYPE_4__ {int /*<<< orphan*/  disk_conf; } ;

/* Variables and functions */
 scalar_t__ C_CONNECTED ; 
 scalar_t__ C_PAUSED_SYNC_S ; 
 scalar_t__ C_STARTING_SYNC_S ; 
 scalar_t__ C_STARTING_SYNC_T ; 
 scalar_t__ C_SYNC_SOURCE ; 
 scalar_t__ C_VERIFY_S ; 
 scalar_t__ C_VERIFY_T ; 
 scalar_t__ C_WF_BITMAP_S ; 
 scalar_t__ D_INCONSISTENT ; 
 scalar_t__ D_OUTDATED ; 
 scalar_t__ D_UNKNOWN ; 
 scalar_t__ D_UP_TO_DATE ; 
 int FP_DONT_CARE ; 
 int FP_RESOURCE ; 
 scalar_t__ R_PRIMARY ; 
 scalar_t__ R_SECONDARY ; 
 int SS_CONNECTED_OUTDATES ; 
 int SS_DEVICE_IN_USE ; 
 int SS_NEED_CONNECTION ; 
 int SS_NOT_SUPPORTED ; 
 int SS_NO_LOCAL_DISK ; 
 int SS_NO_REMOTE_DISK ; 
 int SS_NO_UP_TO_DATE_DISK ; 
 int SS_NO_VERIFY_ALG ; 
 int SS_O_VOL_PEER_PRI ; 
 int SS_PRIMARY_NOP ; 
 int SS_SUCCESS ; 
 int SS_TWO_PRIMARIES ; 
 scalar_t__ conn_highest_peer (TYPE_3__*) ; 
 TYPE_2__* first_peer_device (struct drbd_device*) ; 
 scalar_t__ get_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  put_ldev (struct drbd_device*) ; 
 struct net_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static enum drbd_state_rv
is_valid_state(struct drbd_device *device, union drbd_state ns)
{
	/* See drbd_state_sw_errors in drbd_strings.c */

	enum drbd_fencing_p fp;
	enum drbd_state_rv rv = SS_SUCCESS;
	struct net_conf *nc;

	rcu_read_lock();
	fp = FP_DONT_CARE;
	if (get_ldev(device)) {
		fp = rcu_dereference(device->ldev->disk_conf)->fencing;
		put_ldev(device);
	}

	nc = rcu_dereference(first_peer_device(device)->connection->net_conf);
	if (nc) {
		if (!nc->two_primaries && ns.role == R_PRIMARY) {
			if (ns.peer == R_PRIMARY)
				rv = SS_TWO_PRIMARIES;
			else if (conn_highest_peer(first_peer_device(device)->connection) == R_PRIMARY)
				rv = SS_O_VOL_PEER_PRI;
		}
	}

	if (rv <= 0)
		goto out; /* already found a reason to abort */
	else if (ns.role == R_SECONDARY && device->open_cnt)
		rv = SS_DEVICE_IN_USE;

	else if (ns.role == R_PRIMARY && ns.conn < C_CONNECTED && ns.disk < D_UP_TO_DATE)
		rv = SS_NO_UP_TO_DATE_DISK;

	else if (fp >= FP_RESOURCE &&
		 ns.role == R_PRIMARY && ns.conn < C_CONNECTED && ns.pdsk >= D_UNKNOWN)
		rv = SS_PRIMARY_NOP;

	else if (ns.role == R_PRIMARY && ns.disk <= D_INCONSISTENT && ns.pdsk <= D_INCONSISTENT)
		rv = SS_NO_UP_TO_DATE_DISK;

	else if (ns.conn > C_CONNECTED && ns.disk < D_INCONSISTENT)
		rv = SS_NO_LOCAL_DISK;

	else if (ns.conn > C_CONNECTED && ns.pdsk < D_INCONSISTENT)
		rv = SS_NO_REMOTE_DISK;

	else if (ns.conn > C_CONNECTED && ns.disk < D_UP_TO_DATE && ns.pdsk < D_UP_TO_DATE)
		rv = SS_NO_UP_TO_DATE_DISK;

	else if ((ns.conn == C_CONNECTED ||
		  ns.conn == C_WF_BITMAP_S ||
		  ns.conn == C_SYNC_SOURCE ||
		  ns.conn == C_PAUSED_SYNC_S) &&
		  ns.disk == D_OUTDATED)
		rv = SS_CONNECTED_OUTDATES;

	else if ((ns.conn == C_VERIFY_S || ns.conn == C_VERIFY_T) &&
		 (nc->verify_alg[0] == 0))
		rv = SS_NO_VERIFY_ALG;

	else if ((ns.conn == C_VERIFY_S || ns.conn == C_VERIFY_T) &&
		  first_peer_device(device)->connection->agreed_pro_version < 88)
		rv = SS_NOT_SUPPORTED;

	else if (ns.role == R_PRIMARY && ns.disk < D_UP_TO_DATE && ns.pdsk < D_UP_TO_DATE)
		rv = SS_NO_UP_TO_DATE_DISK;

	else if ((ns.conn == C_STARTING_SYNC_S || ns.conn == C_STARTING_SYNC_T) &&
                 ns.pdsk == D_UNKNOWN)
		rv = SS_NEED_CONNECTION;

	else if (ns.conn >= C_CONNECTED && ns.pdsk == D_UNKNOWN)
		rv = SS_CONNECTED_OUTDATES;

out:
	rcu_read_unlock();

	return rv;
}