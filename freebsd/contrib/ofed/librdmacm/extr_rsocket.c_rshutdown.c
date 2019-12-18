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
struct rsocket {int opts; int fd_flags; int state; TYPE_1__* cm_id; int /*<<< orphan*/  ctrl_seqno; } ;
struct TYPE_2__ {int /*<<< orphan*/  recv_cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int O_NONBLOCK ; 
 int RS_CTRL_DISCONNECT ; 
 int RS_CTRL_SHUTDOWN ; 
 int RS_OPT_SVC_ACTIVE ; 
 int /*<<< orphan*/  RS_OP_CTRL ; 
 int /*<<< orphan*/  RS_SVC_REM_KEEPALIVE ; 
 int SHUT_RDWR ; 
 int SHUT_WR ; 
 int /*<<< orphan*/  ibv_req_notify_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idm ; 
 struct rsocket* idm_lookup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rs_conn_all_sends_done ; 
 int /*<<< orphan*/  rs_conn_can_send_ctrl ; 
 int rs_connected ; 
 scalar_t__ rs_ctrl_avail (struct rsocket*) ; 
 int rs_disconnected ; 
 int /*<<< orphan*/  rs_msg_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rs_notify_svc (int /*<<< orphan*/ *,struct rsocket*,int /*<<< orphan*/ ) ; 
 int rs_post_msg (struct rsocket*,int /*<<< orphan*/ ) ; 
 int rs_process_cq (struct rsocket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rs_readable ; 
 int /*<<< orphan*/  rs_set_nonblocking (struct rsocket*,int) ; 
 int rs_writable ; 
 int /*<<< orphan*/  tcp_svc ; 
 int /*<<< orphan*/  ucma_shutdown (TYPE_1__*) ; 

int rshutdown(int socket, int how)
{
	struct rsocket *rs;
	int ctrl, ret = 0;

	rs = idm_lookup(&idm, socket);
	if (!rs)
		return ERR(EBADF);
	if (rs->opts & RS_OPT_SVC_ACTIVE)
		rs_notify_svc(&tcp_svc, rs, RS_SVC_REM_KEEPALIVE);

	if (rs->fd_flags & O_NONBLOCK)
		rs_set_nonblocking(rs, 0);

	if (rs->state & rs_connected) {
		if (how == SHUT_RDWR) {
			ctrl = RS_CTRL_DISCONNECT;
			rs->state &= ~(rs_readable | rs_writable);
		} else if (how == SHUT_WR) {
			rs->state &= ~rs_writable;
			ctrl = (rs->state & rs_readable) ?
				RS_CTRL_SHUTDOWN : RS_CTRL_DISCONNECT;
		} else {
			rs->state &= ~rs_readable;
			if (rs->state & rs_writable)
				goto out;
			ctrl = RS_CTRL_DISCONNECT;
		}
		if (!rs_ctrl_avail(rs)) {
			ret = rs_process_cq(rs, 0, rs_conn_can_send_ctrl);
			if (ret)
				goto out;
		}

		if ((rs->state & rs_connected) && rs_ctrl_avail(rs)) {
			rs->ctrl_seqno++;
			ret = rs_post_msg(rs, rs_msg_set(RS_OP_CTRL, ctrl));
		}
	}

	if (rs->state & rs_connected)
		rs_process_cq(rs, 0, rs_conn_all_sends_done);

out:
	if ((rs->fd_flags & O_NONBLOCK) && (rs->state & rs_connected))
		rs_set_nonblocking(rs, rs->fd_flags);

	if (rs->state & rs_disconnected) {
		/* Generate event by flushing receives to unblock rpoll */
		ibv_req_notify_cq(rs->cm_id->recv_cq, 0);
		ucma_shutdown(rs->cm_id);
	}

	return ret;
}