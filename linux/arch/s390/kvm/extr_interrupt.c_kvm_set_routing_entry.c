#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  adapter_id; int /*<<< orphan*/  ind_offset; int /*<<< orphan*/  summary_offset; int /*<<< orphan*/  ind_addr; int /*<<< orphan*/  summary_addr; } ;
struct kvm_kernel_irq_routing_entry {TYPE_1__ adapter; int /*<<< orphan*/  set; } ;
struct TYPE_5__ {int /*<<< orphan*/  adapter_id; int /*<<< orphan*/  ind_offset; int /*<<< orphan*/  summary_offset; int /*<<< orphan*/  ind_addr; int /*<<< orphan*/  summary_addr; } ;
struct TYPE_6__ {TYPE_2__ adapter; } ;
struct kvm_irq_routing_entry {int type; TYPE_3__ u; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  KVM_IRQ_ROUTING_S390_ADAPTER 128 
 int /*<<< orphan*/  set_adapter_int ; 

int kvm_set_routing_entry(struct kvm *kvm,
			  struct kvm_kernel_irq_routing_entry *e,
			  const struct kvm_irq_routing_entry *ue)
{
	int ret;

	switch (ue->type) {
	case KVM_IRQ_ROUTING_S390_ADAPTER:
		e->set = set_adapter_int;
		e->adapter.summary_addr = ue->u.adapter.summary_addr;
		e->adapter.ind_addr = ue->u.adapter.ind_addr;
		e->adapter.summary_offset = ue->u.adapter.summary_offset;
		e->adapter.ind_offset = ue->u.adapter.ind_offset;
		e->adapter.adapter_id = ue->u.adapter.adapter_id;
		ret = 0;
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}