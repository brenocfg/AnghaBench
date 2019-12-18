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
struct sys_reg_desc {size_t reg; int /*<<< orphan*/  val; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dbg_bvr; } ;
struct TYPE_4__ {TYPE_1__ vcpu_debug_state; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */

__attribute__((used)) static void reset_bvr(struct kvm_vcpu *vcpu,
		      const struct sys_reg_desc *rd)
{
	vcpu->arch.vcpu_debug_state.dbg_bvr[rd->reg] = rd->val;
}