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
union drbd_state {scalar_t__ conn; scalar_t__ disk; scalar_t__ role; scalar_t__ pdsk; } ;
struct drbd_connection {int /*<<< orphan*/  flags; } ;
typedef  enum drbd_state_rv { ____Placeholder_drbd_state_rv } drbd_state_rv ;

/* Variables and functions */
 scalar_t__ C_CONNECTED ; 
 scalar_t__ C_DISCONNECTING ; 
 scalar_t__ C_STANDALONE ; 
 scalar_t__ C_STARTING_SYNC_S ; 
 scalar_t__ C_STARTING_SYNC_T ; 
 scalar_t__ C_SYNC_SOURCE ; 
 scalar_t__ C_SYNC_TARGET ; 
 scalar_t__ C_UNCONNECTED ; 
 scalar_t__ C_VERIFY_S ; 
 scalar_t__ C_VERIFY_T ; 
 scalar_t__ C_WF_CONNECTION ; 
 scalar_t__ C_WF_REPORT_PARAMS ; 
 scalar_t__ C_WF_SYNC_UUID ; 
 scalar_t__ D_ATTACHING ; 
 scalar_t__ D_DISKLESS ; 
 scalar_t__ D_OUTDATED ; 
 scalar_t__ D_UP_TO_DATE ; 
 scalar_t__ R_PRIMARY ; 
 int SS_ALREADY_STANDALONE ; 
 int SS_IN_TRANSIENT_STATE ; 
 int SS_IS_DISKLESS ; 
 int SS_LOWER_THAN_OUTDATED ; 
 int SS_NEED_CONNECTION ; 
 int SS_NO_NET_CONFIG ; 
 int SS_OUTDATE_WO_CONN ; 
 int SS_RESYNC_RUNNING ; 
 int SS_SUCCESS ; 
 int /*<<< orphan*/  STATE_SENT ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum drbd_state_rv
is_valid_soft_transition(union drbd_state os, union drbd_state ns, struct drbd_connection *connection)
{
	enum drbd_state_rv rv = SS_SUCCESS;

	if ((ns.conn == C_STARTING_SYNC_T || ns.conn == C_STARTING_SYNC_S) &&
	    os.conn > C_CONNECTED)
		rv = SS_RESYNC_RUNNING;

	if (ns.conn == C_DISCONNECTING && os.conn == C_STANDALONE)
		rv = SS_ALREADY_STANDALONE;

	if (ns.disk > D_ATTACHING && os.disk == D_DISKLESS)
		rv = SS_IS_DISKLESS;

	if (ns.conn == C_WF_CONNECTION && os.conn < C_UNCONNECTED)
		rv = SS_NO_NET_CONFIG;

	if (ns.disk == D_OUTDATED && os.disk < D_OUTDATED && os.disk != D_ATTACHING)
		rv = SS_LOWER_THAN_OUTDATED;

	if (ns.conn == C_DISCONNECTING && os.conn == C_UNCONNECTED)
		rv = SS_IN_TRANSIENT_STATE;

	/* While establishing a connection only allow cstate to change.
	   Delay/refuse role changes, detach attach etc... (they do not touch cstate) */
	if (test_bit(STATE_SENT, &connection->flags) &&
	    !((ns.conn == C_WF_REPORT_PARAMS && os.conn == C_WF_CONNECTION) ||
	      (ns.conn >= C_CONNECTED && os.conn == C_WF_REPORT_PARAMS)))
		rv = SS_IN_TRANSIENT_STATE;

	/* Do not promote during resync handshake triggered by "force primary".
	 * This is a hack. It should really be rejected by the peer during the
	 * cluster wide state change request. */
	if (os.role != R_PRIMARY && ns.role == R_PRIMARY
		&& ns.pdsk == D_UP_TO_DATE
		&& ns.disk != D_UP_TO_DATE && ns.disk != D_DISKLESS
		&& (ns.conn <= C_WF_SYNC_UUID || ns.conn != os.conn))
			rv = SS_IN_TRANSIENT_STATE;

	if ((ns.conn == C_VERIFY_S || ns.conn == C_VERIFY_T) && os.conn < C_CONNECTED)
		rv = SS_NEED_CONNECTION;

	if ((ns.conn == C_VERIFY_S || ns.conn == C_VERIFY_T) &&
	    ns.conn != os.conn && os.conn > C_CONNECTED)
		rv = SS_RESYNC_RUNNING;

	if ((ns.conn == C_STARTING_SYNC_S || ns.conn == C_STARTING_SYNC_T) &&
	    os.conn < C_CONNECTED)
		rv = SS_NEED_CONNECTION;

	if ((ns.conn == C_SYNC_TARGET || ns.conn == C_SYNC_SOURCE)
	    && os.conn < C_WF_REPORT_PARAMS)
		rv = SS_NEED_CONNECTION; /* No NetworkFailure -> SyncTarget etc... */

	if (ns.conn == C_DISCONNECTING && ns.pdsk == D_OUTDATED &&
	    os.conn < C_CONNECTED && os.pdsk > D_OUTDATED)
		rv = SS_OUTDATE_WO_CONN;

	return rv;
}