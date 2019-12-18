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
struct ena_com_admin_sq {int phase; int /*<<< orphan*/ * db_addr; scalar_t__ tail; scalar_t__ head; int /*<<< orphan*/  entries; int /*<<< orphan*/  mem_handle; int /*<<< orphan*/  dma_addr; } ;
struct ena_com_admin_queue {int /*<<< orphan*/  q_dmadev; int /*<<< orphan*/  q_depth; struct ena_com_admin_sq sq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADMIN_SQ_SIZE (int /*<<< orphan*/ ) ; 
 int ENA_COM_NO_MEM ; 
 int /*<<< orphan*/  ENA_MEM_ALLOC_COHERENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_trc_err (char*) ; 

__attribute__((used)) static int ena_com_admin_init_sq(struct ena_com_admin_queue *queue)
{
	struct ena_com_admin_sq *sq = &queue->sq;
	u16 size = ADMIN_SQ_SIZE(queue->q_depth);

	ENA_MEM_ALLOC_COHERENT(queue->q_dmadev, size, sq->entries, sq->dma_addr,
			       sq->mem_handle);

	if (!sq->entries) {
		ena_trc_err("memory allocation failed\n");
		return ENA_COM_NO_MEM;
	}

	sq->head = 0;
	sq->tail = 0;
	sq->phase = 1;

	sq->db_addr = NULL;

	return 0;
}