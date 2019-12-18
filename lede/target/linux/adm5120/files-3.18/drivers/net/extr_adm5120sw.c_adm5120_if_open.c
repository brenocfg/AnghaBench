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
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  SWITCH_INTS_USED ; 
 int SWITCH_NUM_PORTS ; 
 int /*<<< orphan*/  SWITCH_REG_PORT_CONF0 ; 
 int /*<<< orphan*/  SW_ERR (char*,int /*<<< orphan*/ ) ; 
 struct net_device** adm5120_devs ; 
 int /*<<< orphan*/ * adm5120_eth_vlans ; 
 int /*<<< orphan*/  adm5120_if_napi_disable (struct net_device*) ; 
 int /*<<< orphan*/  adm5120_if_napi_enable (struct net_device*) ; 
 int /*<<< orphan*/  adm5120_switch_irq ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  sw_int_unmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw_used ; 
 int /*<<< orphan*/  sw_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adm5120_if_open(struct net_device *dev)
{
	u32 t;
	int err;
	int i;

	adm5120_if_napi_enable(dev);

	err = request_irq(dev->irq, adm5120_switch_irq, IRQF_SHARED,
			  dev->name, dev);
	if (err) {
		SW_ERR("unable to get irq for %s\n", dev->name);
		goto err;
	}

	if (!sw_used++)
		/* enable interrupts on first open */
		sw_int_unmask(SWITCH_INTS_USED);

	/* enable (additional) port */
	t = sw_read_reg(SWITCH_REG_PORT_CONF0);
	for (i = 0; i < SWITCH_NUM_PORTS; i++) {
		if (dev == adm5120_devs[i])
			t &= ~adm5120_eth_vlans[i];
	}
	sw_write_reg(SWITCH_REG_PORT_CONF0, t);

	netif_start_queue(dev);

	return 0;

err:
	adm5120_if_napi_disable(dev);
	return err;
}