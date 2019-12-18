#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
struct sys_reg_params {int regval; scalar_t__ is_32bit; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void dbg_to_reg(struct kvm_vcpu *vcpu,
		       struct sys_reg_params *p,
		       u64 *dbg_reg)
{
	p->regval = *dbg_reg;
	if (p->is_32bit)
		p->regval &= 0xffffffffUL;
}