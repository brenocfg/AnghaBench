#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/ ** hw_wq; int /*<<< orphan*/ * wq_cpu_array; int /*<<< orphan*/ * wq_class_array; } ;
typedef  TYPE_1__ ocs_hw_t ;
struct TYPE_7__ {int wq_steering; size_t wq_class; TYPE_3__* eq; } ;
typedef  TYPE_2__ ocs_hw_io_t ;
typedef  int /*<<< orphan*/  hw_wq_t ;
struct TYPE_8__ {int /*<<< orphan*/  wq_array; } ;
typedef  TYPE_3__ hw_eq_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
#define  OCS_HW_WQ_STEERING_CLASS 130 
#define  OCS_HW_WQ_STEERING_CPU 129 
#define  OCS_HW_WQ_STEERING_REQUEST 128 
 int /*<<< orphan*/  likely (int) ; 
 size_t ocs_thread_getcpu () ; 
 int /*<<< orphan*/ * ocs_varray_iter_next (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

hw_wq_t *
ocs_hw_queue_next_wq(ocs_hw_t *hw, ocs_hw_io_t *io)
{
	hw_eq_t *eq;
	hw_wq_t *wq = NULL;

	switch(io->wq_steering) {
	case OCS_HW_WQ_STEERING_CLASS:
		if (likely(io->wq_class < ARRAY_SIZE(hw->wq_class_array))) {
			wq = ocs_varray_iter_next(hw->wq_class_array[io->wq_class]);
		}
		break;
	case OCS_HW_WQ_STEERING_REQUEST:
		eq = io->eq;
		if (likely(eq != NULL)) {
			wq = ocs_varray_iter_next(eq->wq_array);
		}
		break;
	case OCS_HW_WQ_STEERING_CPU: {
		uint32_t cpuidx = ocs_thread_getcpu();

		if (likely(cpuidx < ARRAY_SIZE(hw->wq_cpu_array))) {
			wq = ocs_varray_iter_next(hw->wq_cpu_array[cpuidx]);
		}
		break;
	}
	}

	if (unlikely(wq == NULL)) {
		wq = hw->hw_wq[0];
	}

	return wq;
}