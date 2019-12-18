#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct kvm_s390_sie_block {int ibc; } ;
struct vsie_page {struct kvm_s390_sie_block* scb_o; struct kvm_s390_sie_block scb_s; } ;
struct kvm_vcpu {TYPE_3__* kvm; } ;
typedef  scalar_t__ __u64 ;
struct TYPE_8__ {int ibc; } ;
struct TYPE_5__ {scalar_t__ ibc; } ;
struct TYPE_6__ {TYPE_1__ model; } ;
struct TYPE_7__ {TYPE_2__ arch; } ;

/* Variables and functions */
 int READ_ONCE (int const) ; 
 TYPE_4__ sclp ; 

__attribute__((used)) static void prepare_ibc(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page)
{
	struct kvm_s390_sie_block *scb_s = &vsie_page->scb_s;
	struct kvm_s390_sie_block *scb_o = vsie_page->scb_o;
	/* READ_ONCE does not work on bitfields - use a temporary variable */
	const uint32_t __new_ibc = scb_o->ibc;
	const uint32_t new_ibc = READ_ONCE(__new_ibc) & 0x0fffU;
	__u64 min_ibc = (sclp.ibc >> 16) & 0x0fffU;

	scb_s->ibc = 0;
	/* ibc installed in g2 and requested for g3 */
	if (vcpu->kvm->arch.model.ibc && new_ibc) {
		scb_s->ibc = new_ibc;
		/* takte care of the minimum ibc level of the machine */
		if (scb_s->ibc < min_ibc)
			scb_s->ibc = min_ibc;
		/* take care of the maximum ibc level set for the guest */
		if (scb_s->ibc > vcpu->kvm->arch.model.ibc)
			scb_s->ibc = vcpu->kvm->arch.model.ibc;
	}
}