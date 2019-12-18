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
typedef  union ib_gid {int dummy; } ib_gid ;
struct sockaddr_ib {int /*<<< orphan*/  sib_pkey; int /*<<< orphan*/  sib_addr; } ;
struct rdma_dev_addr {int /*<<< orphan*/  dev_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_INFINIBAND ; 
 int /*<<< orphan*/  ib_addr_set_pkey (struct rdma_dev_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_addr_set_sgid (struct rdma_dev_addr*,union ib_gid*) ; 

__attribute__((used)) static void cma_translate_ib(struct sockaddr_ib *sib, struct rdma_dev_addr *dev_addr)
{
	dev_addr->dev_type = ARPHRD_INFINIBAND;
	rdma_addr_set_sgid(dev_addr, (union ib_gid *) &sib->sib_addr);
	ib_addr_set_pkey(dev_addr, ntohs(sib->sib_pkey));
}