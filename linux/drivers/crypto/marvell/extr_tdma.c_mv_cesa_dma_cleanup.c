#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct mv_cesa_tdma_desc {scalar_t__ flags; int /*<<< orphan*/  cur_dma; struct mv_cesa_tdma_desc* next; int /*<<< orphan*/  src; struct mv_cesa_tdma_desc* op; } ;
struct TYPE_5__ {int /*<<< orphan*/ * last; struct mv_cesa_tdma_desc* first; } ;
struct mv_cesa_req {TYPE_2__ chain; } ;
struct TYPE_6__ {TYPE_1__* dma; } ;
struct TYPE_4__ {int /*<<< orphan*/  tdma_desc_pool; int /*<<< orphan*/  op_pool; } ;

/* Variables and functions */
 scalar_t__ CESA_TDMA_OP ; 
 scalar_t__ CESA_TDMA_TYPE_MSK ; 
 TYPE_3__* cesa_dev ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct mv_cesa_tdma_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

void mv_cesa_dma_cleanup(struct mv_cesa_req *dreq)
{
	struct mv_cesa_tdma_desc *tdma;

	for (tdma = dreq->chain.first; tdma;) {
		struct mv_cesa_tdma_desc *old_tdma = tdma;
		u32 type = tdma->flags & CESA_TDMA_TYPE_MSK;

		if (type == CESA_TDMA_OP)
			dma_pool_free(cesa_dev->dma->op_pool, tdma->op,
				      le32_to_cpu(tdma->src));

		tdma = tdma->next;
		dma_pool_free(cesa_dev->dma->tdma_desc_pool, old_tdma,
			      old_tdma->cur_dma);
	}

	dreq->chain.first = NULL;
	dreq->chain.last = NULL;
}