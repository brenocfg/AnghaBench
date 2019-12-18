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
struct TYPE_3__ {int /*<<< orphan*/  rsize; } ;
union nps_pkt_in_instr_rsize {int value; TYPE_1__ s; } ;
struct TYPE_4__ {int dbell; } ;
union nps_pkt_in_instr_baoff_dbell {int value; TYPE_2__ s; } ;
typedef  int /*<<< orphan*/  u64 ;
struct nitrox_device {int nr_queues; int /*<<< orphan*/  qlen; struct nitrox_cmdq* pkt_inq; } ;
struct nitrox_cmdq {int dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPS_PKT_IN_INSTR_BADDRX (int) ; 
 int /*<<< orphan*/  NPS_PKT_IN_INSTR_BAOFF_DBELLX (int) ; 
 int /*<<< orphan*/  NPS_PKT_IN_INSTR_RSIZEX (int) ; 
 int /*<<< orphan*/  NPS_PKT_IN_INT_LEVELSX (int) ; 
 int /*<<< orphan*/  enable_pkt_input_ring (struct nitrox_device*,int) ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_pkt_input_ring (struct nitrox_device*,int) ; 

void nitrox_config_pkt_input_rings(struct nitrox_device *ndev)
{
	int i;

	for (i = 0; i < ndev->nr_queues; i++) {
		struct nitrox_cmdq *cmdq = &ndev->pkt_inq[i];
		union nps_pkt_in_instr_rsize pkt_in_rsize;
		union nps_pkt_in_instr_baoff_dbell pkt_in_dbell;
		u64 offset;

		reset_pkt_input_ring(ndev, i);

		/**
		 * step 4:
		 * configure ring base address 16-byte aligned,
		 * size and interrupt threshold.
		 */
		offset = NPS_PKT_IN_INSTR_BADDRX(i);
		nitrox_write_csr(ndev, offset, cmdq->dma);

		/* configure ring size */
		offset = NPS_PKT_IN_INSTR_RSIZEX(i);
		pkt_in_rsize.value = 0;
		pkt_in_rsize.s.rsize = ndev->qlen;
		nitrox_write_csr(ndev, offset, pkt_in_rsize.value);

		/* set high threshold for pkt input ring interrupts */
		offset = NPS_PKT_IN_INT_LEVELSX(i);
		nitrox_write_csr(ndev, offset, 0xffffffff);

		/* step 5: clear off door bell counts */
		offset = NPS_PKT_IN_INSTR_BAOFF_DBELLX(i);
		pkt_in_dbell.value = 0;
		pkt_in_dbell.s.dbell = 0xffffffff;
		nitrox_write_csr(ndev, offset, pkt_in_dbell.value);

		/* enable the ring */
		enable_pkt_input_ring(ndev, i);
	}
}