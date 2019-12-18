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
union drbd_dev_state {int /*<<< orphan*/  disk; int /*<<< orphan*/  conn; } ;
struct drbd_device {union drbd_dev_state state; } ;
typedef  enum drbd_disk_state { ____Placeholder_drbd_disk_state } drbd_disk_state ;
typedef  enum drbd_conns { ____Placeholder_drbd_conns } drbd_conns ;
struct TYPE_4__ {TYPE_1__* connection; } ;
struct TYPE_3__ {int agreed_pro_version; } ;

/* Variables and functions */
#define  C_AHEAD 162 
#define  C_BEHIND 161 
#define  C_BROKEN_PIPE 160 
#define  C_CONNECTED 159 
#define  C_DISCONNECTING 158 
#define  C_MASK 157 
#define  C_NETWORK_FAILURE 156 
#define  C_PAUSED_SYNC_S 155 
#define  C_PAUSED_SYNC_T 154 
#define  C_PROTOCOL_ERROR 153 
#define  C_STANDALONE 152 
#define  C_STARTING_SYNC_S 151 
#define  C_STARTING_SYNC_T 150 
#define  C_SYNC_SOURCE 149 
#define  C_SYNC_TARGET 148 
#define  C_TEAR_DOWN 147 
#define  C_TIMEOUT 146 
#define  C_UNCONNECTED 145 
#define  C_VERIFY_S 144 
#define  C_VERIFY_T 143 
#define  C_WF_BITMAP_S 142 
#define  C_WF_BITMAP_T 141 
#define  C_WF_CONNECTION 140 
#define  C_WF_REPORT_PARAMS 139 
#define  C_WF_SYNC_UUID 138 
#define  D_ATTACHING 137 
#define  D_CONSISTENT 136 
#define  D_DISKLESS 135 
#define  D_FAILED 134 
#define  D_INCONSISTENT 133 
#define  D_MASK 132 
#define  D_NEGOTIATING 131 
#define  D_OUTDATED 130 
#define  D_UNKNOWN 129 
#define  D_UP_TO_DATE 128 
 TYPE_2__* first_peer_device (struct drbd_device*) ; 

__attribute__((used)) static inline int drbd_state_is_stable(struct drbd_device *device)
{
	union drbd_dev_state s = device->state;

	/* DO NOT add a default clause, we want the compiler to warn us
	 * for any newly introduced state we may have forgotten to add here */

	switch ((enum drbd_conns)s.conn) {
	/* new io only accepted when there is no connection, ... */
	case C_STANDALONE:
	case C_WF_CONNECTION:
	/* ... or there is a well established connection. */
	case C_CONNECTED:
	case C_SYNC_SOURCE:
	case C_SYNC_TARGET:
	case C_VERIFY_S:
	case C_VERIFY_T:
	case C_PAUSED_SYNC_S:
	case C_PAUSED_SYNC_T:
	case C_AHEAD:
	case C_BEHIND:
		/* transitional states, IO allowed */
	case C_DISCONNECTING:
	case C_UNCONNECTED:
	case C_TIMEOUT:
	case C_BROKEN_PIPE:
	case C_NETWORK_FAILURE:
	case C_PROTOCOL_ERROR:
	case C_TEAR_DOWN:
	case C_WF_REPORT_PARAMS:
	case C_STARTING_SYNC_S:
	case C_STARTING_SYNC_T:
		break;

		/* Allow IO in BM exchange states with new protocols */
	case C_WF_BITMAP_S:
		if (first_peer_device(device)->connection->agreed_pro_version < 96)
			return 0;
		break;

		/* no new io accepted in these states */
	case C_WF_BITMAP_T:
	case C_WF_SYNC_UUID:
	case C_MASK:
		/* not "stable" */
		return 0;
	}

	switch ((enum drbd_disk_state)s.disk) {
	case D_DISKLESS:
	case D_INCONSISTENT:
	case D_OUTDATED:
	case D_CONSISTENT:
	case D_UP_TO_DATE:
	case D_FAILED:
		/* disk state is stable as well. */
		break;

	/* no new io accepted during transitional states */
	case D_ATTACHING:
	case D_NEGOTIATING:
	case D_UNKNOWN:
	case D_MASK:
		/* not "stable" */
		return 0;
	}

	return 1;
}