#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_8__ {size_t hw_rq_count; int /*<<< orphan*/  seq_pool; TYPE_3__** hw_rq; } ;
typedef  TYPE_1__ ocs_hw_t ;
struct TYPE_9__ {int /*<<< orphan*/ * payload; int /*<<< orphan*/ * header; } ;
typedef  TYPE_2__ ocs_hw_sequence_t ;
typedef  scalar_t__ ocs_hw_rtn_e ;
typedef  scalar_t__ int32_t ;
struct TYPE_10__ {int entry_count; int /*<<< orphan*/ * payload_buf; int /*<<< orphan*/ * hdr_buf; } ;
typedef  TYPE_3__ hw_rq_t ;

/* Variables and functions */
 TYPE_2__* ocs_array_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_hw_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ ocs_hw_sequence_free (TYPE_1__*,TYPE_2__*) ; 

ocs_hw_rtn_e
ocs_hw_rx_post(ocs_hw_t *hw)
{
	uint32_t i;
	uint32_t idx;
	uint32_t rq_idx;
	int32_t rc = 0;

	/*
	 * In RQ pair mode, we MUST post the header and payload buffer at the
	 * same time.
	 */
	for (rq_idx = 0, idx = 0; rq_idx < hw->hw_rq_count; rq_idx++) {
		hw_rq_t *rq = hw->hw_rq[rq_idx];

		for (i = 0; i < rq->entry_count-1; i++) {
			ocs_hw_sequence_t *seq = ocs_array_get(hw->seq_pool, idx++);
			ocs_hw_assert(seq != NULL);

			seq->header = &rq->hdr_buf[i];

			seq->payload = &rq->payload_buf[i];

			rc = ocs_hw_sequence_free(hw, seq);
			if (rc) {
				break;
			}
		}
		if (rc) {
			break;
		}
	}

	return rc;
}