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
struct net_device {struct in_device* ip_ptr; } ;
struct in_ifaddr {int /*<<< orphan*/  ifa_mask; } ;
struct in_device {struct in_ifaddr* ifa_list; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */

int dev_netmask(void *d, void *m)
{
	struct net_device *dev = d;
	struct in_device *ip = dev->ip_ptr;
	struct in_ifaddr *in;
	__be32 *mask_out = m;

	if (ip == NULL)
		return 1;

	in = ip->ifa_list;
	if (in == NULL)
		return 1;

	*mask_out = in->ifa_mask;
	return 0;
}