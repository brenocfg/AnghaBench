#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {void* s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;
struct qlnxr_qp {int /*<<< orphan*/  ecore_qp; int /*<<< orphan*/  rq_psn; } ;
struct qlnxr_iw_ep {struct iw_cm_id* cm_id; struct qlnxr_qp* qp; struct qlnxr_dev* dev; } ;
struct qlnxr_dev {int /*<<< orphan*/  rdma_ctx; TYPE_4__* ha; int /*<<< orphan*/  qpidr; } ;
struct iw_cm_id {int /*<<< orphan*/  (* rem_ref ) (struct iw_cm_id*) ;int /*<<< orphan*/  (* add_ref ) (struct iw_cm_id*) ;int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; int /*<<< orphan*/  device; } ;
struct iw_cm_conn_param {int /*<<< orphan*/  private_data_len; int /*<<< orphan*/  private_data; int /*<<< orphan*/  ird; int /*<<< orphan*/  ord; int /*<<< orphan*/  qpn; } ;
struct TYPE_9__ {int /*<<< orphan*/  private_data_len; int /*<<< orphan*/  private_data; int /*<<< orphan*/  ird; int /*<<< orphan*/  ord; scalar_t__ vlan; void* local_port; void* remote_port; void** local_ip; void** remote_ip; int /*<<< orphan*/  ip_version; } ;
struct ecore_iwarp_connect_out {int /*<<< orphan*/  local_mac_addr; int /*<<< orphan*/  qp; TYPE_3__ cm_info; scalar_t__ remote_mac_addr; scalar_t__ mss; struct qlnxr_iw_ep* cb_context; int /*<<< orphan*/  event_cb; } ;
struct ecore_iwarp_connect_in {int /*<<< orphan*/  local_mac_addr; int /*<<< orphan*/  qp; TYPE_3__ cm_info; scalar_t__ remote_mac_addr; scalar_t__ mss; struct qlnxr_iw_ep* cb_context; int /*<<< orphan*/  event_cb; } ;
struct TYPE_10__ {int /*<<< orphan*/  primary_mac; TYPE_2__* ifp; } ;
typedef  TYPE_4__ qlnx_host_t ;
struct TYPE_8__ {int if_drv_flags; scalar_t__ if_mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_TCP_IPV4 ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  NIPQUAD (void*) ; 
 int /*<<< orphan*/  QL_DPRINT11 (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (TYPE_4__*,char*,...) ; 
 int ecore_iwarp_connect (int /*<<< orphan*/ ,struct ecore_iwarp_connect_out*,struct ecore_iwarp_connect_out*) ; 
 struct qlnxr_dev* get_qlnxr_dev (int /*<<< orphan*/ ) ; 
 struct qlnxr_qp* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qlnxr_iw_ep*) ; 
 struct qlnxr_iw_ep* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ecore_iwarp_connect_out*,int /*<<< orphan*/ ,int) ; 
 void* ntohl (void*) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 
 int qlnxr_addr4_resolve (struct qlnxr_dev*,struct sockaddr_in*,struct sockaddr_in*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlnxr_iw_event_handler ; 
 int /*<<< orphan*/  stub1 (struct iw_cm_id*) ; 
 int /*<<< orphan*/  stub2 (struct iw_cm_id*) ; 

int
qlnxr_iw_connect(struct iw_cm_id *cm_id, struct iw_cm_conn_param *conn_param)
{
	struct qlnxr_dev *dev;
	struct ecore_iwarp_connect_out out_params;
	struct ecore_iwarp_connect_in in_params;
	struct qlnxr_iw_ep *ep;
	struct qlnxr_qp *qp;
	struct sockaddr_in *laddr;
	struct sockaddr_in *raddr;
	int rc = 0;
	qlnx_host_t	*ha;

	dev = get_qlnxr_dev((cm_id->device));
	ha = dev->ha;

	QL_DPRINT12(ha, "[cm_id, conn_param] = [%p, %p] "
		"enter \n", cm_id, conn_param);

	if (!(ha->ifp->if_drv_flags & IFF_DRV_RUNNING))
		return -EINVAL;

	qp = idr_find(&dev->qpidr, conn_param->qpn);

	laddr = (struct sockaddr_in *)&cm_id->local_addr;
	raddr = (struct sockaddr_in *)&cm_id->remote_addr;

	QL_DPRINT12(ha,
		"local = [%d.%d.%d.%d, %d] remote = [%d.%d.%d.%d, %d]\n",
		NIPQUAD((laddr->sin_addr.s_addr)), laddr->sin_port,
		NIPQUAD((raddr->sin_addr.s_addr)), raddr->sin_port);

	ep = kzalloc(sizeof(*ep), GFP_KERNEL);
	if (!ep) {
		QL_DPRINT11(ha, "struct qlnxr_iw_ep "
			"alloc memory failed\n");
		return -ENOMEM;
	}

	ep->dev = dev;
	ep->qp = qp;
	cm_id->add_ref(cm_id);
	ep->cm_id = cm_id;

	memset(&in_params, 0, sizeof (struct ecore_iwarp_connect_in));
	memset(&out_params, 0, sizeof (struct ecore_iwarp_connect_out));

	in_params.event_cb = qlnxr_iw_event_handler;
	in_params.cb_context = ep;

	in_params.cm_info.ip_version = ECORE_TCP_IPV4;

	in_params.cm_info.remote_ip[0] = ntohl(raddr->sin_addr.s_addr);
	in_params.cm_info.local_ip[0] = ntohl(laddr->sin_addr.s_addr);
	in_params.cm_info.remote_port = ntohs(raddr->sin_port);
	in_params.cm_info.local_port = ntohs(laddr->sin_port);
	in_params.cm_info.vlan = 0;
	in_params.mss = dev->ha->ifp->if_mtu - 40;

	QL_DPRINT12(ha, "remote_ip = [%d.%d.%d.%d] "
		"local_ip = [%d.%d.%d.%d] remote_port = %d local_port = %d "
		"vlan = %d\n",
		NIPQUAD((in_params.cm_info.remote_ip[0])),
		NIPQUAD((in_params.cm_info.local_ip[0])),
		in_params.cm_info.remote_port, in_params.cm_info.local_port,
		in_params.cm_info.vlan);

	rc = qlnxr_addr4_resolve(dev, laddr, raddr, (u8 *)in_params.remote_mac_addr);

	if (rc) {
		QL_DPRINT11(ha, "qlnxr_addr4_resolve failed\n");
		goto err;
	}

	QL_DPRINT12(ha, "ord = %d ird=%d private_data=%p"
		" private_data_len=%d rq_psn=%d\n",
		conn_param->ord, conn_param->ird, conn_param->private_data,
		conn_param->private_data_len, qp->rq_psn);

	in_params.cm_info.ord = conn_param->ord;
	in_params.cm_info.ird = conn_param->ird;
	in_params.cm_info.private_data = conn_param->private_data;
	in_params.cm_info.private_data_len = conn_param->private_data_len;
	in_params.qp = qp->ecore_qp;

	memcpy(in_params.local_mac_addr, dev->ha->primary_mac, ETH_ALEN);

	rc = ecore_iwarp_connect(dev->rdma_ctx, &in_params, &out_params);

	if (rc) {
		QL_DPRINT12(ha, "ecore_iwarp_connect failed\n");
		goto err;
	}

	QL_DPRINT12(ha, "exit\n");

	return rc;

err:
	cm_id->rem_ref(cm_id);
	kfree(ep);

	QL_DPRINT12(ha, "exit [%d]\n", rc);
	return rc;
}