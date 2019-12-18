#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_5__ {int /*<<< orphan*/  token; } ;
struct ng_mesg {scalar_t__ data; TYPE_1__ header; } ;
struct TYPE_6__ {int ident; int lcid; int linktype; int result; scalar_t__ status; int /*<<< orphan*/  bdaddr; } ;
typedef  TYPE_2__ ng_l2cap_l2ca_con_rsp_ip ;
typedef  TYPE_3__* ng_btsocket_l2cap_rtentry_p ;
typedef  int /*<<< orphan*/  bdaddr_p ;
struct TYPE_7__ {int /*<<< orphan*/ * hook; } ;

/* Variables and functions */
 int ENETDOWN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGM_L2CAP_COOKIE ; 
 int /*<<< orphan*/  NGM_L2CAP_L2CA_CON_RSP ; 
 scalar_t__ NG_HOOK_NOT_VALID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_MKMESSAGE (struct ng_mesg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_SEND_MSG_HOOK (int,int /*<<< orphan*/ ,struct ng_mesg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ng_btsocket_l2cap_node ; 

__attribute__((used)) static int
ng_btsocket_l2cap_send_l2ca_con_rsp_req(u_int32_t token,
		ng_btsocket_l2cap_rtentry_p rt, bdaddr_p dst, int ident, 
					int lcid, int result, int linktype)
{
	struct ng_mesg			*msg = NULL;
	ng_l2cap_l2ca_con_rsp_ip	*ip = NULL;
	int				 error = 0;

	if (rt == NULL || rt->hook == NULL || NG_HOOK_NOT_VALID(rt->hook))
		return (ENETDOWN); 

	NG_MKMESSAGE(msg, NGM_L2CAP_COOKIE, NGM_L2CAP_L2CA_CON_RSP,
		sizeof(*ip), M_NOWAIT);
	if (msg == NULL)
		return (ENOMEM);

	msg->header.token = token;

	ip = (ng_l2cap_l2ca_con_rsp_ip *)(msg->data);
	bcopy(dst, &ip->bdaddr, sizeof(ip->bdaddr));
	ip->ident = ident;
	ip->lcid = lcid;
	ip->linktype = linktype;
	ip->result = result;
	ip->status = 0;

	NG_SEND_MSG_HOOK(error, ng_btsocket_l2cap_node, msg, rt->hook, 0);

	return (error);
}