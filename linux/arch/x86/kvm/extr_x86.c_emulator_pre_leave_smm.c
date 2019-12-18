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
struct x86_emulate_ctxt {int dummy; } ;
struct TYPE_2__ {int (* pre_leave_smm ) (int /*<<< orphan*/ ,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  emul_to_vcpu (struct x86_emulate_ctxt*) ; 
 TYPE_1__* kvm_x86_ops ; 
 int stub1 (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int emulator_pre_leave_smm(struct x86_emulate_ctxt *ctxt,
				  const char *smstate)
{
	return kvm_x86_ops->pre_leave_smm(emul_to_vcpu(ctxt), smstate);
}