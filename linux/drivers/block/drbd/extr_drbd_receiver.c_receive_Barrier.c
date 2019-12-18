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
struct packet_info {struct p_barrier* data; } ;
struct p_barrier {int /*<<< orphan*/  barrier; } ;
struct drbd_epoch {int /*<<< orphan*/  list; int /*<<< orphan*/  epoch_size; int /*<<< orphan*/  active; scalar_t__ flags; struct drbd_connection* connection; int /*<<< orphan*/  barrier_nr; } ;
struct drbd_connection {int /*<<< orphan*/  epoch_lock; int /*<<< orphan*/  epochs; struct drbd_epoch* current_epoch; TYPE_1__* resource; } ;
struct TYPE_2__ {int write_ordering; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  EV_GOT_BARRIER_NR ; 
 int FE_RECYCLED ; 
 int /*<<< orphan*/  GFP_NOIO ; 
#define  WO_BDEV_FLUSH 130 
#define  WO_DRAIN_IO 129 
#define  WO_NONE 128 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn_wait_active_ee_empty (struct drbd_connection*) ; 
 int /*<<< orphan*/  drbd_err (struct drbd_connection*,char*,int) ; 
 int /*<<< orphan*/  drbd_flush (struct drbd_connection*) ; 
 int drbd_may_finish_epoch (struct drbd_connection*,struct drbd_epoch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_warn (struct drbd_connection*,char*) ; 
 int /*<<< orphan*/  kfree (struct drbd_epoch*) ; 
 struct drbd_epoch* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int receive_Barrier(struct drbd_connection *connection, struct packet_info *pi)
{
	int rv;
	struct p_barrier *p = pi->data;
	struct drbd_epoch *epoch;

	/* FIXME these are unacked on connection,
	 * not a specific (peer)device.
	 */
	connection->current_epoch->barrier_nr = p->barrier;
	connection->current_epoch->connection = connection;
	rv = drbd_may_finish_epoch(connection, connection->current_epoch, EV_GOT_BARRIER_NR);

	/* P_BARRIER_ACK may imply that the corresponding extent is dropped from
	 * the activity log, which means it would not be resynced in case the
	 * R_PRIMARY crashes now.
	 * Therefore we must send the barrier_ack after the barrier request was
	 * completed. */
	switch (connection->resource->write_ordering) {
	case WO_NONE:
		if (rv == FE_RECYCLED)
			return 0;

		/* receiver context, in the writeout path of the other node.
		 * avoid potential distributed deadlock */
		epoch = kmalloc(sizeof(struct drbd_epoch), GFP_NOIO);
		if (epoch)
			break;
		else
			drbd_warn(connection, "Allocation of an epoch failed, slowing down\n");
			/* Fall through */

	case WO_BDEV_FLUSH:
	case WO_DRAIN_IO:
		conn_wait_active_ee_empty(connection);
		drbd_flush(connection);

		if (atomic_read(&connection->current_epoch->epoch_size)) {
			epoch = kmalloc(sizeof(struct drbd_epoch), GFP_NOIO);
			if (epoch)
				break;
		}

		return 0;
	default:
		drbd_err(connection, "Strangeness in connection->write_ordering %d\n",
			 connection->resource->write_ordering);
		return -EIO;
	}

	epoch->flags = 0;
	atomic_set(&epoch->epoch_size, 0);
	atomic_set(&epoch->active, 0);

	spin_lock(&connection->epoch_lock);
	if (atomic_read(&connection->current_epoch->epoch_size)) {
		list_add(&epoch->list, &connection->current_epoch->list);
		connection->current_epoch = epoch;
		connection->epochs++;
	} else {
		/* The current_epoch got recycled while we allocated this one... */
		kfree(epoch);
	}
	spin_unlock(&connection->epoch_lock);

	return 0;
}