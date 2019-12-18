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
struct sockaddr_in {int dummy; } ;
struct rdma_dev_addr {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 

__attribute__((used)) static int addr4_resolve(struct sockaddr_in *src_in,
			 const struct sockaddr_in *dst_in,
			 struct rdma_dev_addr *addr,
			 u8 *edst,
			 struct ifnet **ifpp)
{
	return -EADDRNOTAVAIL;
}