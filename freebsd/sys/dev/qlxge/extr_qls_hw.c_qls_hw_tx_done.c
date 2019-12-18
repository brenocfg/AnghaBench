#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_5__ {TYPE_1__* tx_ring; } ;
typedef  TYPE_2__ qla_host_t ;
struct TYPE_4__ {size_t txr_done; size_t txr_next; size_t txr_free; } ;

/* Variables and functions */
 size_t NUM_TX_DESCRIPTORS ; 
 scalar_t__ QLA_TX_MIN_FREE ; 

int
qls_hw_tx_done(qla_host_t *ha, uint32_t txr_idx)
{
	uint32_t txr_done, txr_next;

	txr_done = ha->tx_ring[txr_idx].txr_done;
	txr_next = ha->tx_ring[txr_idx].txr_next;

	if (txr_done == txr_next) {
		ha->tx_ring[txr_idx].txr_free = NUM_TX_DESCRIPTORS;
	} else if (txr_done > txr_next) {
		ha->tx_ring[txr_idx].txr_free = txr_done - txr_next;
	} else {
		ha->tx_ring[txr_idx].txr_free = NUM_TX_DESCRIPTORS +
			txr_done - txr_next;
	}

	if (ha->tx_ring[txr_idx].txr_free <= QLA_TX_MIN_FREE)
		return (-1);

	return (0);
}