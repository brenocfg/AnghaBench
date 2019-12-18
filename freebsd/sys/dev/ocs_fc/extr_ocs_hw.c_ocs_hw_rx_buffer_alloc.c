#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ocs_t ;
struct TYPE_7__ {int /*<<< orphan*/ * os; } ;
typedef  TYPE_1__ ocs_hw_t ;
struct TYPE_8__ {int rqindex; int /*<<< orphan*/  dma; } ;
typedef  TYPE_2__ ocs_hw_rq_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_MIN_DMA_ALIGNMENT ; 
 int OCS_M_NOWAIT ; 
 int OCS_M_ZERO ; 
 scalar_t__ ocs_dma_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* ocs_malloc (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static ocs_hw_rq_buffer_t *
ocs_hw_rx_buffer_alloc(ocs_hw_t *hw, uint32_t rqindex, uint32_t count, uint32_t size)
{
	ocs_t *ocs = hw->os;
	ocs_hw_rq_buffer_t *rq_buf = NULL;
	ocs_hw_rq_buffer_t *prq;
	uint32_t i;

	if (count != 0) {
		rq_buf = ocs_malloc(hw->os, sizeof(*rq_buf) * count, OCS_M_NOWAIT | OCS_M_ZERO);
		if (rq_buf == NULL) {
			ocs_log_err(hw->os, "Failure to allocate unsolicited DMA trackers\n");
			return NULL;
		}

		for (i = 0, prq = rq_buf; i < count; i ++, prq++) {
			prq->rqindex = rqindex;
			if (ocs_dma_alloc(ocs, &prq->dma, size, OCS_MIN_DMA_ALIGNMENT)) {
				ocs_log_err(hw->os, "DMA allocation failed\n");
				ocs_free(hw->os, rq_buf, sizeof(*rq_buf) * count);
				rq_buf = NULL;
				break;
			}
		}
	}
	return rq_buf;
}