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
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int /*<<< orphan*/  ioapic_handled_vectors; int /*<<< orphan*/  apic; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* load_eoi_exitmap ) (struct kvm_vcpu*,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  vec_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_or (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kvm_apic_hw_enabled (int /*<<< orphan*/ ) ; 
 TYPE_3__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 TYPE_2__* vcpu_to_synic (struct kvm_vcpu*) ; 

__attribute__((used)) static void vcpu_load_eoi_exitmap(struct kvm_vcpu *vcpu)
{
	u64 eoi_exit_bitmap[4];

	if (!kvm_apic_hw_enabled(vcpu->arch.apic))
		return;

	bitmap_or((ulong *)eoi_exit_bitmap, vcpu->arch.ioapic_handled_vectors,
		  vcpu_to_synic(vcpu)->vec_bitmap, 256);
	kvm_x86_ops->load_eoi_exitmap(vcpu, eoi_exit_bitmap);
}