#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rs_svc_msg {int cmd; int /*<<< orphan*/  status; TYPE_1__* rs; } ;
struct rs_svc {size_t cnt; int /*<<< orphan*/ * sock; scalar_t__* contexts; } ;
struct TYPE_4__ {scalar_t__ keepalive_time; int /*<<< orphan*/  opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  RS_OPT_SVC_ACTIVE ; 
#define  RS_SVC_ADD_KEEPALIVE 131 
#define  RS_SVC_MOD_KEEPALIVE 130 
#define  RS_SVC_NOOP 129 
#define  RS_SVC_REM_KEEPALIVE 128 
 int /*<<< orphan*/  read_all (int /*<<< orphan*/ ,struct rs_svc_msg*,int) ; 
 scalar_t__ rs_get_time () ; 
 int /*<<< orphan*/  rs_svc_add_rs (struct rs_svc*,TYPE_1__*) ; 
 int rs_svc_index (struct rs_svc*,TYPE_1__*) ; 
 int /*<<< orphan*/  rs_svc_rm_rs (struct rs_svc*,TYPE_1__*) ; 
 scalar_t__* tcp_svc_timeouts ; 
 int /*<<< orphan*/  write_all (int /*<<< orphan*/ ,struct rs_svc_msg*,int) ; 

__attribute__((used)) static void tcp_svc_process_sock(struct rs_svc *svc)
{
	struct rs_svc_msg msg;
	int i;

	read_all(svc->sock[1], &msg, sizeof msg);
	switch (msg.cmd) {
	case RS_SVC_ADD_KEEPALIVE:
		msg.status = rs_svc_add_rs(svc, msg.rs);
		if (!msg.status) {
			msg.rs->opts |= RS_OPT_SVC_ACTIVE;
			tcp_svc_timeouts = svc->contexts;
			tcp_svc_timeouts[svc->cnt] = rs_get_time() +
						     msg.rs->keepalive_time;
		}
		break;
	case RS_SVC_REM_KEEPALIVE:
		msg.status = rs_svc_rm_rs(svc, msg.rs);
		if (!msg.status)
			msg.rs->opts &= ~RS_OPT_SVC_ACTIVE;
		break;
	case RS_SVC_MOD_KEEPALIVE:
		i = rs_svc_index(svc, msg.rs);
		if (i >= 0) {
			tcp_svc_timeouts[i] = rs_get_time() + msg.rs->keepalive_time;
			msg.status = 0;
		} else {
			msg.status = EBADF;
		}
		break;
	case RS_SVC_NOOP:
		msg.status = 0;
		break;
	default:
		break;
	}
	write_all(svc->sock[1], &msg, sizeof msg);
}