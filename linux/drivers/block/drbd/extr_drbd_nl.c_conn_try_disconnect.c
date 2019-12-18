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
struct drbd_connection {int cstate; int /*<<< orphan*/  receiver; TYPE_1__* resource; } ;
typedef  enum drbd_state_rv { ____Placeholder_drbd_state_rv } drbd_state_rv ;
typedef  enum drbd_conns { ____Placeholder_drbd_conns } drbd_conns ;
struct TYPE_2__ {int /*<<< orphan*/  req_lock; } ;

/* Variables and functions */
 int CS_HARD ; 
 int CS_VERBOSE ; 
 int /*<<< orphan*/  C_DISCONNECTING ; 
 int /*<<< orphan*/  C_STANDALONE ; 
 int C_WF_CONNECTION ; 
 int /*<<< orphan*/  D_OUTDATED ; 
 int /*<<< orphan*/  NS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SS_ALREADY_STANDALONE 131 
#define  SS_CW_FAILED_BY_PEER 130 
 int SS_IS_DISKLESS ; 
 int SS_LOWER_THAN_OUTDATED ; 
#define  SS_NOTHING_TO_DO 129 
 int SS_OUTDATE_WO_CONN ; 
#define  SS_PRIMARY_NOP 128 
 int SS_SUCCESS ; 
 int /*<<< orphan*/  conn ; 
 int conn_request_state (struct drbd_connection*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  disk ; 
 int /*<<< orphan*/  drbd_err (struct drbd_connection*,char*,int) ; 
 int /*<<< orphan*/  drbd_thread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdsk ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum drbd_state_rv conn_try_disconnect(struct drbd_connection *connection, bool force)
{
	enum drbd_conns cstate;
	enum drbd_state_rv rv;

repeat:
	rv = conn_request_state(connection, NS(conn, C_DISCONNECTING),
			force ? CS_HARD : 0);

	switch (rv) {
	case SS_NOTHING_TO_DO:
		break;
	case SS_ALREADY_STANDALONE:
		return SS_SUCCESS;
	case SS_PRIMARY_NOP:
		/* Our state checking code wants to see the peer outdated. */
		rv = conn_request_state(connection, NS2(conn, C_DISCONNECTING, pdsk, D_OUTDATED), 0);

		if (rv == SS_OUTDATE_WO_CONN) /* lost connection before graceful disconnect succeeded */
			rv = conn_request_state(connection, NS(conn, C_DISCONNECTING), CS_VERBOSE);

		break;
	case SS_CW_FAILED_BY_PEER:
		spin_lock_irq(&connection->resource->req_lock);
		cstate = connection->cstate;
		spin_unlock_irq(&connection->resource->req_lock);
		if (cstate <= C_WF_CONNECTION)
			goto repeat;
		/* The peer probably wants to see us outdated. */
		rv = conn_request_state(connection, NS2(conn, C_DISCONNECTING,
							disk, D_OUTDATED), 0);
		if (rv == SS_IS_DISKLESS || rv == SS_LOWER_THAN_OUTDATED) {
			rv = conn_request_state(connection, NS(conn, C_DISCONNECTING),
					CS_HARD);
		}
		break;
	default:;
		/* no special handling necessary */
	}

	if (rv >= SS_SUCCESS) {
		enum drbd_state_rv rv2;
		/* No one else can reconfigure the network while I am here.
		 * The state handling only uses drbd_thread_stop_nowait(),
		 * we want to really wait here until the receiver is no more.
		 */
		drbd_thread_stop(&connection->receiver);

		/* Race breaker.  This additional state change request may be
		 * necessary, if this was a forced disconnect during a receiver
		 * restart.  We may have "killed" the receiver thread just
		 * after drbd_receiver() returned.  Typically, we should be
		 * C_STANDALONE already, now, and this becomes a no-op.
		 */
		rv2 = conn_request_state(connection, NS(conn, C_STANDALONE),
				CS_VERBOSE | CS_HARD);
		if (rv2 < SS_SUCCESS)
			drbd_err(connection,
				"unexpected rv2=%d in conn_try_disconnect()\n",
				rv2);
		/* Unlike in DRBD 9, the state engine has generated
		 * NOTIFY_DESTROY events before clearing connection->net_conf. */
	}
	return rv;
}