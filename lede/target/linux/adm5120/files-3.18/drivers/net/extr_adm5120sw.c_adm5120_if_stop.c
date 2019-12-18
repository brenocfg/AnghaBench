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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWITCH_INTS_USED ; 
 int SWITCH_NUM_PORTS ; 
 int /*<<< orphan*/  SWITCH_PORTS_NOCPU ; 
 int /*<<< orphan*/  SWITCH_REG_PORT_CONF0 ; 
 struct net_device** adm5120_devs ; 
 int /*<<< orphan*/ * adm5120_eth_vlans ; 
 int /*<<< orphan*/  adm5120_if_napi_disable (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  sw_int_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw_used ; 
 int /*<<< orphan*/  sw_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adm5120_if_stop(struct net_device *dev)
{
	u32 t;
	int i;

	netif_stop_queue(dev);
	adm5120_if_napi_disable(dev);

	/* disable port if not assigned to other devices */
	t = sw_read_reg(SWITCH_REG_PORT_CONF0);
	t |= SWITCH_PORTS_NOCPU;
	for (i = 0; i < SWITCH_NUM_PORTS; i++) {
		if ((dev != adm5120_devs[i]) && netif_running(adm5120_devs[i]))
			t &= ~adm5120_eth_vlans[i];
	}
	sw_write_reg(SWITCH_REG_PORT_CONF0, t);

	if (!--sw_used)
		sw_int_mask(SWITCH_INTS_USED);

	free_irq(dev->irq, dev);

	return 0;
}