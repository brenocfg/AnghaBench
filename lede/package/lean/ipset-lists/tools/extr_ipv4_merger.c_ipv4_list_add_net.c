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
typedef  int u32 ;
struct sa_open_data {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ipv4_list_add_netmask (struct sa_open_data*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipv4_list_add_net(struct sa_open_data *od, u32 net,
		int net_bits, gfp_t gfp)
{
	u32 net_mask;

	if(net_bits == 0)
		net_mask = 0x00000000;
	else
		net_mask = ~(((u32)1 << (32 - net_bits)) - 1);
	//printf("%d: %08x, %08x\n", net_bits, net_mask, net_size);

	return ipv4_list_add_netmask(od, net, net_mask, gfp);
}