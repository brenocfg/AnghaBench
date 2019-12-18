#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mm_struct {int dummy; } ;
struct TYPE_2__ {struct mm_struct guest_user_mm; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_asid (int,struct mm_struct*) ; 
 int smp_processor_id () ; 

__attribute__((used)) static u32 kvm_mips_get_user_asid(struct kvm_vcpu *vcpu)
{
	struct mm_struct *user_mm = &vcpu->arch.guest_user_mm;
	int cpu = smp_processor_id();

	return cpu_asid(cpu, user_mm);
}