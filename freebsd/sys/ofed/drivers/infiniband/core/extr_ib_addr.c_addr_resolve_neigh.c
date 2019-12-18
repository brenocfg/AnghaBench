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
typedef  int /*<<< orphan*/  u8 ;
struct sockaddr {int dummy; } ;
struct rdma_dev_addr {scalar_t__ bound_dev_if; int /*<<< orphan*/  src_dev_addr; int /*<<< orphan*/  dst_dev_addr; } ;
struct ifnet {int if_flags; scalar_t__ if_index; } ;

/* Variables and functions */
 int IFF_LOOPBACK ; 
 int IFF_NOARP ; 
 int /*<<< orphan*/  MAX_ADDR_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdma_copy_addr (struct rdma_dev_addr*,struct ifnet*,int /*<<< orphan*/ *) ; 
 int rdma_translate_ip (struct sockaddr const*,struct rdma_dev_addr*) ; 

__attribute__((used)) static int addr_resolve_neigh(struct ifnet *dev,
			      const struct sockaddr *dst_in,
			      u8 *edst,
			      struct rdma_dev_addr *addr)
{
	if (dev->if_flags & IFF_LOOPBACK) {
		int ret;

		/*
		 * Binding to a loopback device is not allowed. Make
		 * sure the destination device address is global by
		 * clearing the bound device interface:
		 */
		if (addr->bound_dev_if == dev->if_index)
			addr->bound_dev_if = 0;

		ret = rdma_translate_ip(dst_in, addr);
		if (ret == 0) {
			memcpy(addr->dst_dev_addr, addr->src_dev_addr,
			       MAX_ADDR_LEN);
		}
		return ret;
	}

	/* If the device doesn't do ARP internally */
	if (!(dev->if_flags & IFF_NOARP))
		return rdma_copy_addr(addr, dev, edst);

	return rdma_copy_addr(addr, dev, NULL);
}