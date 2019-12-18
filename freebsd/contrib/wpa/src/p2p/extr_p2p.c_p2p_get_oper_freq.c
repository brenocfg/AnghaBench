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
struct p2p_device {scalar_t__ oper_freq; } ;
struct p2p_data {int dummy; } ;

/* Variables and functions */
 struct p2p_device* p2p_get_device_interface (struct p2p_data*,int /*<<< orphan*/  const*) ; 

int p2p_get_oper_freq(struct p2p_data *p2p, const u8 *iface_addr)
{
	struct p2p_device *dev = p2p_get_device_interface(p2p, iface_addr);
	if (dev == NULL)
		return -1;
	if (dev->oper_freq <= 0)
		return -1;
	return dev->oper_freq;
}