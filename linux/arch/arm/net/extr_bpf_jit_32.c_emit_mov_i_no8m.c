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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct jit_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_LDR_I (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARM_MOVT (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  ARM_MOVW (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  ARM_PC ; 
 int /*<<< orphan*/  emit (int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int /*<<< orphan*/  imm_offset (int,struct jit_ctx*) ; 

__attribute__((used)) static inline void emit_mov_i_no8m(const u8 rd, u32 val, struct jit_ctx *ctx)
{
#if __LINUX_ARM_ARCH__ < 7
	emit(ARM_LDR_I(rd, ARM_PC, imm_offset(val, ctx)), ctx);
#else
	emit(ARM_MOVW(rd, val & 0xffff), ctx);
	if (val > 0xffff)
		emit(ARM_MOVT(rd, val >> 16), ctx);
#endif
}