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
typedef  size_t u16 ;
struct ena_comp_ctx {int occupied; } ;
struct ena_com_admin_queue {size_t q_depth; struct ena_comp_ctx* comp_ctx; int /*<<< orphan*/  outstanding_cmds; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC32_INC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ena_trc_err (char*,...) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct ena_comp_ctx *get_comp_ctxt(struct ena_com_admin_queue *queue,
					  u16 command_id, bool capture)
{
	if (unlikely(command_id >= queue->q_depth)) {
		ena_trc_err("command id is larger than the queue size. cmd_id: %u queue size %d\n",
			    command_id, queue->q_depth);
		return NULL;
	}

	if (unlikely(queue->comp_ctx[command_id].occupied && capture)) {
		ena_trc_err("Completion context is occupied\n");
		return NULL;
	}

	if (capture) {
		ATOMIC32_INC(&queue->outstanding_cmds);
		queue->comp_ctx[command_id].occupied = true;
	}

	return &queue->comp_ctx[command_id];
}