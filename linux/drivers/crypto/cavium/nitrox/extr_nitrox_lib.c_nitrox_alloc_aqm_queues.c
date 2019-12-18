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
typedef  int /*<<< orphan*/  u64 ;
struct nitrox_device {int nr_queues; struct nitrox_cmdq** aqmq; int /*<<< orphan*/  node; } ;
struct nitrox_cmdq {int qno; int instr_size; void* compl_cnt_csr_addr; void* dbell_csr_addr; struct nitrox_device* ndev; } ;
struct aqmq_command_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQMQ_CMD_CNTX (int) ; 
 int /*<<< orphan*/  AQMQ_DRBLX (int) ; 
 int /*<<< orphan*/  AQM_Q_ALIGN_BYTES ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* NITROX_CSR_ADDR (struct nitrox_device*,int /*<<< orphan*/ ) ; 
 struct nitrox_cmdq* kzalloc_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (struct nitrox_cmdq*) ; 
 int nitrox_cmdq_init (struct nitrox_cmdq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitrox_free_aqm_queues (struct nitrox_device*) ; 

__attribute__((used)) static int nitrox_alloc_aqm_queues(struct nitrox_device *ndev)
{
	int i, err;

	for (i = 0; i < ndev->nr_queues; i++) {
		struct nitrox_cmdq *cmdq;
		u64 offset;

		cmdq = kzalloc_node(sizeof(*cmdq), GFP_KERNEL, ndev->node);
		if (!cmdq) {
			err = -ENOMEM;
			goto aqmq_fail;
		}

		cmdq->ndev = ndev;
		cmdq->qno = i;
		cmdq->instr_size = sizeof(struct aqmq_command_s);

		/* AQM Queue Doorbell Counter Register Address */
		offset = AQMQ_DRBLX(i);
		cmdq->dbell_csr_addr = NITROX_CSR_ADDR(ndev, offset);
		/* AQM Queue Commands Completed Count Register Address */
		offset = AQMQ_CMD_CNTX(i);
		cmdq->compl_cnt_csr_addr = NITROX_CSR_ADDR(ndev, offset);

		err = nitrox_cmdq_init(cmdq, AQM_Q_ALIGN_BYTES);
		if (err) {
			kzfree(cmdq);
			goto aqmq_fail;
		}
		ndev->aqmq[i] = cmdq;
	}

	return 0;

aqmq_fail:
	nitrox_free_aqm_queues(ndev);
	return err;
}