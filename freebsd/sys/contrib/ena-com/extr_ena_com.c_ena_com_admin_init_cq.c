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
typedef  int /*<<< orphan*/  u16 ;
struct ena_com_admin_cq {int phase; scalar_t__ head; int /*<<< orphan*/  entries; int /*<<< orphan*/  mem_handle; int /*<<< orphan*/  dma_addr; } ;
struct ena_com_admin_queue {int /*<<< orphan*/  q_dmadev; int /*<<< orphan*/  q_depth; struct ena_com_admin_cq cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADMIN_CQ_SIZE (int /*<<< orphan*/ ) ; 
 int ENA_COM_NO_MEM ; 
 int /*<<< orphan*/  ENA_MEM_ALLOC_COHERENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_trc_err (char*) ; 

__attribute__((used)) static int ena_com_admin_init_cq(struct ena_com_admin_queue *queue)
{
	struct ena_com_admin_cq *cq = &queue->cq;
	u16 size = ADMIN_CQ_SIZE(queue->q_depth);

	ENA_MEM_ALLOC_COHERENT(queue->q_dmadev, size, cq->entries, cq->dma_addr,
			       cq->mem_handle);

	if (!cq->entries)  {
		ena_trc_err("memory allocation failed\n");
		return ENA_COM_NO_MEM;
	}

	cq->head = 0;
	cq->phase = 1;

	return 0;
}