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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct x86emu {int cur_rh; int cur_mod; } ;

/* Variables and functions */
 int /*<<< orphan*/  decode_and_fetch_word (struct x86emu*) ; 
 int /*<<< orphan*/  decode_rl_address (struct x86emu*) ; 
 int /*<<< orphan*/ * decode_rl_word_register (struct x86emu*) ; 
 int /*<<< orphan*/  div_word (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_data_word (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_decode_modrm (struct x86emu*) ; 
 int /*<<< orphan*/  fetch_word_imm (struct x86emu*) ; 
 int /*<<< orphan*/  idiv_word (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imul_word (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mul_word (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neg_word (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_word (struct x86emu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_back_word (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x86emu_halt_sys (struct x86emu*) ; 

__attribute__((used)) static void
x86emuOp16_opcF7_word_RM(struct x86emu *emu)
{
	uint16_t destval, srcval;

	/* long, drawn out code follows.  Double switch for a total of 32
	 * cases.  */
	fetch_decode_modrm(emu);
	if (emu->cur_rh == 1)
		x86emu_halt_sys(emu);

	if (emu->cur_rh == 0) {
		if (emu->cur_mod != 3) {
			uint32_t destoffset;

			destoffset = decode_rl_address(emu);
			srcval = fetch_word_imm(emu);
			destval = fetch_data_word(emu, destoffset);
		} else {
			srcval = fetch_word_imm(emu);
			destval = *decode_rl_word_register(emu);
		}
		test_word(emu, destval, srcval);
		return;
	}
	destval = decode_and_fetch_word(emu);
	switch (emu->cur_rh) {
	case 2:
		destval = ~destval;
		write_back_word(emu, destval);
		break;
	case 3:
		destval = neg_word(emu, destval);
		write_back_word(emu, destval);
		break;
	case 4:
		mul_word(emu, destval);
		break;
	case 5:
		imul_word(emu, destval);
		break;
	case 6:
		div_word(emu, destval);
		break;
	case 7:
		idiv_word(emu, destval);
		break;
	}
}