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
struct kvm_vcpu {int dummy; } ;
struct kvm_pmu {int /*<<< orphan*/  irq_work; } ;
struct TYPE_4__ {TYPE_1__* pmu_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* init ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  init_irq_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_pmi_trigger_fn ; 
 int /*<<< orphan*/  kvm_pmu_refresh (struct kvm_vcpu*) ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  memset (struct kvm_pmu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*) ; 
 struct kvm_pmu* vcpu_to_pmu (struct kvm_vcpu*) ; 

void kvm_pmu_init(struct kvm_vcpu *vcpu)
{
	struct kvm_pmu *pmu = vcpu_to_pmu(vcpu);

	memset(pmu, 0, sizeof(*pmu));
	kvm_x86_ops->pmu_ops->init(vcpu);
	init_irq_work(&pmu->irq_work, kvm_pmi_trigger_fn);
	kvm_pmu_refresh(vcpu);
}