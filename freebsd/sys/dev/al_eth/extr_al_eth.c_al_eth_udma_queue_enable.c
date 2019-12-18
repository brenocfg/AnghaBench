#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct al_udma_q_params {int dummy; } ;
struct al_eth_adapter {int /*<<< orphan*/  dev; int /*<<< orphan*/  hal_adapter; TYPE_1__* rx_ring; TYPE_2__* tx_ring; } ;
typedef  enum al_udma_type { ____Placeholder_al_udma_type } al_udma_type ;
struct TYPE_4__ {struct al_udma_q_params q_params; } ;
struct TYPE_3__ {struct al_udma_q_params q_params; } ;

/* Variables and functions */
 int UDMA_TX ; 
 int al_eth_queue_config (int /*<<< orphan*/ *,int,int,struct al_udma_q_params*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static int
al_eth_udma_queue_enable(struct al_eth_adapter *adapter, enum al_udma_type type,
    int qid)
{
	int rc = 0;
	char *name = (type == UDMA_TX) ? "Tx" : "Rx";
	struct al_udma_q_params *q_params;

	if (type == UDMA_TX)
		q_params = &adapter->tx_ring[qid].q_params;
	else
		q_params = &adapter->rx_ring[qid].q_params;

	rc = al_eth_queue_config(&adapter->hal_adapter, type, qid, q_params);
	if (rc < 0) {
		device_printf(adapter->dev, "config %s queue %u failed\n", name,
		    qid);
		return (rc);
	}
	return (rc);
}