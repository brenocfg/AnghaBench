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
typedef  int /*<<< orphan*/  uint8_t ;
struct ibv_query_port_resp {int /*<<< orphan*/  link_layer; int /*<<< orphan*/  phys_state; int /*<<< orphan*/  active_speed; int /*<<< orphan*/  active_width; int /*<<< orphan*/  init_type_reply; int /*<<< orphan*/  subnet_timeout; int /*<<< orphan*/  sm_sl; int /*<<< orphan*/  max_vl_num; int /*<<< orphan*/  lmc; int /*<<< orphan*/  sm_lid; int /*<<< orphan*/  lid; int /*<<< orphan*/  pkey_tbl_len; int /*<<< orphan*/  qkey_viol_cntr; int /*<<< orphan*/  bad_pkey_cntr; int /*<<< orphan*/  max_msg_sz; int /*<<< orphan*/  port_cap_flags; int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  active_mtu; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  state; } ;
struct ibv_query_port {int /*<<< orphan*/  reserved; int /*<<< orphan*/  port_num; } ;
struct ibv_port_attr {int /*<<< orphan*/  link_layer; int /*<<< orphan*/  phys_state; int /*<<< orphan*/  active_speed; int /*<<< orphan*/  active_width; int /*<<< orphan*/  init_type_reply; int /*<<< orphan*/  subnet_timeout; int /*<<< orphan*/  sm_sl; int /*<<< orphan*/  max_vl_num; int /*<<< orphan*/  lmc; int /*<<< orphan*/  sm_lid; int /*<<< orphan*/  lid; int /*<<< orphan*/  pkey_tbl_len; int /*<<< orphan*/  qkey_viol_cntr; int /*<<< orphan*/  bad_pkey_cntr; int /*<<< orphan*/  max_msg_sz; int /*<<< orphan*/  port_cap_flags; int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  active_mtu; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  state; } ;
struct ibv_context {int /*<<< orphan*/  cmd_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_INIT_CMD_RESP (struct ibv_query_port*,size_t,int /*<<< orphan*/ ,struct ibv_query_port_resp*,int) ; 
 int /*<<< orphan*/  QUERY_PORT ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (struct ibv_query_port_resp*,int) ; 
 int errno ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t write (int /*<<< orphan*/ ,struct ibv_query_port*,size_t) ; 

int ibv_cmd_query_port(struct ibv_context *context, uint8_t port_num,
		       struct ibv_port_attr *port_attr,
		       struct ibv_query_port *cmd, size_t cmd_size)
{
	struct ibv_query_port_resp resp;

	IBV_INIT_CMD_RESP(cmd, cmd_size, QUERY_PORT, &resp, sizeof resp);
	cmd->port_num = port_num;
	memset(cmd->reserved, 0, sizeof cmd->reserved);

	if (write(context->cmd_fd, cmd, cmd_size) != cmd_size)
		return errno;

	(void) VALGRIND_MAKE_MEM_DEFINED(&resp, sizeof resp);

	port_attr->state      	   = resp.state;
	port_attr->max_mtu         = resp.max_mtu;
	port_attr->active_mtu      = resp.active_mtu;
	port_attr->gid_tbl_len     = resp.gid_tbl_len;
	port_attr->port_cap_flags  = resp.port_cap_flags;
	port_attr->max_msg_sz      = resp.max_msg_sz;
	port_attr->bad_pkey_cntr   = resp.bad_pkey_cntr;
	port_attr->qkey_viol_cntr  = resp.qkey_viol_cntr;
	port_attr->pkey_tbl_len    = resp.pkey_tbl_len;
	port_attr->lid 	      	   = resp.lid;
	port_attr->sm_lid 	   = resp.sm_lid;
	port_attr->lmc 	      	   = resp.lmc;
	port_attr->max_vl_num      = resp.max_vl_num;
	port_attr->sm_sl      	   = resp.sm_sl;
	port_attr->subnet_timeout  = resp.subnet_timeout;
	port_attr->init_type_reply = resp.init_type_reply;
	port_attr->active_width    = resp.active_width;
	port_attr->active_speed    = resp.active_speed;
	port_attr->phys_state      = resp.phys_state;
	port_attr->link_layer      = resp.link_layer;

	return 0;
}