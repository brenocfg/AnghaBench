#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_5__ {size_t hw_rq_count; TYPE_2__** hw_rq; } ;
typedef  TYPE_1__ ocs_hw_t ;
struct TYPE_6__ {int /*<<< orphan*/ * payload_buf; int /*<<< orphan*/  entry_count; int /*<<< orphan*/ * hdr_buf; } ;
typedef  TYPE_2__ hw_rq_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_hw_rx_buffer_free (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ocs_hw_rx_free(ocs_hw_t *hw)
{
	hw_rq_t *rq;
	uint32_t i;

	/* Free hw_rq buffers */
	for (i = 0; i < hw->hw_rq_count; i++) {
		rq = hw->hw_rq[i];
		if (rq != NULL) {
			ocs_hw_rx_buffer_free(hw, rq->hdr_buf, rq->entry_count);
			rq->hdr_buf = NULL;
			ocs_hw_rx_buffer_free(hw, rq->payload_buf, rq->entry_count);
			rq->payload_buf = NULL;
		}
	}
}