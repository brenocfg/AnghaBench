#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  immediate_data; int /*<<< orphan*/  first_burst_length; int /*<<< orphan*/  max_burst_length; int /*<<< orphan*/  max_send_data_segment_length; int /*<<< orphan*/  max_recv_data_segment_length; int /*<<< orphan*/  statsn; int /*<<< orphan*/  cmdsn; void* data_digest; void* header_digest; int /*<<< orphan*/  portal_group_tag; int /*<<< orphan*/  socket; int /*<<< orphan*/  connection_id; int /*<<< orphan*/  offload; int /*<<< orphan*/  target_name; int /*<<< orphan*/  initiator_isid; int /*<<< orphan*/  initiator_alias; int /*<<< orphan*/  initiator_addr; int /*<<< orphan*/  initiator_name; } ;
struct TYPE_10__ {TYPE_4__ handoff; } ;
struct ctl_iscsi {scalar_t__ status; int /*<<< orphan*/  error_str; TYPE_5__ data; int /*<<< orphan*/  type; } ;
struct connection {scalar_t__ conn_header_digest; scalar_t__ conn_data_digest; int /*<<< orphan*/  conn_immediate_data; int /*<<< orphan*/  conn_first_burst_length; int /*<<< orphan*/  conn_max_burst_length; int /*<<< orphan*/  conn_max_send_data_segment_length; int /*<<< orphan*/  conn_max_recv_data_segment_length; int /*<<< orphan*/  conn_statsn; int /*<<< orphan*/  conn_cmdsn; TYPE_3__* conn_portal; int /*<<< orphan*/  conn_socket; TYPE_1__* conn_target; int /*<<< orphan*/  conn_initiator_isid; int /*<<< orphan*/ * conn_initiator_alias; int /*<<< orphan*/ * conn_initiator_addr; int /*<<< orphan*/ * conn_initiator_name; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_8__ {TYPE_2__* p_portal_group; } ;
struct TYPE_7__ {int /*<<< orphan*/  pg_tag; int /*<<< orphan*/ * pg_offload; } ;
struct TYPE_6__ {int /*<<< orphan*/ * t_name; } ;

/* Variables and functions */
 scalar_t__ CONN_DIGEST_CRC32C ; 
 int /*<<< orphan*/  CTL_ISCSI ; 
 void* CTL_ISCSI_DIGEST_CRC32C ; 
 int /*<<< orphan*/  CTL_ISCSI_HANDOFF ; 
 scalar_t__ CTL_ISCSI_OK ; 
 int /*<<< orphan*/  bzero (struct ctl_iscsi*,int) ; 
 int /*<<< orphan*/  ctl_fd ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ctl_iscsi*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  log_errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ proxy_mode ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void
kernel_handoff(struct connection *conn)
{
	struct ctl_iscsi req;

	bzero(&req, sizeof(req));

	req.type = CTL_ISCSI_HANDOFF;
	strlcpy(req.data.handoff.initiator_name,
	    conn->conn_initiator_name, sizeof(req.data.handoff.initiator_name));
	strlcpy(req.data.handoff.initiator_addr,
	    conn->conn_initiator_addr, sizeof(req.data.handoff.initiator_addr));
	if (conn->conn_initiator_alias != NULL) {
		strlcpy(req.data.handoff.initiator_alias,
		    conn->conn_initiator_alias, sizeof(req.data.handoff.initiator_alias));
	}
	memcpy(req.data.handoff.initiator_isid, conn->conn_initiator_isid,
	    sizeof(req.data.handoff.initiator_isid));
	strlcpy(req.data.handoff.target_name,
	    conn->conn_target->t_name, sizeof(req.data.handoff.target_name));
	if (conn->conn_portal->p_portal_group->pg_offload != NULL) {
		strlcpy(req.data.handoff.offload,
		    conn->conn_portal->p_portal_group->pg_offload,
		    sizeof(req.data.handoff.offload));
	}
#ifdef ICL_KERNEL_PROXY
	if (proxy_mode)
		req.data.handoff.connection_id = conn->conn_socket;
	else
		req.data.handoff.socket = conn->conn_socket;
#else
	req.data.handoff.socket = conn->conn_socket;
#endif
	req.data.handoff.portal_group_tag =
	    conn->conn_portal->p_portal_group->pg_tag;
	if (conn->conn_header_digest == CONN_DIGEST_CRC32C)
		req.data.handoff.header_digest = CTL_ISCSI_DIGEST_CRC32C;
	if (conn->conn_data_digest == CONN_DIGEST_CRC32C)
		req.data.handoff.data_digest = CTL_ISCSI_DIGEST_CRC32C;
	req.data.handoff.cmdsn = conn->conn_cmdsn;
	req.data.handoff.statsn = conn->conn_statsn;
	req.data.handoff.max_recv_data_segment_length =
	    conn->conn_max_recv_data_segment_length;
	req.data.handoff.max_send_data_segment_length =
	    conn->conn_max_send_data_segment_length;
	req.data.handoff.max_burst_length = conn->conn_max_burst_length;
	req.data.handoff.first_burst_length = conn->conn_first_burst_length;
	req.data.handoff.immediate_data = conn->conn_immediate_data;

	if (ioctl(ctl_fd, CTL_ISCSI, &req) == -1) {
		log_err(1, "error issuing CTL_ISCSI ioctl; "
		    "dropping connection");
	}

	if (req.status != CTL_ISCSI_OK) {
		log_errx(1, "error returned from CTL iSCSI handoff request: "
		    "%s; dropping connection", req.error_str);
	}
}