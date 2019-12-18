#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct rsocket {int state; int opts; int fd_flags; scalar_t__ err; TYPE_7__* cm_id; int /*<<< orphan*/  retries; int /*<<< orphan*/ * optval; int /*<<< orphan*/  optlen; } ;
struct rs_conn_private_data {int dummy; } ;
struct rs_conn_data {int version; } ;
struct rdma_conn_param {int flow_control; int retry_count; int rnr_retry_count; int initiator_depth; int /*<<< orphan*/  private_data_len; void* private_data; } ;
struct TYPE_12__ {int /*<<< orphan*/  dst_addr; } ;
struct TYPE_13__ {TYPE_1__ addr; } ;
struct TYPE_18__ {TYPE_6__* channel; TYPE_5__* event; TYPE_2__ route; } ;
struct TYPE_17__ {int /*<<< orphan*/  fd; } ;
struct TYPE_14__ {scalar_t__ private_data; } ;
struct TYPE_15__ {TYPE_3__ conn; } ;
struct TYPE_16__ {TYPE_4__ param; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINPROGRESS ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ ETIMEDOUT ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  RDMA_OPTION_IB ; 
 int /*<<< orphan*/  RDMA_OPTION_IB_PATH ; 
 int /*<<< orphan*/  RS_CONN_RETRIES ; 
 int RS_OPT_MSG_SEND ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct rdma_conn_param*,int /*<<< orphan*/ ,int) ; 
 int rdma_connect (TYPE_7__*,struct rdma_conn_param*) ; 
 int rdma_resolve_addr (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int rdma_resolve_route (TYPE_7__*,int) ; 
 int rdma_set_option (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  rs_accepting 133 
#define  rs_bound 132 
 int /*<<< orphan*/  rs_conn_data_offset (struct rsocket*) ; 
 int rs_connect_error ; 
 void* rs_connect_rdwr ; 
#define  rs_connecting 131 
 int rs_create_ep (struct rsocket*) ; 
 int /*<<< orphan*/  rs_format_conn_data (struct rsocket*,struct rs_conn_data*) ; 
#define  rs_init 130 
#define  rs_resolving_addr 129 
#define  rs_resolving_route 128 
 int /*<<< orphan*/  rs_save_conn_data (struct rsocket*,struct rs_conn_data*) ; 
 int ucma_complete (TYPE_7__*) ; 

__attribute__((used)) static int rs_do_connect(struct rsocket *rs)
{
	struct rdma_conn_param param;
	struct rs_conn_private_data cdata;
	struct rs_conn_data *creq, *cresp;
	int to, ret;

	switch (rs->state) {
	case rs_init:
	case rs_bound:
resolve_addr:
		to = 1000 << rs->retries++;
		ret = rdma_resolve_addr(rs->cm_id, NULL,
					&rs->cm_id->route.addr.dst_addr, to);
		if (!ret)
			goto resolve_route;
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			rs->state = rs_resolving_addr;
		break;
	case rs_resolving_addr:
		ret = ucma_complete(rs->cm_id);
		if (ret) {
			if (errno == ETIMEDOUT && rs->retries <= RS_CONN_RETRIES)
				goto resolve_addr;
			break;
		}

		rs->retries = 0;
resolve_route:
		to = 1000 << rs->retries++;
		if (rs->optval) {
			ret = rdma_set_option(rs->cm_id,  RDMA_OPTION_IB,
					      RDMA_OPTION_IB_PATH, rs->optval,
					      rs->optlen);
			free(rs->optval);
			rs->optval = NULL;
			if (!ret) {
				rs->state = rs_resolving_route;
				goto resolving_route;
			}
		} else {
			ret = rdma_resolve_route(rs->cm_id, to);
			if (!ret)
				goto do_connect;
		}
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			rs->state = rs_resolving_route;
		break;
	case rs_resolving_route:
resolving_route:
		ret = ucma_complete(rs->cm_id);
		if (ret) {
			if (errno == ETIMEDOUT && rs->retries <= RS_CONN_RETRIES)
				goto resolve_route;
			break;
		}
do_connect:
		ret = rs_create_ep(rs);
		if (ret)
			break;

		memset(&param, 0, sizeof param);
		creq = (void *) &cdata + rs_conn_data_offset(rs);
		rs_format_conn_data(rs, creq);
		param.private_data = (void *) creq - rs_conn_data_offset(rs);
		param.private_data_len = sizeof(*creq) + rs_conn_data_offset(rs);
		param.flow_control = 1;
		param.retry_count = 7;
		param.rnr_retry_count = 7;
		/* work-around: iWarp issues RDMA read during connection */
		if (rs->opts & RS_OPT_MSG_SEND)
			param.initiator_depth = 1;
		rs->retries = 0;

		ret = rdma_connect(rs->cm_id, &param);
		if (!ret)
			goto connected;
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			rs->state = rs_connecting;
		break;
	case rs_connecting:
		ret = ucma_complete(rs->cm_id);
		if (ret)
			break;
connected:
		cresp = (struct rs_conn_data *) rs->cm_id->event->param.conn.private_data;
		if (cresp->version != 1) {
			ret = ERR(ENOTSUP);
			break;
		}

		rs_save_conn_data(rs, cresp);
		rs->state = rs_connect_rdwr;
		break;
	case rs_accepting:
		if (!(rs->fd_flags & O_NONBLOCK))
			fcntl(rs->cm_id->channel->fd, F_SETFL, 0);

		ret = ucma_complete(rs->cm_id);
		if (ret)
			break;

		rs->state = rs_connect_rdwr;
		break;
	default:
		ret = ERR(EINVAL);
		break;
	}

	if (ret) {
		if (errno == EAGAIN || errno == EWOULDBLOCK) {
			errno = EINPROGRESS;
		} else {
			rs->state = rs_connect_error;
			rs->err = errno;
		}
	}
	return ret;
}