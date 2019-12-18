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
struct rdma_cm_id {struct iser_conn* context; } ;
struct iser_device {int dummy; } ;
struct ib_conn {struct iser_device* device; } ;
struct iser_conn {struct ib_conn ib_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISER_ERR (char*,struct iser_conn*,...) ; 
 int /*<<< orphan*/  iser_connect_error (struct rdma_cm_id*) ; 
 struct iser_device* iser_device_find_by_ib_device (struct rdma_cm_id*) ; 
 int rdma_resolve_route (struct rdma_cm_id*,int) ; 

__attribute__((used)) static void
iser_addr_handler(struct rdma_cm_id *cma_id)
{
	struct iser_device *device;
	struct iser_conn   *iser_conn;
	struct ib_conn   *ib_conn;
	int    ret;

	iser_conn = cma_id->context;

	ib_conn = &iser_conn->ib_conn;
	device = iser_device_find_by_ib_device(cma_id);
	if (!device) {
		ISER_ERR("conn %p device lookup/creation failed",
			 iser_conn);
		iser_connect_error(cma_id);
		return;
	}

	ib_conn->device = device;

	ret = rdma_resolve_route(cma_id, 1000);
	if (ret) {
		ISER_ERR("conn %p resolve route failed: %d", iser_conn, ret);
		iser_connect_error(cma_id);
		return;
	}
}