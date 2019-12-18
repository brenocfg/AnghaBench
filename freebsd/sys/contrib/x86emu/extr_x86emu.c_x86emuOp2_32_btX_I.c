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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct x86emu {int cur_rh; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONDITIONAL_SET_FLAG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_CF ; 
 int decode_and_fetch_long_imm8 (struct x86emu*,int*) ; 
 int /*<<< orphan*/  fetch_decode_modrm (struct x86emu*) ; 
 int /*<<< orphan*/  write_back_long (struct x86emu*,int) ; 
 int /*<<< orphan*/  x86emu_halt_sys (struct x86emu*) ; 

__attribute__((used)) static void
x86emuOp2_32_btX_I(struct x86emu *emu)
{
	int bit;
	uint32_t srcval, mask;
	uint8_t shift;

	fetch_decode_modrm(emu);
	if (emu->cur_rh < 4)
		x86emu_halt_sys(emu);

	srcval = decode_and_fetch_long_imm8(emu, &shift);
	bit = shift & 0x1F;
	mask = (0x1 << bit);

	switch (emu->cur_rh) {
	case 5:
		write_back_long(emu, srcval | mask);
		break;
	case 6:
		write_back_long(emu, srcval & ~mask);
		break;
	case 7:
		write_back_long(emu, srcval ^ mask);
		break;
	}
	CONDITIONAL_SET_FLAG(srcval & mask, F_CF);
}