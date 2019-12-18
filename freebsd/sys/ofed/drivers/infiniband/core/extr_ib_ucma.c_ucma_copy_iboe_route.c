#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union ib_gid {int dummy; } ib_gid ;
struct sockaddr {int dummy; } ;
struct rdma_ucm_query_route_resp {int num_paths; TYPE_2__* ib_route; } ;
struct TYPE_3__ {int /*<<< orphan*/  src_addr; int /*<<< orphan*/  dst_addr; } ;
struct rdma_route {int num_paths; int /*<<< orphan*/ * path_rec; TYPE_1__ addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  pkey; int /*<<< orphan*/  sgid; int /*<<< orphan*/  dgid; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  ib_copy_path_rec_to_user (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_ip2gid (struct sockaddr*,union ib_gid*) ; 

__attribute__((used)) static void ucma_copy_iboe_route(struct rdma_ucm_query_route_resp *resp,
				 struct rdma_route *route)
{

	resp->num_paths = route->num_paths;
	switch (route->num_paths) {
	case 0:
		rdma_ip2gid((struct sockaddr *)&route->addr.dst_addr,
			    (union ib_gid *)&resp->ib_route[0].dgid);
		rdma_ip2gid((struct sockaddr *)&route->addr.src_addr,
			    (union ib_gid *)&resp->ib_route[0].sgid);
		resp->ib_route[0].pkey = cpu_to_be16(0xffff);
		break;
	case 2:
		ib_copy_path_rec_to_user(&resp->ib_route[1],
					 &route->path_rec[1]);
		/* fall through */
	case 1:
		ib_copy_path_rec_to_user(&resp->ib_route[0],
					 &route->path_rec[0]);
		break;
	default:
		break;
	}
}