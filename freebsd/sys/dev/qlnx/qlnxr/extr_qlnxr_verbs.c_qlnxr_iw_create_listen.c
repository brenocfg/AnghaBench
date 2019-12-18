#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_2__ sin_addr; } ;
struct qlnxr_iw_listener {int backlog; int /*<<< orphan*/  ecore_handle; struct iw_cm_id* cm_id; struct qlnxr_dev* dev; } ;
struct qlnxr_dev {int /*<<< orphan*/  rdma_ctx; TYPE_3__* ha; } ;
struct iw_cm_id {int /*<<< orphan*/  (* rem_ref ) (struct iw_cm_id*) ;struct qlnxr_iw_listener* provider_data; int /*<<< orphan*/  (* add_ref ) (struct iw_cm_id*) ;int /*<<< orphan*/  local_addr; int /*<<< orphan*/  device; } ;
struct ecore_iwarp_listen_out {int max_backlog; int /*<<< orphan*/  handle; int /*<<< orphan*/  port; scalar_t__ vlan; int /*<<< orphan*/ * ip_addr; int /*<<< orphan*/  ip_version; int /*<<< orphan*/  event_cb; struct qlnxr_iw_listener* cb_context; } ;
struct ecore_iwarp_listen_in {int max_backlog; int /*<<< orphan*/  handle; int /*<<< orphan*/  port; scalar_t__ vlan; int /*<<< orphan*/ * ip_addr; int /*<<< orphan*/  ip_version; int /*<<< orphan*/  event_cb; struct qlnxr_iw_listener* cb_context; } ;
struct TYPE_8__ {TYPE_1__* ifp; } ;
typedef  TYPE_3__ qlnx_host_t ;
struct TYPE_6__ {int if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_TCP_IPV4 ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  NIPQUAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QL_DPRINT11 (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  QL_DPRINT12 (TYPE_3__*,char*,...) ; 
 int ecore_iwarp_create_listen (int /*<<< orphan*/ ,struct ecore_iwarp_listen_out*,struct ecore_iwarp_listen_out*) ; 
 struct qlnxr_dev* get_qlnxr_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qlnxr_iw_listener*) ; 
 struct qlnxr_iw_listener* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ecore_iwarp_listen_out*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlnxr_iw_event_handler ; 
 int /*<<< orphan*/  stub1 (struct iw_cm_id*) ; 
 int /*<<< orphan*/  stub2 (struct iw_cm_id*) ; 

int
qlnxr_iw_create_listen(struct iw_cm_id *cm_id, int backlog)
{
	struct qlnxr_dev *dev;
	struct qlnxr_iw_listener *listener;
	struct ecore_iwarp_listen_in iparams;
	struct ecore_iwarp_listen_out oparams;
	struct sockaddr_in *laddr;
	qlnx_host_t	*ha;
	int rc;

	dev = get_qlnxr_dev((cm_id->device));
	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");

	if (!(ha->ifp->if_drv_flags & IFF_DRV_RUNNING))
		return -EINVAL;

	laddr = (struct sockaddr_in *)&cm_id->local_addr;

	listener = kzalloc(sizeof(*listener), GFP_KERNEL);

	if (listener == NULL) {
		QL_DPRINT11(ha, "listener memory alloc failed\n");
		return -ENOMEM;
	}

	listener->dev = dev;
	cm_id->add_ref(cm_id);
	listener->cm_id = cm_id;
	listener->backlog = backlog;

	memset(&iparams, 0, sizeof (struct ecore_iwarp_listen_in));
	memset(&oparams, 0, sizeof (struct ecore_iwarp_listen_out));

	iparams.cb_context = listener;
	iparams.event_cb = qlnxr_iw_event_handler;
	iparams.max_backlog = backlog;

	iparams.ip_version = ECORE_TCP_IPV4;

	iparams.ip_addr[0] = ntohl(laddr->sin_addr.s_addr);
	iparams.port = ntohs(laddr->sin_port);
	iparams.vlan = 0;

	QL_DPRINT12(ha, "[%d.%d.%d.%d, %d] iparamsport=%d\n",
		NIPQUAD((laddr->sin_addr.s_addr)),
		laddr->sin_port, iparams.port);

	rc = ecore_iwarp_create_listen(dev->rdma_ctx, &iparams, &oparams);
	if (rc) {
		QL_DPRINT11(ha,
			"ecore_iwarp_create_listen failed rc = %d\n", rc);
		goto err;
	}

	listener->ecore_handle = oparams.handle;
	cm_id->provider_data = listener;

	QL_DPRINT12(ha, "exit\n");
	return rc;

err:
	cm_id->rem_ref(cm_id);
	kfree(listener);

	QL_DPRINT12(ha, "exit [%d]\n", rc);
	return rc;
}