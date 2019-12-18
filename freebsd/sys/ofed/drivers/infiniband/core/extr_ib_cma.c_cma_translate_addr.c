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
struct sockaddr_ib {int dummy; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct rdma_dev_addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_IB ; 
 int /*<<< orphan*/  cma_translate_ib (struct sockaddr_ib*,struct rdma_dev_addr*) ; 
 int rdma_translate_ip (struct sockaddr*,struct rdma_dev_addr*) ; 

__attribute__((used)) static int cma_translate_addr(struct sockaddr *addr, struct rdma_dev_addr *dev_addr)
{
	int ret;

	if (addr->sa_family != AF_IB) {
		ret = rdma_translate_ip(addr, dev_addr);
	} else {
		cma_translate_ib((struct sockaddr_ib *) addr, dev_addr);
		ret = 0;
	}

	return ret;
}