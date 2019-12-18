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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  EMIT1 (int) ; 
 int /*<<< orphan*/  EMIT1_off32 (int /*<<< orphan*/ ,scalar_t__ const) ; 
 int /*<<< orphan*/  EMIT2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMIT3_off32 (int,int,int /*<<< orphan*/ ,scalar_t__ const) ; 
 int add_1mod (int,scalar_t__) ; 
 int /*<<< orphan*/  add_1reg (int,scalar_t__) ; 
 int add_2mod (int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  add_2reg (int,scalar_t__,scalar_t__) ; 
 scalar_t__ is_ereg (scalar_t__) ; 

__attribute__((used)) static void emit_mov_imm32(u8 **pprog, bool sign_propagate,
			   u32 dst_reg, const u32 imm32)
{
	u8 *prog = *pprog;
	u8 b1, b2, b3;
	int cnt = 0;

	/*
	 * Optimization: if imm32 is positive, use 'mov %eax, imm32'
	 * (which zero-extends imm32) to save 2 bytes.
	 */
	if (sign_propagate && (s32)imm32 < 0) {
		/* 'mov %rax, imm32' sign extends imm32 */
		b1 = add_1mod(0x48, dst_reg);
		b2 = 0xC7;
		b3 = 0xC0;
		EMIT3_off32(b1, b2, add_1reg(b3, dst_reg), imm32);
		goto done;
	}

	/*
	 * Optimization: if imm32 is zero, use 'xor %eax, %eax'
	 * to save 3 bytes.
	 */
	if (imm32 == 0) {
		if (is_ereg(dst_reg))
			EMIT1(add_2mod(0x40, dst_reg, dst_reg));
		b2 = 0x31; /* xor */
		b3 = 0xC0;
		EMIT2(b2, add_2reg(b3, dst_reg, dst_reg));
		goto done;
	}

	/* mov %eax, imm32 */
	if (is_ereg(dst_reg))
		EMIT1(add_1mod(0x40, dst_reg));
	EMIT1_off32(add_1reg(0xB8, dst_reg), imm32);
done:
	*pprog = prog;
}