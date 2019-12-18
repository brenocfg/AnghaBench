#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct al_hal_eth_adapter {int /*<<< orphan*/  name; TYPE_1__ rx_udma; TYPE_1__ tx_udma; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDMA_DISABLE ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ) ; 
 int al_udma_state_set_wait (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_warn (char*,int /*<<< orphan*/ ,int) ; 

int al_eth_adapter_stop(struct al_hal_eth_adapter *adapter)
{
	int rc;

	al_dbg("eth [%s]: stop controller's UDMA\n", adapter->name);

	/* disable Tx dma*/
	rc = al_udma_state_set_wait(&adapter->tx_udma, UDMA_DISABLE);
	if (rc != 0) {
		al_warn("[%s] warn: failed to change state, error %d\n",
			 adapter->tx_udma.name, rc);
		return rc;
	}

	al_dbg("eth [%s]: controller's TX UDMA stopped\n",
		 adapter->name);
	/* disable Rx dma*/
	rc = al_udma_state_set_wait(&adapter->rx_udma, UDMA_DISABLE);
	if (rc != 0) {
		al_warn("[%s] warn: failed to change state, error %d\n",
			 adapter->rx_udma.name, rc);
		return rc;
	}

	al_dbg("eth [%s]: controller's RX UDMA stopped\n",
		 adapter->name);
	return 0;
}