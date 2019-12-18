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
struct rdma_id_private {int dummy; } ;
struct rdma_bind_list {int dummy; } ;
typedef  struct rdma_id_private net_device ;
struct ib_cm_id {int /*<<< orphan*/  service_id; } ;
struct ib_cm_event {int dummy; } ;
struct cma_req_info {int /*<<< orphan*/  service_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 struct rdma_id_private* ERR_CAST (struct rdma_id_private*) ; 
 struct rdma_id_private* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct rdma_id_private*) ; 
 int /*<<< orphan*/  PTR_ERR (struct rdma_id_private*) ; 
 int /*<<< orphan*/  RDMA_PS_SDP ; 
 struct rdma_id_private* cma_find_listener (struct rdma_bind_list*,struct ib_cm_id*,struct ib_cm_event*,struct cma_req_info*,struct rdma_id_private*) ; 
 struct rdma_id_private* cma_get_net_dev (struct ib_cm_event*,struct cma_req_info*) ; 
 int /*<<< orphan*/  cma_port_from_service_id (int /*<<< orphan*/ ) ; 
 struct rdma_bind_list* cma_ps_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cma_save_req_info (struct ib_cm_event*,struct cma_req_info*) ; 
 int /*<<< orphan*/ * dev_net (struct rdma_id_private*) ; 
 int /*<<< orphan*/  dev_put (struct rdma_id_private*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  rdma_ps_from_service_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rdma_id_private *cma_id_from_event(struct ib_cm_id *cm_id,
						 struct ib_cm_event *ib_event,
						 struct net_device **net_dev)
{
	struct cma_req_info req;
	struct rdma_bind_list *bind_list;
	struct rdma_id_private *id_priv;
	int err;

	err = cma_save_req_info(ib_event, &req);
	if (err)
		return ERR_PTR(err);

	if (rdma_ps_from_service_id(cm_id->service_id) == RDMA_PS_SDP) {
		*net_dev = NULL;
		goto there_is_no_net_dev;
	}

	*net_dev = cma_get_net_dev(ib_event, &req);
	if (IS_ERR(*net_dev)) {
		if (PTR_ERR(*net_dev) == -EAFNOSUPPORT) {
			/* Assuming the protocol is AF_IB */
			*net_dev = NULL;
		} else {
			return ERR_CAST(*net_dev);
		}
	}

there_is_no_net_dev:
	bind_list = cma_ps_find(*net_dev ? dev_net(*net_dev) : &init_net,
				rdma_ps_from_service_id(req.service_id),
				cma_port_from_service_id(req.service_id));
	id_priv = cma_find_listener(bind_list, cm_id, ib_event, &req, *net_dev);
	if (IS_ERR(id_priv) && *net_dev) {
		dev_put(*net_dev);
		*net_dev = NULL;
	}

	return id_priv;
}