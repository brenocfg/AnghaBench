#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/ * ifq_head; } ;
struct ifnet {TYPE_1__ if_snd; } ;
struct TYPE_8__ {scalar_t__ irq_rid; TYPE_4__* ha; } ;
typedef  TYPE_2__ qla_ivec_t ;
struct TYPE_9__ {scalar_t__ txr_comp; int /*<<< orphan*/ * tx_cons; } ;
typedef  TYPE_3__ qla_hw_t ;
struct TYPE_10__ {int /*<<< orphan*/  tx_task; int /*<<< orphan*/  tx_tq; struct ifnet* ifp; TYPE_3__ hw; int /*<<< orphan*/  pci_dev; } ;
typedef  TYPE_4__ qla_host_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  QL_ENABLE_INTERRUPTS (TYPE_4__*,scalar_t__) ; 
 scalar_t__ QL_RUNNING (struct ifnet*) ; 
 scalar_t__ qla_le32_to_host (int /*<<< orphan*/ ) ; 
 scalar_t__ qla_rcv_isr (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcv_pkt_thres_d ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
qla_rcv(void *context, int pending)
{
	qla_ivec_t *ivec = context;
	qla_host_t *ha;
	device_t dev;
	qla_hw_t *hw;
	uint32_t sds_idx;
	uint32_t ret;
	struct ifnet *ifp;

	ha = ivec->ha;
	dev = ha->pci_dev;
	hw = &ha->hw;
	sds_idx = ivec->irq_rid - 1;
	ifp = ha->ifp;

	do {
		if (sds_idx == 0) {
			if (qla_le32_to_host(*(hw->tx_cons)) != hw->txr_comp) {
				taskqueue_enqueue(ha->tx_tq, &ha->tx_task);
			} else if ((ifp->if_snd.ifq_head != NULL) &&
					QL_RUNNING(ifp)) {
				taskqueue_enqueue(ha->tx_tq, &ha->tx_task);
			}
		}
		ret = qla_rcv_isr(ha, sds_idx, rcv_pkt_thres_d);
	} while (ret);

	if (sds_idx == 0)
		taskqueue_enqueue(ha->tx_tq, &ha->tx_task);

	QL_ENABLE_INTERRUPTS(ha, sds_idx);
}