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
 int ipv4_list_add_range (struct sa_open_data*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ipv4_list_add_netmask(struct sa_open_data *od,
		u32 net, u32 net_mask, gfp_t gfp)
{
	u32 start = net & net_mask;
	u32 end = net | ~net_mask;
	
	return ipv4_list_add_range(od, start, end, gfp);
}