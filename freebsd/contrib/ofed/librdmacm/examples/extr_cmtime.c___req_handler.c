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
struct rdma_cm_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_qp_attr ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int rdma_accept (struct rdma_cm_id*,int /*<<< orphan*/ *) ; 
 int rdma_create_qp (struct rdma_cm_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_destroy_id (struct rdma_cm_id*) ; 
 int /*<<< orphan*/  rdma_reject (struct rdma_cm_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __req_handler(struct rdma_cm_id *id)
{
	int ret;

	ret = rdma_create_qp(id, NULL, &init_qp_attr);
	if (ret) {
		perror("failure creating qp");
		goto err;
	}

	ret = rdma_accept(id, NULL);
	if (ret) {
		perror("failure accepting");
		goto err;
	}
	return;

err:
	printf("failing connection request\n");
	rdma_reject(id, NULL, 0);
	rdma_destroy_id(id);
	return;
}