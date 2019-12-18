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
struct TYPE_2__ {int typecookie; int /*<<< orphan*/  cmd; } ;
struct ng_mesg {TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  ng_l2cap_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;

/* Variables and functions */
 struct ng_mesg* NGI_MSG (int /*<<< orphan*/ ) ; 
#define  NGM_L2CAP_COOKIE 141 
#define  NGM_L2CAP_L2CA_CFG 140 
#define  NGM_L2CAP_L2CA_CFG_RSP 139 
#define  NGM_L2CAP_L2CA_CON 138 
#define  NGM_L2CAP_L2CA_CON_RSP 137 
#define  NGM_L2CAP_L2CA_DISCON 136 
#define  NGM_L2CAP_L2CA_ENABLE_CLT 135 
#define  NGM_L2CAP_L2CA_GET_INFO 134 
#define  NGM_L2CAP_L2CA_GRP_ADD_MEMBER 133 
#define  NGM_L2CAP_L2CA_GRP_CLOSE 132 
#define  NGM_L2CAP_L2CA_GRP_CREATE 131 
#define  NGM_L2CAP_L2CA_GRP_MEMBERSHIP 130 
#define  NGM_L2CAP_L2CA_GRP_REM_MEMBER 129 
#define  NGM_L2CAP_L2CA_PING 128 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int ng_l2cap_default_rcvmsg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ng_l2cap_l2ca_cfg_req (int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int ng_l2cap_l2ca_cfg_rsp_req (int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int ng_l2cap_l2ca_con_req (int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int ng_l2cap_l2ca_con_rsp_req (int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int ng_l2cap_l2ca_discon_req (int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int ng_l2cap_l2ca_enable_clt (int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int ng_l2cap_l2ca_get_info_req (int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int ng_l2cap_l2ca_grp_add_member_req (int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int ng_l2cap_l2ca_grp_close (int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int ng_l2cap_l2ca_grp_create (int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int ng_l2cap_l2ca_grp_get_members (int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int ng_l2cap_l2ca_grp_rem_member (int /*<<< orphan*/ ,struct ng_mesg*) ; 
 int ng_l2cap_l2ca_ping_req (int /*<<< orphan*/ ,struct ng_mesg*) ; 

__attribute__((used)) static int
ng_l2cap_upper_rcvmsg(node_p node, item_p item, hook_p lasthook)
{
	ng_l2cap_p	 l2cap = (ng_l2cap_p) NG_NODE_PRIVATE(node);
	struct ng_mesg	*msg = NGI_MSG(item); /* item still has message */
	int		 error = 0;

	switch (msg->header.typecookie) {
	case NGM_L2CAP_COOKIE:
		switch (msg->header.cmd) {
		/* L2CA_Connect */
		case NGM_L2CAP_L2CA_CON:
			error = ng_l2cap_l2ca_con_req(l2cap, msg);
			break;

		/* L2CA_ConnectRsp */
		case NGM_L2CAP_L2CA_CON_RSP:
			error = ng_l2cap_l2ca_con_rsp_req(l2cap, msg);
			break;

		/* L2CA_Config */
		case NGM_L2CAP_L2CA_CFG:
			error = ng_l2cap_l2ca_cfg_req(l2cap, msg);
			break;

		/* L2CA_ConfigRsp */
		case NGM_L2CAP_L2CA_CFG_RSP:
			error = ng_l2cap_l2ca_cfg_rsp_req(l2cap, msg);
			break;

		/* L2CA_Disconnect */
		case NGM_L2CAP_L2CA_DISCON:
			error = ng_l2cap_l2ca_discon_req(l2cap, msg);
			break;

		/* L2CA_GroupCreate */
		case NGM_L2CAP_L2CA_GRP_CREATE:
			error = ng_l2cap_l2ca_grp_create(l2cap, msg);
			break;

		/* L2CA_GroupClose */
		case NGM_L2CAP_L2CA_GRP_CLOSE:
			error = ng_l2cap_l2ca_grp_close(l2cap, msg);
			break;

		/* L2CA_GroupAddMember */
		case NGM_L2CAP_L2CA_GRP_ADD_MEMBER:
			error = ng_l2cap_l2ca_grp_add_member_req(l2cap, msg);
			break;

		/* L2CA_GroupDeleteMember */
		case NGM_L2CAP_L2CA_GRP_REM_MEMBER:
			error = ng_l2cap_l2ca_grp_rem_member(l2cap, msg);
			break;

		/* L2CA_GroupMembership */
		case NGM_L2CAP_L2CA_GRP_MEMBERSHIP:
			error = ng_l2cap_l2ca_grp_get_members(l2cap, msg);
			break;

		/* L2CA_Ping */
		case NGM_L2CAP_L2CA_PING:
			error = ng_l2cap_l2ca_ping_req(l2cap, msg);
			break;

		/* L2CA_GetInfo */
		case NGM_L2CAP_L2CA_GET_INFO:
			error = ng_l2cap_l2ca_get_info_req(l2cap, msg);
			break;

		/* L2CA_EnableCLT */
		case NGM_L2CAP_L2CA_ENABLE_CLT:
			error = ng_l2cap_l2ca_enable_clt(l2cap, msg);
			break;

		default:
			return (ng_l2cap_default_rcvmsg(node, item, lasthook));
			/* NOT REACHED */
		}
		break;

	default:
		return (ng_l2cap_default_rcvmsg(node, item, lasthook));
		/* NOT REACHED */
	}

	NG_FREE_ITEM(item);

	return (error);
}