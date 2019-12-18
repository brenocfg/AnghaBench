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
struct TYPE_2__ {scalar_t__ slc_int; } ;
union nps_pkt_slc_cnts {TYPE_1__ s; int /*<<< orphan*/  value; } ;
struct nitrox_q_vector {int /*<<< orphan*/  resp_tasklet; struct nitrox_cmdq* cmdq; } ;
struct nitrox_cmdq {int /*<<< orphan*/  compl_cnt_csr_addr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t nps_pkt_slc_isr(int irq, void *data)
{
	struct nitrox_q_vector *qvec = data;
	union nps_pkt_slc_cnts slc_cnts;
	struct nitrox_cmdq *cmdq = qvec->cmdq;

	slc_cnts.value = readq(cmdq->compl_cnt_csr_addr);
	/* New packet on SLC output port */
	if (slc_cnts.s.slc_int)
		tasklet_hi_schedule(&qvec->resp_tasklet);

	return IRQ_HANDLED;
}