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
struct nitrox_device {int dummy; } ;
struct nitrox_cmdq {scalar_t__ instr_size; scalar_t__ qsize; scalar_t__ dma; scalar_t__ unalign_dma; int /*<<< orphan*/ * base; int /*<<< orphan*/ * unalign_base; int /*<<< orphan*/ * compl_cnt_csr_addr; int /*<<< orphan*/ * dbell_csr_addr; int /*<<< orphan*/  backlog_qflush; struct nitrox_device* ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV (struct nitrox_device*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  nitrox_cmdq_reset (struct nitrox_cmdq*) ; 

__attribute__((used)) static void nitrox_cmdq_cleanup(struct nitrox_cmdq *cmdq)
{
	struct nitrox_device *ndev;

	if (!cmdq)
		return;

	if (!cmdq->unalign_base)
		return;

	ndev = cmdq->ndev;
	cancel_work_sync(&cmdq->backlog_qflush);

	dma_free_coherent(DEV(ndev), cmdq->qsize,
			  cmdq->unalign_base, cmdq->unalign_dma);
	nitrox_cmdq_reset(cmdq);

	cmdq->dbell_csr_addr = NULL;
	cmdq->compl_cnt_csr_addr = NULL;
	cmdq->unalign_base = NULL;
	cmdq->base = NULL;
	cmdq->unalign_dma = 0;
	cmdq->dma = 0;
	cmdq->qsize = 0;
	cmdq->instr_size = 0;
}