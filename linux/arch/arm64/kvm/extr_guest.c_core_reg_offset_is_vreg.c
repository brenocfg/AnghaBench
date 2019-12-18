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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {int /*<<< orphan*/  fpsr; int /*<<< orphan*/  vregs; } ;

/* Variables and functions */
 scalar_t__ KVM_REG_ARM_CORE_REG (int /*<<< orphan*/ ) ; 
 TYPE_1__ fp_regs ; 

__attribute__((used)) static bool core_reg_offset_is_vreg(u64 off)
{
	return off >= KVM_REG_ARM_CORE_REG(fp_regs.vregs) &&
		off < KVM_REG_ARM_CORE_REG(fp_regs.fpsr);
}