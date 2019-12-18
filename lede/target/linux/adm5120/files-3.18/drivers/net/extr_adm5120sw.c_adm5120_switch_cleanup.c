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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWITCH_INTS_ALL ; 
 int SWITCH_NUM_PORTS ; 
 struct net_device** adm5120_devs ; 
 int /*<<< orphan*/  adm5120_switch_rx_ring_free () ; 
 int /*<<< orphan*/  adm5120_switch_tx_ring_free () ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  sw_int_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void adm5120_switch_cleanup(void)
{
	int i;

	/* disable interrupts */
	sw_int_mask(SWITCH_INTS_ALL);

	for (i = 0; i < SWITCH_NUM_PORTS; i++) {
		struct net_device *dev = adm5120_devs[i];
		if (dev) {
			unregister_netdev(dev);
			free_netdev(dev);
		}
	}

	adm5120_switch_tx_ring_free();
	adm5120_switch_rx_ring_free();
}