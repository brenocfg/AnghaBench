#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_uncore_box {TYPE_1__* pmu; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int event_ctl; scalar_t__ pair_ctr_ctl; } ;
struct TYPE_3__ {TYPE_2__* type; } ;

/* Variables and functions */
 int CFL_UNC_CBO_7_PERFEVTSEL0 ; 
 int /*<<< orphan*/  UNCORE_BOX_FLAG_CFL8_CBOX_MSR_OFFS ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uncore_msr_box_offset (struct intel_uncore_box*) ; 

__attribute__((used)) static inline
unsigned uncore_msr_event_ctl(struct intel_uncore_box *box, int idx)
{
	if (test_bit(UNCORE_BOX_FLAG_CFL8_CBOX_MSR_OFFS, &box->flags)) {
		return CFL_UNC_CBO_7_PERFEVTSEL0 +
		       (box->pmu->type->pair_ctr_ctl ? 2 * idx : idx);
	} else {
		return box->pmu->type->event_ctl +
		       (box->pmu->type->pair_ctr_ctl ? 2 * idx : idx) +
		       uncore_msr_box_offset(box);
	}
}