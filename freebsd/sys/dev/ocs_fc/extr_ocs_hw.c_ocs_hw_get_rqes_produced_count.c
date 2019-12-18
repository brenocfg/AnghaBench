#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_4__ {size_t hw_rq_count; TYPE_2__** hw_rq; } ;
typedef  TYPE_1__ ocs_hw_t ;
struct TYPE_5__ {size_t entry_count; int /*<<< orphan*/ ** rq_tracker; } ;
typedef  TYPE_2__ hw_rq_t ;

/* Variables and functions */

uint32_t
ocs_hw_get_rqes_produced_count(ocs_hw_t *hw)
{
	uint32_t count = 0;
	uint32_t i;
	uint32_t j;

	for (i = 0; i < hw->hw_rq_count; i++) {
		hw_rq_t *rq = hw->hw_rq[i];
		if (rq->rq_tracker != NULL) {
			for (j = 0; j < rq->entry_count; j++) {
				if (rq->rq_tracker[j] != NULL) {
					count++;
				}
			}
		}
	}

	return count;
}