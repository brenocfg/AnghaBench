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
typedef  int u16 ;
struct ena_com_io_cq {int head; int last_head_update; int q_depth; int /*<<< orphan*/  cq_head_db_reg; int /*<<< orphan*/  bus; int /*<<< orphan*/  qid; } ;

/* Variables and functions */
 int ENA_COMP_HEAD_THRESH ; 
 int /*<<< orphan*/  ENA_REG_WRITE32 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_trc_dbg (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int ena_com_update_dev_comp_head(struct ena_com_io_cq *io_cq)
{
	u16 unreported_comp, head;
	bool need_update;

	head = io_cq->head;
	unreported_comp = head - io_cq->last_head_update;
	need_update = unreported_comp > (io_cq->q_depth / ENA_COMP_HEAD_THRESH);

	if (io_cq->cq_head_db_reg && need_update) {
		ena_trc_dbg("Write completion queue doorbell for queue %d: head: %d\n",
			    io_cq->qid, head);
		ENA_REG_WRITE32(io_cq->bus, head, io_cq->cq_head_db_reg);
		io_cq->last_head_update = head;
	}

	return 0;
}