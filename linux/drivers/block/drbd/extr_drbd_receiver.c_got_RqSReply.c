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
struct packet_info {int /*<<< orphan*/  vnr; struct p_req_state_reply* data; } ;
struct p_req_state_reply {int /*<<< orphan*/  retcode; } ;
struct drbd_peer_device {struct drbd_device* device; } ;
struct drbd_device {int /*<<< orphan*/  state_wait; int /*<<< orphan*/  flags; } ;
struct drbd_connection {int agreed_pro_version; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ST_CHG_FAIL ; 
 int /*<<< orphan*/  CL_ST_CHG_SUCCESS ; 
 int /*<<< orphan*/  CONN_WD_ST_CHG_REQ ; 
 int /*<<< orphan*/  D_ASSERT (struct drbd_device*,int) ; 
 int EIO ; 
 int SS_SUCCESS ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct drbd_peer_device* conn_peer_device (struct drbd_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_err (struct drbd_device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drbd_set_st_err_str (int) ; 
 int got_conn_RqSReply (struct drbd_connection*,struct packet_info*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int got_RqSReply(struct drbd_connection *connection, struct packet_info *pi)
{
	struct drbd_peer_device *peer_device;
	struct drbd_device *device;
	struct p_req_state_reply *p = pi->data;
	int retcode = be32_to_cpu(p->retcode);

	peer_device = conn_peer_device(connection, pi->vnr);
	if (!peer_device)
		return -EIO;
	device = peer_device->device;

	if (test_bit(CONN_WD_ST_CHG_REQ, &connection->flags)) {
		D_ASSERT(device, connection->agreed_pro_version < 100);
		return got_conn_RqSReply(connection, pi);
	}

	if (retcode >= SS_SUCCESS) {
		set_bit(CL_ST_CHG_SUCCESS, &device->flags);
	} else {
		set_bit(CL_ST_CHG_FAIL, &device->flags);
		drbd_err(device, "Requested state change failed by peer: %s (%d)\n",
			drbd_set_st_err_str(retcode), retcode);
	}
	wake_up(&device->state_wait);

	return 0;
}