#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rs_svc_msg {int cmd; int /*<<< orphan*/  status; TYPE_2__* rs; } ;
struct rs_svc {size_t cnt; int /*<<< orphan*/ * sock; TYPE_1__* contexts; } ;
struct TYPE_5__ {int /*<<< orphan*/  opts; int /*<<< orphan*/  udp_sock; } ;
struct TYPE_4__ {int /*<<< orphan*/  revents; int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  RS_OPT_SVC_ACTIVE ; 
#define  RS_SVC_ADD_DGRAM 130 
#define  RS_SVC_NOOP 129 
#define  RS_SVC_REM_DGRAM 128 
 int /*<<< orphan*/  read_all (int /*<<< orphan*/ ,struct rs_svc_msg*,int) ; 
 int /*<<< orphan*/  rs_svc_add_rs (struct rs_svc*,TYPE_2__*) ; 
 int /*<<< orphan*/  rs_svc_rm_rs (struct rs_svc*,TYPE_2__*) ; 
 TYPE_1__* udp_svc_fds ; 
 int /*<<< orphan*/  write_all (int /*<<< orphan*/ ,struct rs_svc_msg*,int) ; 

__attribute__((used)) static void udp_svc_process_sock(struct rs_svc *svc)
{
	struct rs_svc_msg msg;

	read_all(svc->sock[1], &msg, sizeof msg);
	switch (msg.cmd) {
	case RS_SVC_ADD_DGRAM:
		msg.status = rs_svc_add_rs(svc, msg.rs);
		if (!msg.status) {
			msg.rs->opts |= RS_OPT_SVC_ACTIVE;
			udp_svc_fds = svc->contexts;
			udp_svc_fds[svc->cnt].fd = msg.rs->udp_sock;
			udp_svc_fds[svc->cnt].events = POLLIN;
			udp_svc_fds[svc->cnt].revents = 0;
		}
		break;
	case RS_SVC_REM_DGRAM:
		msg.status = rs_svc_rm_rs(svc, msg.rs);
		if (!msg.status)
			msg.rs->opts &= ~RS_OPT_SVC_ACTIVE;
		break;
	case RS_SVC_NOOP:
		msg.status = 0;
		break;
	default:
		break;
	}

	write_all(svc->sock[1], &msg, sizeof msg);
}