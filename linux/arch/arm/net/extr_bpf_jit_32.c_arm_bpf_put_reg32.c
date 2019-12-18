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
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_FP ; 
 int /*<<< orphan*/  ARM_MOV_R (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ARM_STR_I (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EBPF_SCRATCH_TO_ARM_FP (scalar_t__) ; 
 int /*<<< orphan*/  emit (int /*<<< orphan*/ ,struct jit_ctx*) ; 
 scalar_t__ is_stacked (scalar_t__) ; 

__attribute__((used)) static void arm_bpf_put_reg32(s8 reg, s8 src, struct jit_ctx *ctx)
{
	if (is_stacked(reg))
		emit(ARM_STR_I(src, ARM_FP, EBPF_SCRATCH_TO_ARM_FP(reg)), ctx);
	else if (reg != src)
		emit(ARM_MOV_R(reg, src), ctx);
}