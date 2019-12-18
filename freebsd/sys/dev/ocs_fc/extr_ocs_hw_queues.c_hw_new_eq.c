#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/  os; int /*<<< orphan*/  eq_list; TYPE_2__** hw_eq; int /*<<< orphan*/  sli; TYPE_3__* eq; int /*<<< orphan*/  eq_count; } ;
typedef  TYPE_1__ ocs_hw_t ;
struct TYPE_11__ {size_t instance; int /*<<< orphan*/  entry_count; TYPE_3__* queue; int /*<<< orphan*/ * wq_array; int /*<<< orphan*/  cq_list; TYPE_1__* hw; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ hw_eq_t ;
struct TYPE_12__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_MAX_NUM_WQ ; 
 int OCS_M_NOWAIT ; 
 int OCS_M_ZERO ; 
 int /*<<< orphan*/  SLI_QTYPE_EQ ; 
 int /*<<< orphan*/  hw_cq_t ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ocs_list_add_tail (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_list_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,size_t) ; 
 TYPE_2__* ocs_malloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * ocs_varray_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_eq_modify_delay (int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sli_queue_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

hw_eq_t*
hw_new_eq(ocs_hw_t *hw, uint32_t entry_count)
{
	hw_eq_t *eq = ocs_malloc(hw->os, sizeof(*eq), OCS_M_ZERO | OCS_M_NOWAIT);

	if (eq != NULL) {
		eq->type = SLI_QTYPE_EQ;
		eq->hw = hw;
		eq->entry_count = entry_count;
		eq->instance = hw->eq_count++;
		eq->queue = &hw->eq[eq->instance];
		ocs_list_init(&eq->cq_list, hw_cq_t, link);

		eq->wq_array = ocs_varray_alloc(hw->os, OCS_HW_MAX_NUM_WQ);
		if (eq->wq_array == NULL) {
			ocs_free(hw->os, eq, sizeof(*eq));
			eq = NULL;
		} else {
			if (sli_queue_alloc(&hw->sli, SLI_QTYPE_EQ, eq->queue, entry_count, NULL, 0)) {
				ocs_log_err(hw->os, "EQ[%d] allocation failure\n", eq->instance);
				ocs_free(hw->os, eq, sizeof(*eq));
				eq = NULL;
			} else {
				sli_eq_modify_delay(&hw->sli, eq->queue, 1, 0, 8);
				hw->hw_eq[eq->instance] = eq;
				ocs_list_add_tail(&hw->eq_list, eq);
				ocs_log_debug(hw->os, "create eq[%2d] id %3d len %4d\n", eq->instance, eq->queue->id,
					eq->entry_count);
			}
		}
	}
	return eq;
}