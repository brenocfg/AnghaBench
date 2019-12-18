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
struct sw_rx_data {int /*<<< orphan*/  data; } ;
struct qlnx_rx_queue {size_t sw_rx_cons; size_t sw_rx_prod; struct sw_rx_data* sw_rx_ring; int /*<<< orphan*/  rx_bd_ring; } ;
struct eth_rx_bd {int dummy; } ;

/* Variables and functions */
 int RX_RING_SIZE ; 
 struct eth_rx_bd* ecore_chain_consume (int /*<<< orphan*/ *) ; 
 struct eth_rx_bd* ecore_chain_produce (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct eth_rx_bd*,struct eth_rx_bd*,int) ; 

__attribute__((used)) static void
qlnx_reuse_rx_data(struct qlnx_rx_queue *rxq)
{
        struct eth_rx_bd	*rx_bd_cons =
					ecore_chain_consume(&rxq->rx_bd_ring);
        struct eth_rx_bd	*rx_bd_prod =
					ecore_chain_produce(&rxq->rx_bd_ring);
        struct sw_rx_data	*sw_rx_data_cons =
					&rxq->sw_rx_ring[rxq->sw_rx_cons];
        struct sw_rx_data	*sw_rx_data_prod =
					&rxq->sw_rx_ring[rxq->sw_rx_prod];

        sw_rx_data_prod->data = sw_rx_data_cons->data;
        memcpy(rx_bd_prod, rx_bd_cons, sizeof(struct eth_rx_bd));

        rxq->sw_rx_cons  = (rxq->sw_rx_cons + 1) & (RX_RING_SIZE - 1);
        rxq->sw_rx_prod  = (rxq->sw_rx_prod + 1) & (RX_RING_SIZE - 1);

	return;
}