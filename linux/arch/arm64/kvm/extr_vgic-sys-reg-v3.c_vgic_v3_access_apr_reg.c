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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t u8 ;
struct vgic_v3_cpu_if {int /*<<< orphan*/ * vgic_ap0r; int /*<<< orphan*/ * vgic_ap1r; } ;
struct sys_reg_params {int /*<<< orphan*/  regval; scalar_t__ is_write; } ;
struct TYPE_3__ {struct vgic_v3_cpu_if vgic_v3; } ;
struct TYPE_4__ {TYPE_1__ vgic_cpu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */

__attribute__((used)) static void vgic_v3_access_apr_reg(struct kvm_vcpu *vcpu,
				   struct sys_reg_params *p, u8 apr, u8 idx)
{
	struct vgic_v3_cpu_if *vgicv3 = &vcpu->arch.vgic_cpu.vgic_v3;
	uint32_t *ap_reg;

	if (apr)
		ap_reg = &vgicv3->vgic_ap1r[idx];
	else
		ap_reg = &vgicv3->vgic_ap0r[idx];

	if (p->is_write)
		*ap_reg = p->regval;
	else
		p->regval = *ap_reg;
}