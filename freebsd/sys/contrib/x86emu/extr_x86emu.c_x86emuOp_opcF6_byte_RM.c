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
typedef  int /*<<< orphan*/  uint8_t ;
struct x86emu {int cur_rh; } ;

/* Variables and functions */
 int /*<<< orphan*/  decode_and_fetch_byte (struct x86emu*) ; 
 int /*<<< orphan*/  decode_and_fetch_byte_imm8 (struct x86emu*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  div_byte (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_decode_modrm (struct x86emu*) ; 
 int /*<<< orphan*/  idiv_byte (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imul_byte (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mul_byte (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neg_byte (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_byte (struct x86emu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_back_byte (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x86emu_halt_sys (struct x86emu*) ; 

__attribute__((used)) static void
x86emuOp_opcF6_byte_RM(struct x86emu *emu)
{
	uint8_t destval, srcval;

	/* long, drawn out code follows.  Double switch for a total of 32
	 * cases.  */
	fetch_decode_modrm(emu);
	if (emu->cur_rh == 1)
		x86emu_halt_sys(emu);

	if (emu->cur_rh == 0) {
		destval = decode_and_fetch_byte_imm8(emu, &srcval);
		test_byte(emu, destval, srcval);
		return;
	}
	destval = decode_and_fetch_byte(emu);
	switch (emu->cur_rh) {
	case 2:
		destval = ~destval;
		write_back_byte(emu, destval);
		break;
	case 3:
		destval = neg_byte(emu, destval);
		write_back_byte(emu, destval);
		break;
	case 4:
		mul_byte(emu, destval);
		break;
	case 5:
		imul_byte(emu, destval);
		break;
	case 6:
		div_byte(emu, destval);
		break;
	case 7:
		idiv_byte(emu, destval);
		break;
	}
}