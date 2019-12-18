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
struct sockaddr_ib {void* sib_sid_mask; void* sib_sid; int /*<<< orphan*/  sib_family; } ;
struct sockaddr {int dummy; } ;
struct rdma_cm_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_IB ; 
 int /*<<< orphan*/  RDMA_IB_IP_PS_MASK ; 
 int /*<<< orphan*/  RDMA_IB_IP_PS_TCP ; 
 int /*<<< orphan*/  RDMA_PS_IB ; 
 int af_ib_support ; 
 void* htobe64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_ib*,int /*<<< orphan*/ ,int) ; 
 int rdma_bind_addr (struct rdma_cm_id*,struct sockaddr*) ; 
 int rdma_create_id (int /*<<< orphan*/ *,struct rdma_cm_id**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_destroy_id (struct rdma_cm_id*) ; 

__attribute__((used)) static void ucma_set_af_ib_support(void)
{
	struct rdma_cm_id *id;
	struct sockaddr_ib sib;
	int ret;

	ret = rdma_create_id(NULL, &id, NULL, RDMA_PS_IB);
	if (ret)
		return;

	memset(&sib, 0, sizeof sib);
	sib.sib_family = AF_IB;
	sib.sib_sid = htobe64(RDMA_IB_IP_PS_TCP);
	sib.sib_sid_mask = htobe64(RDMA_IB_IP_PS_MASK);
	af_ib_support = 1;
	ret = rdma_bind_addr(id, (struct sockaddr *) &sib);
	af_ib_support = !ret;

	rdma_destroy_id(id);
}