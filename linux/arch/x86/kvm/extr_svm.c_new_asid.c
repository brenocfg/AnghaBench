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
struct vcpu_svm {TYPE_2__* vmcb; scalar_t__ asid_generation; } ;
struct svm_cpu_data {scalar_t__ next_asid; scalar_t__ max_asid; scalar_t__ min_asid; scalar_t__ asid_generation; } ;
struct TYPE_3__ {scalar_t__ asid; int /*<<< orphan*/  tlb_ctl; } ;
struct TYPE_4__ {TYPE_1__ control; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLB_CONTROL_FLUSH_ALL_ASID ; 
 int /*<<< orphan*/  VMCB_ASID ; 
 int /*<<< orphan*/  mark_dirty (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void new_asid(struct vcpu_svm *svm, struct svm_cpu_data *sd)
{
	if (sd->next_asid > sd->max_asid) {
		++sd->asid_generation;
		sd->next_asid = sd->min_asid;
		svm->vmcb->control.tlb_ctl = TLB_CONTROL_FLUSH_ALL_ASID;
	}

	svm->asid_generation = sd->asid_generation;
	svm->vmcb->control.asid = sd->next_asid++;

	mark_dirty(svm->vmcb, VMCB_ASID);
}