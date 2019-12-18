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
struct x86emu {int cur_mod; } ;

/* Variables and functions */
 int /*<<< orphan*/  decode_rl_address (struct x86emu*) ; 
 int /*<<< orphan*/ * decode_rl_word_register (struct x86emu*) ; 
 int /*<<< orphan*/  fetch_decode_modrm (struct x86emu*) ; 
 int /*<<< orphan*/  pop_word (struct x86emu*) ; 
 int /*<<< orphan*/  store_data_word (struct x86emu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
x86emuOp16_pop_RM(struct x86emu *emu)
{
	uint32_t destoffset;
	uint16_t destval, *destreg;

	fetch_decode_modrm(emu);
	if (emu->cur_mod != 3) {
		destoffset = decode_rl_address(emu);
		destval = pop_word(emu);
		store_data_word(emu, destoffset, destval);
	} else {
		destreg = decode_rl_word_register(emu);
		*destreg = pop_word(emu);
	}
}