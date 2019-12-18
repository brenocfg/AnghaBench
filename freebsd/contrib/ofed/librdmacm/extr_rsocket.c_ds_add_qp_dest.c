#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union socket_addr {int dummy; } socket_addr ;
struct ibv_port_attr {int /*<<< orphan*/  lid; } ;
struct ibv_ah_attr {int /*<<< orphan*/  port_num; int /*<<< orphan*/  dlid; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  ah; int /*<<< orphan*/  qpn; struct ds_qp* qp; } ;
struct ds_qp {TYPE_4__* rs; TYPE_3__ dest; TYPE_2__* cm_id; } ;
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_8__ {int /*<<< orphan*/  dest_map; } ;
struct TYPE_6__ {int /*<<< orphan*/  pd; int /*<<< orphan*/  port_num; int /*<<< orphan*/  verbs; TYPE_1__* qp; } ;
struct TYPE_5__ {int /*<<< orphan*/  qp_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds_compare_addr ; 
 int /*<<< orphan*/  ibv_create_ah (int /*<<< orphan*/ ,struct ibv_ah_attr*) ; 
 int ibv_query_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ibv_port_attr*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,union socket_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ibv_ah_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tsearch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds_add_qp_dest(struct ds_qp *qp, union socket_addr *addr,
			  socklen_t addrlen)
{
	struct ibv_port_attr port_attr;
	struct ibv_ah_attr attr;
	int ret;

	memcpy(&qp->dest.addr, addr, addrlen);
	qp->dest.qp = qp;
	qp->dest.qpn = qp->cm_id->qp->qp_num;

	ret = ibv_query_port(qp->cm_id->verbs, qp->cm_id->port_num, &port_attr);
	if (ret)
		return ret;

	memset(&attr, 0, sizeof attr);
	attr.dlid = port_attr.lid;
	attr.port_num = qp->cm_id->port_num;
	qp->dest.ah = ibv_create_ah(qp->cm_id->pd, &attr);
	if (!qp->dest.ah)
		return ERR(ENOMEM);

	tsearch(&qp->dest.addr, &qp->rs->dest_map, ds_compare_addr);
	return 0;
}