#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {scalar_t__ sa_family; } ;
struct TYPE_5__ {int hoplimit; int /*<<< orphan*/  network; int /*<<< orphan*/  dst_dev_addr; scalar_t__ bound_dev_if; int /*<<< orphan*/  net; } ;
struct rdma_addr {TYPE_2__ dev_addr; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; } ;
struct rdma_route {int num_paths; struct cma_work* path_rec; struct rdma_addr addr; } ;
struct TYPE_4__ {struct rdma_route route; int /*<<< orphan*/  port_num; int /*<<< orphan*/  device; } ;
struct rdma_id_private {int /*<<< orphan*/  tos; TYPE_1__ id; int /*<<< orphan*/  gid_type; } ;
struct net_device {int /*<<< orphan*/  if_mtu; int /*<<< orphan*/  if_index; int /*<<< orphan*/  if_vnet; } ;
struct TYPE_6__ {scalar_t__ status; int /*<<< orphan*/  event; } ;
struct cma_work {scalar_t__ gid_type; int hop_limit; int reversible; int /*<<< orphan*/  work; TYPE_3__ event; int /*<<< orphan*/  new_state; int /*<<< orphan*/  old_state; int /*<<< orphan*/  mtu; int /*<<< orphan*/  packet_life_time; void* packet_life_time_selector; int /*<<< orphan*/  rate; void* rate_selector; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  sl; void* mtu_selector; int /*<<< orphan*/  pkey; int /*<<< orphan*/  dgid; int /*<<< orphan*/  sgid; int /*<<< orphan*/  dmac; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  net; struct rdma_id_private* id; } ;

/* Variables and functions */
 scalar_t__ AF_IB ; 
 int /*<<< orphan*/  CMA_IBOE_PACKET_LIFETIME ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* IB_SA_EQ ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDMA_CM_EVENT_ROUTE_RESOLVED ; 
 int /*<<< orphan*/  RDMA_CM_ROUTE_QUERY ; 
 int /*<<< orphan*/  RDMA_CM_ROUTE_RESOLVED ; 
 scalar_t__ cma_route_gid_type (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cma_work_handler ; 
 int /*<<< orphan*/  cma_wq ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 struct net_device* dev_get_by_index (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 scalar_t__ ib_network_to_gid_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iboe_get_mtu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iboe_get_rate (struct net_device*) ; 
 int /*<<< orphan*/  iboe_tos_to_sl (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cma_work*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_ip2gid (struct sockaddr*,int /*<<< orphan*/ *) ; 
 unsigned long roce_gid_type_mask_support (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cma_resolve_iboe_route(struct rdma_id_private *id_priv)
{
	struct rdma_route *route = &id_priv->id.route;
	struct rdma_addr *addr = &route->addr;
	struct cma_work *work;
	int ret;
	struct net_device *ndev = NULL;


	work = kzalloc(sizeof *work, GFP_KERNEL);
	if (!work)
		return -ENOMEM;

	work->id = id_priv;
	INIT_WORK(&work->work, cma_work_handler);

	route->path_rec = kzalloc(sizeof *route->path_rec, GFP_KERNEL);
	if (!route->path_rec) {
		ret = -ENOMEM;
		goto err1;
	}

	route->num_paths = 1;

	if (addr->dev_addr.bound_dev_if) {
		unsigned long supported_gids;

		ndev = dev_get_by_index(addr->dev_addr.net,
					addr->dev_addr.bound_dev_if);
		if (!ndev) {
			ret = -ENODEV;
			goto err2;
		}

		route->path_rec->net = ndev->if_vnet;
		route->path_rec->ifindex = ndev->if_index;
		supported_gids = roce_gid_type_mask_support(id_priv->id.device,
							    id_priv->id.port_num);
		route->path_rec->gid_type =
			cma_route_gid_type(addr->dev_addr.network,
					   supported_gids,
					   id_priv->gid_type);
	}
	if (!ndev) {
		ret = -ENODEV;
		goto err2;
	}

	memcpy(route->path_rec->dmac, addr->dev_addr.dst_dev_addr, ETH_ALEN);

	rdma_ip2gid((struct sockaddr *)&id_priv->id.route.addr.src_addr,
		    &route->path_rec->sgid);
	rdma_ip2gid((struct sockaddr *)&id_priv->id.route.addr.dst_addr,
		    &route->path_rec->dgid);

	/* Use the hint from IP Stack to select GID Type */
	if (route->path_rec->gid_type < ib_network_to_gid_type(addr->dev_addr.network))
		route->path_rec->gid_type = ib_network_to_gid_type(addr->dev_addr.network);
	if (((struct sockaddr *)&id_priv->id.route.addr.dst_addr)->sa_family != AF_IB)
		/* TODO: get the hoplimit from the inet/inet6 device */
		route->path_rec->hop_limit = addr->dev_addr.hoplimit;
	else
		route->path_rec->hop_limit = 1;
	route->path_rec->reversible = 1;
	route->path_rec->pkey = cpu_to_be16(0xffff);
	route->path_rec->mtu_selector = IB_SA_EQ;
	route->path_rec->sl = iboe_tos_to_sl(ndev, id_priv->tos);
	route->path_rec->traffic_class = id_priv->tos;
	route->path_rec->mtu = iboe_get_mtu(ndev->if_mtu);
	route->path_rec->rate_selector = IB_SA_EQ;
	route->path_rec->rate = iboe_get_rate(ndev);
	dev_put(ndev);
	route->path_rec->packet_life_time_selector = IB_SA_EQ;
	route->path_rec->packet_life_time = CMA_IBOE_PACKET_LIFETIME;
	if (!route->path_rec->mtu) {
		ret = -EINVAL;
		goto err2;
	}

	work->old_state = RDMA_CM_ROUTE_QUERY;
	work->new_state = RDMA_CM_ROUTE_RESOLVED;
	work->event.event = RDMA_CM_EVENT_ROUTE_RESOLVED;
	work->event.status = 0;

	queue_work(cma_wq, &work->work);

	return 0;

err2:
	kfree(route->path_rec);
	route->path_rec = NULL;
err1:
	kfree(work);
	return ret;
}