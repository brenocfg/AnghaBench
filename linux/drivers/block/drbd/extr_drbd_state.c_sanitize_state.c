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
union drbd_state {scalar_t__ conn; scalar_t__ pdsk; scalar_t__ disk; scalar_t__ role; int susp_fen; int susp_nod; scalar_t__ user_isp; scalar_t__ peer_isp; scalar_t__ aftr_isp; int /*<<< orphan*/  peer; } ;
struct TYPE_9__ {scalar_t__ disk; scalar_t__ pdsk; } ;
struct drbd_device {scalar_t__ ed_uuid; TYPE_5__* resource; TYPE_3__ new_state_tmp; TYPE_2__* ldev; } ;
typedef  enum sanitize_state_warnings { ____Placeholder_sanitize_state_warnings } sanitize_state_warnings ;
typedef  enum drbd_fencing_p { ____Placeholder_drbd_fencing_p } drbd_fencing_p ;
typedef  enum drbd_disk_state { ____Placeholder_drbd_disk_state } drbd_disk_state ;
typedef  enum drbd_conns { ____Placeholder_drbd_conns } drbd_conns ;
struct TYPE_12__ {int fencing; } ;
struct TYPE_10__ {scalar_t__ on_no_data; } ;
struct TYPE_11__ {TYPE_4__ res_opts; } ;
struct TYPE_7__ {scalar_t__* uuid; } ;
struct TYPE_8__ {TYPE_1__ md; int /*<<< orphan*/  disk_conf; } ;

/* Variables and functions */
 int ABORTED_ONLINE_VERIFY ; 
 int ABORTED_RESYNC ; 
 int CONNECTION_LOST_NEGOTIATING ; 
#define  C_AHEAD 152 
#define  C_BEHIND 151 
#define  C_BROKEN_PIPE 150 
#define  C_CONNECTED 149 
#define  C_DISCONNECTING 148 
#define  C_MASK 147 
#define  C_NETWORK_FAILURE 146 
#define  C_PAUSED_SYNC_S 145 
#define  C_PAUSED_SYNC_T 144 
#define  C_PROTOCOL_ERROR 143 
#define  C_STANDALONE 142 
#define  C_STARTING_SYNC_S 141 
#define  C_STARTING_SYNC_T 140 
#define  C_SYNC_SOURCE 139 
#define  C_SYNC_TARGET 138 
#define  C_TEAR_DOWN 137 
#define  C_TIMEOUT 136 
#define  C_UNCONNECTED 135 
#define  C_VERIFY_S 134 
#define  C_VERIFY_T 133 
#define  C_WF_BITMAP_S 132 
#define  C_WF_BITMAP_T 131 
#define  C_WF_CONNECTION 130 
#define  C_WF_REPORT_PARAMS 129 
#define  C_WF_SYNC_UUID 128 
 scalar_t__ D_CONSISTENT ; 
 scalar_t__ D_DISKLESS ; 
 scalar_t__ D_FAILED ; 
 scalar_t__ D_INCONSISTENT ; 
 scalar_t__ D_NEGOTIATING ; 
 scalar_t__ D_OUTDATED ; 
 scalar_t__ D_UNKNOWN ; 
 scalar_t__ D_UP_TO_DATE ; 
 int FP_DONT_CARE ; 
 int FP_STONITH ; 
 int IMPLICITLY_UPGRADED_DISK ; 
 int IMPLICITLY_UPGRADED_PDSK ; 
 int NO_WARNING ; 
 scalar_t__ OND_SUSPEND_IO ; 
 scalar_t__ R_PRIMARY ; 
 scalar_t__ R_SECONDARY ; 
 int /*<<< orphan*/  R_UNKNOWN ; 
 size_t UI_CURRENT ; 
 scalar_t__ get_ldev (struct drbd_device*) ; 
 scalar_t__ get_ldev_if_state (struct drbd_device*,scalar_t__) ; 
 int /*<<< orphan*/  put_ldev (struct drbd_device*) ; 
 TYPE_6__* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static union drbd_state sanitize_state(struct drbd_device *device, union drbd_state os,
				       union drbd_state ns, enum sanitize_state_warnings *warn)
{
	enum drbd_fencing_p fp;
	enum drbd_disk_state disk_min, disk_max, pdsk_min, pdsk_max;

	if (warn)
		*warn = NO_WARNING;

	fp = FP_DONT_CARE;
	if (get_ldev(device)) {
		rcu_read_lock();
		fp = rcu_dereference(device->ldev->disk_conf)->fencing;
		rcu_read_unlock();
		put_ldev(device);
	}

	/* Implications from connection to peer and peer_isp */
	if (ns.conn < C_CONNECTED) {
		ns.peer_isp = 0;
		ns.peer = R_UNKNOWN;
		if (ns.pdsk > D_UNKNOWN || ns.pdsk < D_INCONSISTENT)
			ns.pdsk = D_UNKNOWN;
	}

	/* Clear the aftr_isp when becoming unconfigured */
	if (ns.conn == C_STANDALONE && ns.disk == D_DISKLESS && ns.role == R_SECONDARY)
		ns.aftr_isp = 0;

	/* An implication of the disk states onto the connection state */
	/* Abort resync if a disk fails/detaches */
	if (ns.conn > C_CONNECTED && (ns.disk <= D_FAILED || ns.pdsk <= D_FAILED)) {
		if (warn)
			*warn = ns.conn == C_VERIFY_S || ns.conn == C_VERIFY_T ?
				ABORTED_ONLINE_VERIFY : ABORTED_RESYNC;
		ns.conn = C_CONNECTED;
	}

	/* Connection breaks down before we finished "Negotiating" */
	if (ns.conn < C_CONNECTED && ns.disk == D_NEGOTIATING &&
	    get_ldev_if_state(device, D_NEGOTIATING)) {
		if (device->ed_uuid == device->ldev->md.uuid[UI_CURRENT]) {
			ns.disk = device->new_state_tmp.disk;
			ns.pdsk = device->new_state_tmp.pdsk;
		} else {
			if (warn)
				*warn = CONNECTION_LOST_NEGOTIATING;
			ns.disk = D_DISKLESS;
			ns.pdsk = D_UNKNOWN;
		}
		put_ldev(device);
	}

	/* D_CONSISTENT and D_OUTDATED vanish when we get connected */
	if (ns.conn >= C_CONNECTED && ns.conn < C_AHEAD) {
		if (ns.disk == D_CONSISTENT || ns.disk == D_OUTDATED)
			ns.disk = D_UP_TO_DATE;
		if (ns.pdsk == D_CONSISTENT || ns.pdsk == D_OUTDATED)
			ns.pdsk = D_UP_TO_DATE;
	}

	/* Implications of the connection state on the disk states */
	disk_min = D_DISKLESS;
	disk_max = D_UP_TO_DATE;
	pdsk_min = D_INCONSISTENT;
	pdsk_max = D_UNKNOWN;
	switch ((enum drbd_conns)ns.conn) {
	case C_WF_BITMAP_T:
	case C_PAUSED_SYNC_T:
	case C_STARTING_SYNC_T:
	case C_WF_SYNC_UUID:
	case C_BEHIND:
		disk_min = D_INCONSISTENT;
		disk_max = D_OUTDATED;
		pdsk_min = D_UP_TO_DATE;
		pdsk_max = D_UP_TO_DATE;
		break;
	case C_VERIFY_S:
	case C_VERIFY_T:
		disk_min = D_UP_TO_DATE;
		disk_max = D_UP_TO_DATE;
		pdsk_min = D_UP_TO_DATE;
		pdsk_max = D_UP_TO_DATE;
		break;
	case C_CONNECTED:
		disk_min = D_DISKLESS;
		disk_max = D_UP_TO_DATE;
		pdsk_min = D_DISKLESS;
		pdsk_max = D_UP_TO_DATE;
		break;
	case C_WF_BITMAP_S:
	case C_PAUSED_SYNC_S:
	case C_STARTING_SYNC_S:
	case C_AHEAD:
		disk_min = D_UP_TO_DATE;
		disk_max = D_UP_TO_DATE;
		pdsk_min = D_INCONSISTENT;
		pdsk_max = D_CONSISTENT; /* D_OUTDATED would be nice. But explicit outdate necessary*/
		break;
	case C_SYNC_TARGET:
		disk_min = D_INCONSISTENT;
		disk_max = D_INCONSISTENT;
		pdsk_min = D_UP_TO_DATE;
		pdsk_max = D_UP_TO_DATE;
		break;
	case C_SYNC_SOURCE:
		disk_min = D_UP_TO_DATE;
		disk_max = D_UP_TO_DATE;
		pdsk_min = D_INCONSISTENT;
		pdsk_max = D_INCONSISTENT;
		break;
	case C_STANDALONE:
	case C_DISCONNECTING:
	case C_UNCONNECTED:
	case C_TIMEOUT:
	case C_BROKEN_PIPE:
	case C_NETWORK_FAILURE:
	case C_PROTOCOL_ERROR:
	case C_TEAR_DOWN:
	case C_WF_CONNECTION:
	case C_WF_REPORT_PARAMS:
	case C_MASK:
		break;
	}
	if (ns.disk > disk_max)
		ns.disk = disk_max;

	if (ns.disk < disk_min) {
		if (warn)
			*warn = IMPLICITLY_UPGRADED_DISK;
		ns.disk = disk_min;
	}
	if (ns.pdsk > pdsk_max)
		ns.pdsk = pdsk_max;

	if (ns.pdsk < pdsk_min) {
		if (warn)
			*warn = IMPLICITLY_UPGRADED_PDSK;
		ns.pdsk = pdsk_min;
	}

	if (fp == FP_STONITH &&
	    (ns.role == R_PRIMARY && ns.conn < C_CONNECTED && ns.pdsk > D_OUTDATED) &&
	    !(os.role == R_PRIMARY && os.conn < C_CONNECTED && os.pdsk > D_OUTDATED))
		ns.susp_fen = 1; /* Suspend IO while fence-peer handler runs (peer lost) */

	if (device->resource->res_opts.on_no_data == OND_SUSPEND_IO &&
	    (ns.role == R_PRIMARY && ns.disk < D_UP_TO_DATE && ns.pdsk < D_UP_TO_DATE) &&
	    !(os.role == R_PRIMARY && os.disk < D_UP_TO_DATE && os.pdsk < D_UP_TO_DATE))
		ns.susp_nod = 1; /* Suspend IO while no data available (no accessible data available) */

	if (ns.aftr_isp || ns.peer_isp || ns.user_isp) {
		if (ns.conn == C_SYNC_SOURCE)
			ns.conn = C_PAUSED_SYNC_S;
		if (ns.conn == C_SYNC_TARGET)
			ns.conn = C_PAUSED_SYNC_T;
	} else {
		if (ns.conn == C_PAUSED_SYNC_S)
			ns.conn = C_SYNC_SOURCE;
		if (ns.conn == C_PAUSED_SYNC_T)
			ns.conn = C_SYNC_TARGET;
	}

	return ns;
}