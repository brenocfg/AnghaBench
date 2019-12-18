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
typedef  int uint32_t ;
struct x86emu {int dummy; } ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONDITIONAL_SET_FLAG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_CF ; 
 int decode_and_fetch_long_disp (struct x86emu*,int) ; 
 int* decode_rh_long_register (struct x86emu*) ; 
 int /*<<< orphan*/  fetch_decode_modrm (struct x86emu*) ; 
 int /*<<< orphan*/  write_back_long (struct x86emu*,int) ; 

__attribute__((used)) static void
common_bitstring32(struct x86emu *emu, int op)
{
	int bit;
	uint32_t srcval, *shiftreg, mask;

	fetch_decode_modrm(emu);
	shiftreg = decode_rh_long_register(emu);
	srcval = decode_and_fetch_long_disp(emu, (int16_t) *shiftreg >> 5);
	bit = *shiftreg & 0x1F;
	mask =  0x1 << bit;
	CONDITIONAL_SET_FLAG(srcval & mask, F_CF);

	switch (op) {
	case 0:
		break;
	case 1:
		write_back_long(emu, srcval | mask);
		break;
	case 2:
		write_back_long(emu, srcval & ~mask);
		break;
	case 3:
		write_back_long(emu, srcval ^ mask);
		break;
	}
}