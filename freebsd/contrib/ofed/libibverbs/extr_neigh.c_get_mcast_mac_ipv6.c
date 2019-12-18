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
typedef  int uint8_t ;
struct nl_addr {int dummy; } ;
typedef  int /*<<< orphan*/  mac_addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LLC ; 
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 struct nl_addr* nl_addr_build (int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ nl_addr_get_binary_addr (struct nl_addr*) ; 

__attribute__((used)) static int get_mcast_mac_ipv6(struct nl_addr *dst, struct nl_addr **ll_addr)
{
	uint8_t mac_addr[6] = {0x33, 0x33};

	memcpy(mac_addr + 2, (uint8_t *)nl_addr_get_binary_addr(dst) + 12, 4);

	*ll_addr = nl_addr_build(AF_LLC, mac_addr, sizeof(mac_addr));

	return *ll_addr == NULL ? -EINVAL : 0;
}