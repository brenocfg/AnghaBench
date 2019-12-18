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
struct jit_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_FP ; 
 int /*<<< orphan*/  ARM_LDR_I (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EBPF_SCRATCH_TO_ARM_FP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit (int /*<<< orphan*/ ,struct jit_ctx*) ; 
 scalar_t__ is_stacked (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s8 arm_bpf_get_reg32(s8 reg, s8 tmp, struct jit_ctx *ctx)
{
	if (is_stacked(reg)) {
		emit(ARM_LDR_I(tmp, ARM_FP, EBPF_SCRATCH_TO_ARM_FP(reg)), ctx);
		reg = tmp;
	}
	return reg;
}