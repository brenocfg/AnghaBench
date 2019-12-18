#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int num_tx_rings; TYPE_1__* tx_ring; } ;
typedef  TYPE_2__ qla_host_t ;
struct TYPE_5__ {int /*<<< orphan*/ * tx_buf; } ;

/* Variables and functions */
 int NUM_TX_DESCRIPTORS ; 
 int /*<<< orphan*/  qls_flush_tx_buf (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qls_flush_xmt_bufs(qla_host_t *ha)
{
	int		i, j;

	for (j = 0; j < ha->num_tx_rings; j++) {
		for (i = 0; i < NUM_TX_DESCRIPTORS; i++)
			qls_flush_tx_buf(ha, &ha->tx_ring[j].tx_buf[i]);
	}

	return;
}