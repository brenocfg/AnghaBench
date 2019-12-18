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
struct p2p_device {int /*<<< orphan*/  interface_addr; } ;
struct p2p_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct p2p_device* p2p_get_device (struct p2p_data*,int /*<<< orphan*/  const*) ; 

int p2p_get_interface_addr(struct p2p_data *p2p, const u8 *dev_addr,
			   u8 *iface_addr)
{
	struct p2p_device *dev = p2p_get_device(p2p, dev_addr);
	if (dev == NULL || is_zero_ether_addr(dev->interface_addr))
		return -1;
	os_memcpy(iface_addr, dev->interface_addr, ETH_ALEN);
	return 0;
}