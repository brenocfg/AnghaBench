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
struct al_eth_irq {scalar_t__ requested; int /*<<< orphan*/  vector; int /*<<< orphan*/  cookie; int /*<<< orphan*/  res; } ;
struct al_eth_adapter {int irq_vecs; int /*<<< orphan*/  dev; struct al_eth_irq* irq_tbl; } ;

/* Variables and functions */
 int bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
__al_eth_free_irq(struct al_eth_adapter *adapter)
{
	struct al_eth_irq *irq;
	int i, rc;

	for (i = 0; i < adapter->irq_vecs; i++) {
		irq = &adapter->irq_tbl[i];
		if (irq->requested != 0) {
			device_printf_dbg(adapter->dev, "tear down irq: %d\n",
			    irq->vector);
			rc = bus_teardown_intr(adapter->dev, irq->res,
			    irq->cookie);
			if (rc != 0)
				device_printf(adapter->dev, "failed to tear "
				    "down irq: %d\n", irq->vector);

		}
		irq->requested = 0;
	}
}