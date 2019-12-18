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
typedef  size_t uint16_t ;
struct ena_eth_io_intr_reg {int dummy; } ;
struct ena_com_io_cq {int dummy; } ;
struct ena_adapter {int num_queues; TYPE_1__* ena_dev; } ;
struct TYPE_2__ {struct ena_com_io_cq* io_cq_queues; } ;

/* Variables and functions */
 size_t ENA_IO_TXQ_IDX (int) ; 
 int /*<<< orphan*/  ena_com_unmask_intr (struct ena_com_io_cq*,struct ena_eth_io_intr_reg*) ; 
 int /*<<< orphan*/  ena_com_update_intr_reg (struct ena_eth_io_intr_reg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ena_unmask_all_io_irqs(struct ena_adapter *adapter)
{
	struct ena_com_io_cq* io_cq;
	struct ena_eth_io_intr_reg intr_reg;
	uint16_t ena_qid;
	int i;

	/* Unmask interrupts for all queues */
	for (i = 0; i < adapter->num_queues; i++) {
		ena_qid = ENA_IO_TXQ_IDX(i);
		io_cq = &adapter->ena_dev->io_cq_queues[ena_qid];
		ena_com_update_intr_reg(&intr_reg, 0, 0, true);
		ena_com_unmask_intr(io_cq, &intr_reg);
	}
}