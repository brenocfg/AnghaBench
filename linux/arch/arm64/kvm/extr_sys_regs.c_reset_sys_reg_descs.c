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
struct sys_reg_desc {int reg; int /*<<< orphan*/  (* reset ) (struct kvm_vcpu*,struct sys_reg_desc const*) ;} ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int NR_SYS_REGS ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,struct sys_reg_desc const*) ; 

__attribute__((used)) static void reset_sys_reg_descs(struct kvm_vcpu *vcpu,
				const struct sys_reg_desc *table, size_t num,
				unsigned long *bmap)
{
	unsigned long i;

	for (i = 0; i < num; i++)
		if (table[i].reset) {
			int reg = table[i].reg;

			table[i].reset(vcpu, &table[i]);
			if (reg > 0 && reg < NR_SYS_REGS)
				set_bit(reg, bmap);
		}
}