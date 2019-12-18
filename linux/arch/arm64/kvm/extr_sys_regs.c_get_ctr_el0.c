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
struct sys_reg_desc {int /*<<< orphan*/  val; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_CTR_EL0 ; 
 int /*<<< orphan*/  read_sanitised_ftr_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_ctr_el0(struct kvm_vcpu *v, const struct sys_reg_desc *r)
{
	((struct sys_reg_desc *)r)->val = read_sanitised_ftr_reg(SYS_CTR_EL0);
}