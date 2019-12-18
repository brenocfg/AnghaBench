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
typedef  int /*<<< orphan*/  u32 ;
struct x86_exception {scalar_t__ error_code; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* translate_gpa ) (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct x86_exception*) ;} ;
struct TYPE_4__ {TYPE_1__ nested_mmu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
typedef  int /*<<< orphan*/  gva_t ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct x86_exception*) ; 

__attribute__((used)) static gpa_t nonpaging_gva_to_gpa_nested(struct kvm_vcpu *vcpu, gva_t vaddr,
					 u32 access,
					 struct x86_exception *exception)
{
	if (exception)
		exception->error_code = 0;
	return vcpu->arch.nested_mmu.translate_gpa(vcpu, vaddr, access, exception);
}