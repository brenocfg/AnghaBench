#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  ocs_t ;
struct TYPE_6__ {int /*<<< orphan*/ * os; } ;
typedef  TYPE_1__ ocs_hw_t ;
struct TYPE_7__ {int /*<<< orphan*/  dma; } ;
typedef  TYPE_2__ ocs_hw_rq_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_dma_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ *,TYPE_2__*,int) ; 

__attribute__((used)) static void
ocs_hw_rx_buffer_free(ocs_hw_t *hw, ocs_hw_rq_buffer_t *rq_buf, uint32_t count)
{
	ocs_t *ocs = hw->os;
	uint32_t i;
	ocs_hw_rq_buffer_t *prq;

	if (rq_buf != NULL) {
		for (i = 0, prq = rq_buf; i < count; i++, prq++) {
			ocs_dma_free(ocs, &prq->dma);
		}
		ocs_free(hw->os, rq_buf, sizeof(*rq_buf) * count);
	}
}