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
typedef  scalar_t__ u16 ;
struct ena_comp_ctx {int /*<<< orphan*/  wait_event; } ;
struct ena_com_admin_queue {int q_depth; int /*<<< orphan*/  comp_ctx; int /*<<< orphan*/  q_dmadev; } ;

/* Variables and functions */
 int ENA_COM_NO_MEM ; 
 int /*<<< orphan*/  ENA_MEM_ALLOC (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ENA_WAIT_EVENT_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_trc_err (char*) ; 
 struct ena_comp_ctx* get_comp_ctxt (struct ena_com_admin_queue*,scalar_t__,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int ena_com_init_comp_ctxt(struct ena_com_admin_queue *queue)
{
	size_t size = queue->q_depth * sizeof(struct ena_comp_ctx);
	struct ena_comp_ctx *comp_ctx;
	u16 i;

	queue->comp_ctx = ENA_MEM_ALLOC(queue->q_dmadev, size);
	if (unlikely(!queue->comp_ctx)) {
		ena_trc_err("memory allocation failed\n");
		return ENA_COM_NO_MEM;
	}

	for (i = 0; i < queue->q_depth; i++) {
		comp_ctx = get_comp_ctxt(queue, i, false);
		if (comp_ctx)
			ENA_WAIT_EVENT_INIT(comp_ctx->wait_event);
	}

	return 0;
}